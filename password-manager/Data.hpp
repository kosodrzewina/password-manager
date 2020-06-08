#pragma once

#include <string>
#include <vector>

struct Entry
{
	std::string login, password;
};

class Data
{
	const char* file_name;
	std::string master_password;
	std::vector<Entry> credentials_list;

public:
	Data(const char*, std::string);
	~Data();

	void update_list();
	void list_all();
	void add_entry();
};
