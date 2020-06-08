#include <filesystem>
#include <fstream>

#include "Data.hpp"
#include "password_manager.hpp"

Data::Data(const char* file_name, std::string master_password) : file_name(file_name), master_password(master_password)
{
	if (!std::filesystem::exists(file_name))
		std::ofstream{ this->file_name };

	update_list();
}

void Data::update_list()
{
	credentials_list = serde::serialize(file_name, master_password);
}
