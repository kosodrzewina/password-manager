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

	void deserialize(std::string file_name, Entry credentials, std::string key)
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
			int offset = str[str_index] - key[key_index];

			result += (offset < 0) ? 128 + offset : offset;

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
			int offset = str[str_index] + key[key_index];

			result += (offset > 127) ? offset - 128 : offset;

			if (key_index == key.size() - 1)
				key_index = -1;
		}

		return result;
	}

	bool grant_access(std::string input, std::string master)
	{
		return (encrypt(input, input) == master);
	}
}

int main()
{
	const std::string master_hash = "H^DdJZPBfX^", file_name = "credentials.txt";
	std::string master_password;

	std::cout << "Enter password: ";
	std::cin >> master_password;

	const bool access = hash::grant_access(master_password, master_hash);

	if (access)
	{
		std::cout << "Access granted!" << std::endl;

		Data* data = new Data(file_name, master_password);
	}
	else
	{
		std::cout << "Wrong password!";
		exit(0);
	}
}
