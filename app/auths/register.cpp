#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include "auth.h"

using namespace std;

static string dbUser = "data/database_user.csv";

bool cekUsernameAda(string username) {
	ifstream file(dbUser.c_str());
	for (string line; getline(file, line); ) {
		stringstream ss(line);
		string id, fileUsername, filePassword, fileRole;

		getline(ss, id, ',');
		getline(ss, fileUsername, ',');
		getline(ss, filePassword, ',');
		getline(ss, fileRole, ',');

		if (fileUsername == username) {
			file.close();
			return true;
		}
	}

	file.close();
	return false;
}

int userIdSelanjutnya() {
	ifstream file(dbUser.c_str());
	int lastId = 0;

	for (string line; getline(file, line); ) {
		stringstream ss(line);
		string id;

		getline(ss, id, ',');
		lastId = stoi(id);
	}

	file.close();
	return lastId + 1;
}

void registerUser() {
	string username, password;

	cout << "\n>>> REGISTER AKUN <<<\n";
	cout << "Masukkan username: ";
	getline(cin, username);
	cout << "Masukkan password: ";
	getline(cin, password);

	if (username == "" || password == "") {
		cout << "Username dan password tidak boleh kosong.\n";
		return;
	}

	if (cekUsernameAda(username)) {
		cout << "Username sudah digunakan.\n";
		return;
	}

	bool perluBarisBaru = false;
	ifstream cekAkhir(dbUser.c_str(), ios::binary);
	if (cekAkhir.good()) {
		cekAkhir.seekg(0, ios::end);
		if (cekAkhir.tellg() > 0) {
			cekAkhir.seekg(-1, ios::end);
			char karakterTerakhir;
			cekAkhir.get(karakterTerakhir);

			if (karakterTerakhir != '\n' && karakterTerakhir != '\r') {
				perluBarisBaru = true;
			}
		}
	}
	cekAkhir.close();

	ofstream file(dbUser.c_str(), ios::app);
	int id = userIdSelanjutnya();

	if (perluBarisBaru) {
		file << "\n";
	}
	file << id << "," << username << "," << password << ",user\n";
	file.close();

	cout << "Register berhasil. Silakan login.\n";
}
