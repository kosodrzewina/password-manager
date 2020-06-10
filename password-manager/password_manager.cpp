#include <iostream>
#include <fstream>
#include <filesystem>

#include "password_manager.hpp"
#include "Data.hpp"

namespace serde
{
	std::vector<Entry> serialize(std::string file_name, std::string key)
	{
		std::vector<Entry> output;
		std::fstream file(file_name);

		if (file.is_open())
		{
			std::string line;
			size_t index = 0;
			Entry data_piece;

			while (std::getline(file, line))
			{
				if (data_piece.login == "")
					data_piece.login = hash::decrypt(line, key);
				else
					data_piece.password = hash::decrypt(line, key);

				if (index % 2 != 0)
				{
					output.push_back(data_piece);
					data_piece = Entry();
				}

				index++;
			}
		}

		return output;
	}

	void deserialize(const char* file_name, Entry credentials, std::string key)
	{
		std::ofstream file(file_name, std::ios::app);
		file << hash::encrypt(credentials.login, key) << std::endl
			 << hash::encrypt(credentials.password, key) << std::endl;
	}
}

namespace hash
{
	std::string decrypt(std::string str, std::string key)
	{
		std::string result = "";

		for (int str_index = 0, key_index = 0; str_index < str.size(); str_index++, key_index++)
		{
			int offset = str[str_index] - key[key_index] + 32;

			result += (offset < 32) ? 96 + offset : offset;

			if (key_index == key.size() - 1)
				key_index = -1;
		}

		return result;
	}

	std::string encrypt(std::string str, std::string key)
	{
		std::string result = "";

		for (int str_index = 0, key_index = 0; str_index < str.size(); str_index++, key_index++)
		{
			int offset = str[str_index] + key[key_index] - 32;

			result += (offset > 127) ? offset - 96 : offset;

			if (key_index == key.size() - 1)
				key_index = -1;
		}

		return result;
	}

	bool grant_access(std::string input, std::string offset, std::string master)
	{
		return (encrypt(input, offset) == master);
	}
}

void loop(Data data)
{
	int input;

	std::cout << "0 - list all credentials\n1 - add new entry\n2 - exit" << std::endl;
	std::cin >> input;

	enum class Actions { list_all, add_entry, exit };
	Actions action = static_cast<Actions>(input);

	if (std::cin.fail())
	{
		std::cout << "Wrong input!" << std::endl;
		std::cin.clear();
		std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

		loop(data);
	}

	switch (action)
	{
		case Actions::list_all: data.list_all();
			break;

		case Actions::add_entry: data.add_entry();
			break;

		case Actions::exit: exit(0);

		default: std::cout << "Wrong input!" << std::endl;
			break;
	}

	loop(data);
}

int main()
{
	const std::string master_hash = "QPUfJGPYRb", master_offset = "master_offset";
	const char* file_name = "credentials.txt";
	std::string master_password;

	std::cout << "Enter password: ";
	std::cin >> master_password;

	const bool access = hash::grant_access(master_password, master_offset, master_hash);

	std::cout << hash::encrypt("dobre-haslo", master_offset) << std::endl;
	if (access)
	{
		std::cout << "Access granted!" << std::endl;

		Data* data = new Data(file_name, master_password);
		loop(*data);
	}
	else
	{
		std::cout << "Wrong password!";
		exit(0);
	}
}
