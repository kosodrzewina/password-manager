#pragma once

#include <string>
#include <vector>

struct Entry
{
	std::string login, password;
};

class Data
{
	std::string file_name;
	std::string master_password;
	std::vector<Entry> credentials_list;

public:
	Data(std::string, std::string);
};