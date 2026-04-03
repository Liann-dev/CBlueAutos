#include <iostream>
#include <fstream>
#include <sstream>
#include <string>

using namespace std;

struct User {
    int id;
    string username;
    string password;
    string role;
};

string dbUser = "data/database_user.csv";

bool cekfile() {
    ifstream file(dbUser.c_str());
    return file.good();
}

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

int main() {

    User userTerdaftar;
    int mulai = 1;

    for (; mulai == 1; ) {
        int pilihan;
        cout << "\n=== CAR SHOWROOM ===\n";
        cout << "1. Login\n";
        cout << "2. Register\n";
        cout << "3. Keluar\n";
        cout << "Pilih menu: ";

        if (!(cin >> pilihan)) {
            cin.clear();
            cin.ignore(10000, '\n');
            cout << "Input harus angka menu.\n";
            continue;
        }
        cin.ignore(10000, '\n');

        if (pilihan == 1) {
            bool loginBerhasil = loginUser(userTerdaftar);

            if (loginBerhasil) {
                cout << "Login berhasil.\n";
                cout << "Login sebagai: " << userTerdaftar.role << "\n";
            } else {
                cout << "Username atau password salah.\n";
            }
        } else if (pilihan == 2) {
            registerUser();
        } else if (pilihan == 3) {
                cout << "Program selesai.\n";
                mulai = 0;
        } else {
            cout << "Pilihan tidak valid.\n";
        }
    }

    return 0;
}