#include "CRUD.h"
#include <iostream>
#include "MySQL-Utilities.h"

CRUD::CRUD(mysqlx::Session* p_sess) {
	m_sess = p_sess;
}

void CRUD::ListDatabases() {
	std::vector<mysqlx::Schema> t_Schemas = m_sess->getSchemas();

	std::cout << "Available Schemas Are: \n";
	int i = 1;
	for (const auto& schema : t_Schemas) {
		std::cout << i++ << ". " << schema.getName() << std::endl;
	}
	std::cout << "\n";
}

bool CRUD::ListTables(const std::string& p_DbName) {
	std::vector<std::string> t_TableNames;
	try {
		t_TableNames = m_sess->getSchema(p_DbName).getTableNames();
	}
	catch (mysqlx::Error& e) {
		std::cerr << "Error: " << e.what() << std::endl;
		return true;
	}

	std::cout << "Available Tables are: \n";
	int i = 1;
	for (const auto& tablename : t_TableNames) {
		std::cout << i++ << ". " << tablename << std::endl;
	}
	std::cout << "\n";
	return false;
}

bool CRUD::DescribeTable(const std::string& p_DbName, const std::string& p_TableName) {
	try {
		mysqlx::Table t_Table = m_sess->getSchema(p_DbName).getTable(p_TableName);
		mysqlx::RowResult t_Result = t_Table.select("*").execute();

		std::cout << "Available Fields: \n";
		int i = 1;
		for (const auto& column : t_Result.getColumns()) {
			std::cout << i++ << ". " << column.getColumnLabel() << std::endl;
		}
		std::cout << "\n";
		return false;
	}
	catch (mysqlx::Error& e) {
		std::cerr << "Error: " << e.what() << std::endl;
		return true;
	}
}

void CRUD::DisplayTable() {
	system("cls");
	std::string t_DbName, t_TableName, t_Constraints, t_Values;

	ListDatabases();
	std::cout << "Enter name of Database/Schema: ";
	std::cin >> t_DbName;

	system("cls");
	if (ListTables(t_DbName)) return;
	std::cout << "Enter name of Table: ";
	std::cin >> t_TableName;

	try {
		mysqlx::Table t_Table = m_sess->getSchema(t_DbName).getTable(t_TableName);
		system("cls");
		std::cout << "Table:\n";
		mysqlu::DisplayFullTable(t_Table);
		std::cout << "\n";
	}
	catch (mysqlx::Error& e) {
		std::cerr << "Error: " << e.what() << std::endl;
	}
}

void CRUD::CreateDatabase() {
	std::string t_Name;

	system("cls");
	std::cout << "Enter name of Schema/Database to create: ";
	std::cin >> t_Name;

	try {
		m_sess->createSchema(t_Name);
		std::cout << "Schema/Database " + t_Name + " successfully created!" << std::endl;
	}
	catch (mysqlx::Error& e) {
		std::cerr << "Error: " << e.what() << std::endl;
	}
}

void CRUD::CreateTable() {
	system("cls");
	std::string t_DbName, t_TableName, t_Fields;

	ListDatabases();
	std::cout << "Enter name of Database/Schema: ";
	std::cin >> t_DbName;

	std::cout << "Enter name of Table: ";
	std::cin >> t_TableName;

	std::cout << "Enter the fields of the Table: ";
	std::cin.ignore();
	std::getline(std::cin, t_Fields);

	try {
		m_sess->sql("CREATE TABLE " + t_DbName + "." + t_TableName + "(" + t_Fields + ");").execute();
		std::cout << "Table " + t_TableName + " successfully created under schema: " + t_DbName << std::endl;
	}
	catch (mysqlx::Error& e) {
		std::cerr << "Error: " << e.what() << std::endl;
	}
}

void CRUD::InsertInto() {
	system("cls");
	std::string t_DbName, t_TableName, t_Constraints, t_Values;

	ListDatabases();
	std::cout << "Enter name of Database/Schema: ";
	std::cin >> t_DbName;

	system("cls");
	if (ListTables(t_DbName)) return;
	std::cout << "Enter name of Table: ";
	std::cin >> t_TableName;

	system("cls");
	if (DescribeTable(t_DbName, t_TableName)) return;
	std::cout << "Enter the constraints of the Table: ";
	std::cin.ignore();
	std::getline(std::cin, t_Constraints);

	std::cout << "Enter the values of the table based on constraints chosen: ";
	std::getline(std::cin, t_Values);

	try {
		m_sess->sql("INSERT INTO " + t_DbName + "." + t_TableName + "(" + t_Constraints + ") values(" + t_Values + ");").execute();
		std::cout << "Successfully inserted row into the table: " << t_TableName << std::endl;
	}
	catch (mysqlx::Error& e) {
		std::cerr << "Error: " << e.what() << std::endl;
	}
}

void CRUD::Update() {
	system("cls");
	std::string t_DbName, t_TableName, t_Set, t_Where;

	ListDatabases();
	std::cout << "Enter name of Database/Schema: ";
	std::cin >> t_DbName;

	system("cls");
	if (ListTables(t_DbName)) return;
	std::cout << "Enter name of Table: ";
	std::cin >> t_TableName;

	system("cls");
	if (DescribeTable(t_DbName, t_TableName)) return;
	std::cout << "Enter the set statement for table: ";
	std::cin.ignore();
	std::getline(std::cin, t_Set);

	std::cout << "Enter the where condition for which records to update: ";
	std::getline(std::cin, t_Where);

	try {
		m_sess->sql("UPDATE " + t_DbName + "." + t_TableName + " SET " + t_Set + " WHERE (" + t_Where + ");").execute();
		std::cout << "Successfully Updated the Row!" << std::endl;
	}
	catch (mysqlx::Error& e) {
		std::cerr << "Error: " << e.what() << std::endl;
	}
}

void CRUD::DeleteSchema() {
	system("cls");
	std::string t_DbName;

	ListDatabases();
	std::cout << "Enter name of Database/Schema: ";
	std::cin >> t_DbName;

	try {
		m_sess->dropSchema(t_DbName);
		std::cout << "Successfully deleted Database/Schema: " << t_DbName << std::endl;
	}
	catch (mysqlx::Error& e) {
		std::cerr << "Error: " << e.what() << std::endl;
	}
}

void CRUD::DeleteTable() {
	system("cls");
	std::string t_DbName, t_TableName;

	ListDatabases();
	std::cout << "Enter name of Database/Schema: ";
	std::cin >> t_DbName;

	system("cls");
	if (ListTables(t_DbName)) return;
	std::cout << "Enter name of Table: ";
	std::cin >> t_TableName;

	try {
		m_sess->sql("DROP TABLE " + t_DbName + "." + t_TableName + ";").execute();
		std::cout << "Successfully deleted Table: " << t_TableName << std::endl;
	}
	catch (mysqlx::Error& e) {
		std::cerr << "Error: " << e.what() << std::endl;
	}
}

void CRUD::DeleteRows() {
	system("cls");
	std::string t_DbName, t_TableName, t_Where;

	ListDatabases();
	std::cout << "Enter name of Database/Schema: ";
	std::cin >> t_DbName;

	system("cls");
	if (ListTables(t_DbName)) return;
	std::cout << "Enter name of Table: ";
	std::cin >> t_TableName;

	system("cls");
	if (DescribeTable(t_DbName, t_TableName)) return;
	std::cout << "Enter the where condition for which records to delete: ";
	std::cin.ignore();
	std::getline(std::cin, t_Where);

	try {
		m_sess->sql("DELETE FROM " + t_DbName + "." + t_TableName + " WHERE (" + t_Where + ");").execute();
		std::cout << "Successfully deleted the row(s)" << std::endl;
	}
	catch (mysqlx::Error& e) {
		std::cerr << "Error: " << e.what() << std::endl;
	}
}