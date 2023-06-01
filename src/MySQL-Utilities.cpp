#include "MySQL-Utilities.h"
#include <iostream>
#include <conio.h>

//Displays all the contents of a table object.
void mysqlu::DisplayFullTable(mysqlx::Table& p_Table) {
	mysqlx::RowResult t_Result;

	try {
		t_Result = p_Table.select("*").execute();
	}
	catch (mysqlx::Error& e) {
		std::cerr << "Error: " << e.what() << std::endl;
		return;
	}

	std::vector<std::string> t_ColumnNames;
	for (const auto& column : t_Result.getColumns()) { 
		t_ColumnNames.push_back(column.getColumnLabel());
	}

	for (const auto& columnName : t_ColumnNames) {
		std::cout << columnName << "\t";
	}
	std::cout << std::endl;

	std::vector<mysqlx::Row> rows = t_Result.fetchAll();
	for (const auto& row : rows) {
		for (size_t i = 0; i < t_ColumnNames.size(); i++) { 
			std::cout << row[i] << "\t"; 
		}
		std::cout << std::endl; 
	}
}

//Reads the password from the windows console, while displaying "*" instead of echoing the password in the console.
void mysqlu::ReadPassword(std::string& p_Password) {
    int i = 0;
    char t_Password[100], ch;

    while (true) {
        ch = _getch();
        if (ch == '\r') break;

        if (ch != 8 && ch != 13) {
            std::cout << "*";
            t_Password[i] = ch;
            i++;
        }
        else if (ch == 8 && i > 0) {
            std::cout << "\b \b";
            i--;
        }
    }
    t_Password[i] = '\0';

    p_Password = t_Password;
}

//Reads a username and password from the console and returns the session when successful.
mysqlx::Session mysqlu::Login() {
	std::string t_Username, t_Password;

	std::cout << "Enter Username: ";
	std::cin >> t_Username;
	std::cout << "Enter Password: ";
	ReadPassword(t_Password);

	try {
		system("cls");
		mysqlx::Session sess("localhost", 33060, t_Username, t_Password);
		return sess;
	}
	catch (const mysqlx::Error& e) {
		system("cls");
		std::cerr << "Error: " << e.what() << "\n\n";
		return Login();
	}
}