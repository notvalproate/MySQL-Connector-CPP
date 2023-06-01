#include <iostream>
#include <mysqlx/xdevapi.h>
#include "MySQL-Utilities.h"
#include "CRUD.h"

void Delete(CRUD& p_cursor) {
	int ans;

	while (true) {
		std::cout << "##### DELETE #####\n1. SCHEMA\n2. TABLE\n3. ROW\n4. BACK\n##################\n\nENTER OPTION: ";
		std::cin >> ans;
		system("cls");

		switch (ans) {
		case 1:
			p_cursor.DeleteSchema();
			break;
		case 2:
			p_cursor.DeleteTable();
			break;
		case 3:
			p_cursor.DeleteRows();
			break;
		case 4:
			return;
		default:
			system("cls");
			std::cout << "Enter a valid option number!\n\n";
			break;
		}
	}
}

void Create(CRUD& p_cursor) {
	int ans;

	while (true) {
		std::cout << "##### CREATE #####\n1. SCHEMA\n2. TABLE\n3. ROW\n4. BACK\n##################\n\nENTER OPTION: ";
		std::cin >> ans;
		system("cls");

		switch (ans) {
		case 1:
			p_cursor.CreateDatabase();
			break;
		case 2:
			p_cursor.CreateTable();
			break;
		case 3:
			p_cursor.InsertInto();
			break;
		case 4:
			return;
		default:
			system("cls");
			std::cout << "Enter a valid option number!\n\n";
			break;
		}
	}
}

void Menu(mysqlx::Session& p_sess) {
	CRUD cursor(&p_sess);
	bool exit = true;
	int ans;

	while (exit) {
		std::cout << "##### MENU #####\n1. CREATE\n2. READ\n3. UPDATE\n4. DELETE\n5. EXIT\n################\n\nENTER OPTION: ";
		std::cin >> ans;
		system("cls");

		switch (ans) {
		case 1:
			Create(cursor);
			break;
		case 2:
			cursor.DisplayTable();
			break;
		case 3:
			cursor.Update();
			break;
		case 4:
			Delete(cursor);
			break;
		case 5:
			exit = false;
			break;
		default:
			system("cls");
			std::cout << "Enter a valid option number!\n\n";
			break;
		}
	}
}

int main(int argc, char* argv[]) {
	mysqlx::Session sess = mysqlu::Login();

	Menu(sess);

	return 0;
}