#include "MySQL-Utilities.h"
#include <iostream>
#include <conio.h>

void mysqlu::DisplayFullTable(mysqlx::Table& p_Table) {
	mysqlx::RowResult result = p_Table.select("*").execute();

	std::vector<std::string> columnNames;
	for (const auto& column : result.getColumns()) {
		columnNames.push_back(column.getColumnLabel());
	}

	for (const auto& columnName : columnNames) {
		std::cout << columnName << "\t";
	}
	std::cout << std::endl;

	std::vector<mysqlx::Row> rows = result.fetchAll();
	for (const auto& row : rows) {
		for (size_t i = 0; i < columnNames.size(); i++) { 
			std::cout << row[i] << "\t"; 
		}
		std::cout << std::endl; 
	}
}

void mysqlu::ReadPassword(std::string& p_Password) {
    int i = 0, x;
    char t_Password[100], ch;

    while (true) {
        ch = _getch();
        if (ch == '\r') break;

        if (ch != 8 && ch != 13) {
            std::cout << "*";
            t_Password[i] = ch;
            i++;
        }
        else if (ch == 8) {
            std::cout << "\b \b";
            i--;
        }
    }
    t_Password[i] = '\0';

    p_Password = t_Password;
}

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