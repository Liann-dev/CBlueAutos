#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <cctype>
#include "auth.h"

using namespace std;

static string dbUser = "app/database_user.csv";

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

	for (;;) {
		cout << "Masukkan username (atau tekan Enter untuk kembali): ";
		getline(cin, username);

		if (username == "") {
			cout << ">> Berhasil kembali ke menu utama.\n";
			return;
		}

		bool usernameValid = true;
		for (int i = 0; i < username.length(); i++) {
			if (username[i] == ' ') {
				cout << ">> Username tidak boleh mengandung spasi.\n";
				usernameValid = false;
				break;
			}

			if (!isalnum(username[i])) {
				cout << ">> Username tidak boleh mengandung simbol.\n";
				usernameValid = false;
				break;
			}
		}

		if (!usernameValid) {
			continue;
		}

		if (cekUsernameAda(username)) {
			cout << ">> Username sudah digunakan.\n";
			continue;
		}

		break;
	}

	for (;;) {
		cout << "Masukkan password: ";
		getline(cin, password);

		if (password == "") {
			cout << ">> Password tidak boleh kosong.\n";
			continue;
		}

		if (password.length() < 8) {
			cout << ">> Password minimal 8 karakter.\n";
			continue;
		}

		bool adaHuruf = false;
		bool adaAngka = false;
		bool passwordValid = true;

		for (int i = 0; i < password.length(); i++) {
			if (password[i] == ' ') {
				cout << ">> Password tidak boleh mengandung spasi.\n";
				passwordValid = false;
				break;
			}

			if (isalpha(password[i])) {
				adaHuruf = true;
			}

			if (isdigit(password[i])) {
				adaAngka = true;
			}
		}

		if (!passwordValid) {
			continue;
		}

		if (!adaHuruf || !adaAngka) {
			cout << ">> Password harus mengandung huruf dan angka.\n";
			continue;
		}

		break;
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
	if (!file.is_open()) {
		cout << ">> Database user tidak bisa dibuka.\n";
		return;
	}

	int id = userIdSelanjutnya();

	if (perluBarisBaru) {
		file << "\n";
	}
	file << id << "," << username << "," << password << ",user\n";
	file.close();

	cout << ">> Register berhasil. Silakan login.\n";
}

bool loginUser(User &userTerdaftar) {
	int sisaKesempatan = 3;

	for (; sisaKesempatan > 0; sisaKesempatan--) {
		string username, password;

		cout << "\n>>> LOGIN <<<\n";
		cout << "Masukkan username (atau tekan Enter untuk kembali): ";
		getline(cin, username);
		if (username == "") {
			cout << ">> Berhasil kembali ke menu utama.\n";
			return false;
		}

		cout << "Masukkan password: ";
		getline(cin, password);
		if (password == "") {
			cout << ">> Password tidak boleh kosong.\n";
			sisaKesempatan++;
			continue;
		}

		ifstream file(dbUser.c_str());
		if (!file.is_open()) {
			cout << ">> Database user tidak bisa dibuka.\n";
			return false;
		}

		bool loginBerhasil = false;

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
				loginBerhasil = true;
				break;
			}
		}

		file.close();

		if (loginBerhasil) {
			return true;
		}

		if (sisaKesempatan > 1) {
			cout << ">> Username atau password salah. Sisa kesempatan: " << sisaKesempatan - 1 << "\n";
		} else {
			cout << ">> Kesempatan login habis. Kembali ke menu awal.\n";
		}
	}

	return false;
}
