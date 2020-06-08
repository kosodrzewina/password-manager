#pragma once

#include <vector>
#include <string>

#include "Data.hpp"

namespace serde
{
	std::vector<Entry> serialize(std::string, std::string key);
	void deserialize(std::string, Entry, std::string);
}

namespace hash
{
	std::string encrypt(std::string, std::string);
	std::string decrypt(std::string, std::string);
	bool grant_access(std::string, std::string);
}
