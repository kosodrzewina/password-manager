#pragma once

#include <fstream>
#include <filesystem>
#include <vector>

namespace serde
{
	std::string serialize();
	void deserialize(std::string);
}

namespace hash
{
	std::string encrypt(std::string, std::string);
	std::string decrypt(std::string, std::string);
	bool grant_access(std::string, std::string);
}

struct Data
{
	std::string file_name;
	std::vector<std::vector<std::string>> credentials_list;

public:
	Data(std::string);
	
	void create_file(std::ofstream);
	void save_credentials(std::string, std::string);
	std::vector<std::vector<std::string>> get_list();
};
