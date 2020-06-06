#include <iostream>

#include "password_manager.hpp"

namespace serde 
{
}

namespace hash
{
	std::string decrypt(std::string, std::string);

	bool grant_access(std::string input, std::string key)
	{
		return (decrypt(input, input) == key);
	}
}


int main()
{
	std::string master_password_encrypted, user_input;

	std::cout << "Enter password: ";
	std::cin >> user_input;

	bool access = hash::grant_access(user_input, master_password_encrypted);
}