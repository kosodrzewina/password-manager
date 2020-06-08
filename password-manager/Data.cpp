#include <filesystem>
#include <fstream>

#include "Data.hpp"
#include "password_manager.hpp"

Data::Data(std::string file_name, std::string master_password)
{
	this->file_name = file_name;
	this->master_password = master_password;

	if (!std::filesystem::exists(file_name))
		std::ofstream{ this->file_name };

	credentials_list = serde::serialize(file_name, master_password);
}