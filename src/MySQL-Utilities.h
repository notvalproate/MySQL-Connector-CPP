#pragma once
#include <mysqlx/xdevapi.h>

namespace mysqlu {
	void DisplayFullTable(mysqlx::Table& p_Table);
	void ReadPassword(std::string& p_Password);
	mysqlx::Session Login();
}