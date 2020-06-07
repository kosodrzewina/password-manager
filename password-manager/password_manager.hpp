#pragma once

#include <iostream>
#include <fstream>
#include <filesystem>
#include <vector>
#include <string>

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

struct Data;
