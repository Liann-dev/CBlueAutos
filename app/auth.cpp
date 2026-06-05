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

bool validasiUsernameStandarIndustri(string username) {
    if (username.length() < 3 || username.length() > 20) return false;
    if (!isalnum(username.front()) || !isalnum(username.back())) return false;

    for (int i = 0; i < username.length(); i++) {
        char c = username[i];

        // Jika huruf atau angka, aman
        if (isalnum(c)) continue;

        // Jika spasi, langsung tolak
        if (c == ' ') return false;

        // Jika karakter adalah _, -, atau . (Diizinkan dengan syarat)
        if (c == '_' || c == '-' || c == '.') {
            // Syarat: Tidak boleh berurutan (contoh: a__b akan ditolak)
            if (i > 0 && !isalnum(username[i - 1])) {
                return false; 
            }
            continue;
        }
        // Jika ada simbol lain (!, @, #, $, dll), tolak
        return false;
    }

    return true; 
}

void registerUser() {
    string username, password;

    #ifdef _WIN32
        system("cls");
    #else
        system("clear");
    #endif

    cout << "\n======================================================\n";
    cout << "                 REGISTER AKUN BARU                   \n";
    cout << "======================================================\n";
    cout << " SYARAT USERNAME:\n";
    cout << " - Panjang 3-20 karakter.\n";
    cout << " - Gunakan huruf, angka, underscore (_), titik (.), atau strip (-).\n";
    cout << " - TANPA spasi. Simbol tidak di awal, akhir, atau berurutan.\n";
    cout << "======================================================\n\n";

    while (true) {
        cout << "Masukkan Username (atau Enter untuk batal): ";
        getline(cin, username);
        
        if (username == "") return;

        bool valid = true;
        
        if (!validasiUsernameStandarIndustri(username)) {
            cout << ">> [!] Username tidak memenuhi syarat di atas. Silakan coba lagi.\n\n";
            valid = false;
        }

        if (valid && cekUsernameAda(username)) {
            cout << ">> [!] Username sudah digunakan. Silakan cari nama lain.\n\n";
            valid = false;
        }
        
        if (valid) {
            cout << ">> [OK] Username Terdaftar!\n\n";
            break;
        }
    }

    cout << "======================================================\n";
    cout << " SYARAT PASSWORD:\n";
    cout << " - Minimal 8 karakter.\n";
    cout << " - Harus mengandung kombinasi huruf dan angka.\n";
    cout << " - TANPA spasi.\n";
    cout << "======================================================\n\n";

    while (true) {
        cout << "Masukkan Password: ";
        password = getHiddenPassword();

        bool adaHuruf = false, adaAngka = false, valid = true;
        if (password.length() < 8) {
            cout << ">> [!] Password minimal 8 karakter.\n\n";
            continue;
        }
        for (char c : password) {
            if (isspace(c)) valid = false;
            if (isalpha(c)) adaHuruf = true;
            if (isdigit(c)) adaAngka = true;
        }
        if (!valid || !adaHuruf || !adaAngka) {
            cout << ">> [!] Password harus mengandung huruf, angka, dan tanpa spasi.\n\n";
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
        cout << "\n>> [SUKSES] Register berhasil! Silakan login.\n";
        
        cout << "Tekan Enter untuk kembali ke menu...";
        string pauseBuffer;
        getline(cin, pauseBuffer);
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