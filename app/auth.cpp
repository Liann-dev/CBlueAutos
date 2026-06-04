#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <cctype>
#include <conio.h> 
#include "auth.h"

using namespace std;
static string dbUser = "database_user.csv"; 

string getHiddenPassword() {
    string password = "";
    char ch;
    while (true) {
        ch = _getch();
        if (ch == '\r' || ch == '\n') { 
            cout << endl;
            break;
        } else if (ch == '\b') { 
            if (!password.empty()) {
                password.pop_back();
                cout << "\b \b";
            }
        } else if (ch >= 32) { 
            password.push_back(ch);
            cout << '*';
        }
    }
    return password;
}

bool cekUsernameAda(string username) {
    ifstream file(dbUser.c_str());
    string line;
    while (getline(file, line)) {
        stringstream ss(line);
        string id, fileUsername;
        getline(ss, id, ',');
        getline(ss, fileUsername, ',');
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
    string line;
    int lastId = 0;
    while (getline(file, line)) {
        stringstream ss(line);
        string id;
        if (getline(ss, id, ',')) {
            try { lastId = stoi(id); } catch (...) {}
        }
    }
    file.close();
    return lastId + 1;
}

void registerUser() {
    string username, password;
    cout << "\n>>> REGISTER AKUN <<<\n";

    while (true) {
        cout << "Masukkan username (atau Enter untuk kembali): ";
        getline(cin, username);
        if (username == "") return;

        bool valid = true;
        for (char c : username) {
            if (isspace(c) || !isalnum(c)) {
                cout << ">> Username hanya boleh huruf dan angka tanpa spasi.\n";
                valid = false;
                break;
            }
        }
        if (valid && cekUsernameAda(username)) {
            cout << ">> Username sudah digunakan.\n";
            valid = false;
        }
        if (valid) break;
    }

    while (true) {
        cout << "Masukkan password: ";
        password = getHiddenPassword();

        bool adaHuruf = false, adaAngka = false, valid = true;
        if (password.length() < 8) {
            cout << ">> Password minimal 8 karakter.\n";
            continue;
        }
        for (char c : password) {
            if (isspace(c)) valid = false;
            if (isalpha(c)) adaHuruf = true;
            if (isdigit(c)) adaAngka = true;
        }
        if (!valid || !adaHuruf || !adaAngka) {
            cout << ">> Password harus mengandung huruf, angka, dan tanpa spasi.\n";
            continue;
        }
        break;
    }

    ofstream file(dbUser.c_str(), ios::app);
    if (file.is_open()) {
        file << userIdSelanjutnya()
            << "," << username
            << "," << password
            << ",user,true,0\n";
            
        file.close();
        cout << ">> Register berhasil!\n";
    }
}

bool loginUser(User &userTerdaftar) {
     for (int sisa = 3; sisa > 0; sisa--) {

        string username, password;

        cout << "\n>>> LOGIN (Sisa percobaan: " << sisa << ") <<<\n";
        cout << "Username (Tekan Enter untuk kembali): ";
        getline(cin, username);

        if (username.empty())
            return false;

        cout << "Password: ";
        password = getHiddenPassword();

        ifstream file(dbUser.c_str());

        if (!file.is_open()) {
            cout << "Gagal membuka database user.\n";
            return false;
        }

        string line;
        string dataBaru = "";
        bool loginBerhasil = false;

        // simpan header
        getline(file, line);
        dataBaru += line + "\n";

        while (getline(file, line)) {

            if (line.empty())
                continue;

            stringstream ss(line);

            string id;
            string fUser;
            string fPass;
            string fRole;
            string fStatus;
            string fLoginCount;

            getline(ss, id, ',');
            getline(ss, fUser, ',');
            getline(ss, fPass, ',');
            getline(ss, fRole, ',');
            getline(ss, fStatus, ',');
            getline(ss, fLoginCount, ',');

            if (fUser == username && fPass == password) {

                loginBerhasil = true;

                int loginCount = stoi(fLoginCount);

                loginCount++;

                if (loginCount > 1)
                    fStatus = "false";
                else
                    fStatus = "true";

                fLoginCount = to_string(loginCount);

                userTerdaftar.id = stoi(id);
                userTerdaftar.username = fUser;
                userTerdaftar.role = fRole;
                userTerdaftar.login_count = fLoginCount;
            }

            dataBaru += id + "," +
                        fUser + "," +
                        fPass + "," +
                        fRole + "," +
                        fStatus + "," +
                        fLoginCount + "\n";
        }

        file.close();

        if (loginBerhasil) {

            ofstream simpan(dbUser.c_str());

            simpan << dataBaru;
            simpan.close();

            return true;
        }

        cout << ">> Username atau password salah.\n";
    }

    return false;
}