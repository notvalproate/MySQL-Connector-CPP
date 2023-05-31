#include <iostream>
#include <mysqlx/xdevapi.h>
#include "MySQL-Utilities.h"

int main(int argc, char* argv[]) {
	mysqlx::Session sess = mysqlu::Login();

	mysqlx::Schema db = sess.getSchema("test");
	mysqlx::Table mytable = db.getTable("test_table"); 

	mysqlu::DisplayFullTable(mytable);
	return 0;
}