#include <filesystem>
#include <fstream>
#include <iostream>

#include "Data.hpp"
#include "password_manager.hpp"

Data::Data(const char* file_name, std::string master_password) : file_name(file_name), master_password(master_password)
{
	if (!std::filesystem::exists(file_name))
		std::ofstream{ this->file_name };

	update_list();
}

Data::~Data()
{
	delete[] file_name;
}

void Data::update_list()
{
	credentials_list = serde::serialize(file_name, master_password);
}

void Data::list_all()
{
	std::cout << std::endl;

	for (int i = 0; i < credentials_list.size(); i++)
		std::cout << credentials_list[i].login << "    " << credentials_list[i].password << std::endl;

	std::cout << std::endl;
}

void Data::add_entry()
{
	std::string input;
	Entry entry;

	std::cout << "Enter login: ";
	std::cin >> input;

	entry.login = input;
	input = "";

	std::cout << "Enter password: ";
	std::cin >> input;

	entry.password = input;
	serde::deserialize(file_name, entry, master_password);

	update_list();
	std::cout << "Credentials added!" << std::endl;
}
