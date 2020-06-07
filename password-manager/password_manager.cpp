#include <iostream>

#include "password_manager.hpp"

namespace serde 
{
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

	bool grant_access(std::string input, std::string key)
	{
		return (decrypt(input, input) == key);
	}
}

int main()
{
	const std::string master_password_encrypted;
	std::string user_input;

	std::cout << "Enter password: ";
	std::cin >> user_input;

	const bool access = hash::grant_access(user_input, master_password_encrypted);

	if (access)
	{
		// stuff
	}
	else
	{
		std::cout << "Wrong password!";
		exit(0);
	}
}
