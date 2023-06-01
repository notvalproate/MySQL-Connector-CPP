#pragma once
#include <mysqlx/xdevapi.h>

class CRUD {
public:
	CRUD(mysqlx::Session* p_sess);

	void ListDatabases();
	bool ListTables(const std::string& p_DbName);
	bool DescribeTable(const std::string& p_DbName, const std::string& p_TableName);

	void DisplayTable();

	void CreateDatabase();
	void CreateTable();
	void InsertInto();
	void Update();
	
	void DeleteSchema();
	void DeleteTable();
	void DeleteRows();

private:
	mysqlx::Session* m_sess;
};