#pragma once

#include <string>
#include <vector>

class Data
{
	std::string file_name;
	std::string master_password;
	std::vector<std::vector<std::string>> credentials_list;

public:
	Data(std::string, std::string);
};