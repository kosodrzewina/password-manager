#pragma once

#include <iostream>
#include <fstream>
#include <filesystem>
#include <vector>
#include <string>

namespace serde
{
	std::vector<std::vector<std::string>> serialize(std::string, std::string key);
	void deserialize(std::string, std::vector<std::string>, std::string);
}

namespace hash
{
	std::string encrypt(std::string, std::string);
	std::string decrypt(std::string, std::string);
	bool grant_access(std::string, std::string);
}

class Data
{
	std::string file_name;
	std::string master_password;
	std::vector<std::vector<std::string>> credentials_list;

public:
	Data(std::string, std::string);
};
