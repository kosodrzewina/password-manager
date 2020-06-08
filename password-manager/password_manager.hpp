#pragma once

#include <iostream>
#include <fstream>
#include <filesystem>
#include <vector>
#include <string>

namespace serde
{
	std::vector<std::vector<std::string>> serialize(std::string);
	void deserialize(std::string, std::vector<std::string>);
}

namespace hash
{
	std::string encrypt(std::string, std::string);
	std::string decrypt(std::string, std::string);
	bool grant_access(std::string, std::string);
}

struct Data;
