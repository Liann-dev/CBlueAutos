#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include "auth.h"

using namespace std;

string dbUser = "data/database_user.csv";

bool loginUser(User &userTerdaftar) {
	string username, password;

	cout << "\n>>> LOGIN <<<\n";
	cout << "Masukkan username: ";
	getline(cin, username);
	cout << "Masukkan password: ";
	getline(cin, password);

	ifstream file(dbUser.c_str());

	for (string line; getline(file, line); ) {
		stringstream ss(line);
		string id, fileUsername, filePassword, fileRole;

		getline(ss, id, ',');
		getline(ss, fileUsername, ',');
		getline(ss, filePassword, ',');
		getline(ss, fileRole, ',');

		if (fileUsername == username && filePassword == password) {
			userTerdaftar.id = stoi(id);
			userTerdaftar.username = fileUsername;
			userTerdaftar.password = filePassword;
			userTerdaftar.role = fileRole;

			file.close();
			return true;
		}
	}

	file.close();
	return false;
}
