#pragma once

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
