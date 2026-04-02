#include <iostream>
#include <fstream>
#include <sstream>
#include <string>

// Memanggil header navigasi menu
#include "app/home/user/home.h" 
#include "app/home/admin/home.h" 
#include "app/features/features.h"

using namespace std;

// Struct User untuk menampung data sesi login
struct User {
    int id;
    string username;
    string password;
    string role;
};

string dbUser = "data/database_user.csv";

// Fungsi untuk memastikan folder data dan file csv tersedia
bool cekfile() {
    ifstream file(dbUser.c_str());
    return file.good();
}

// Fungsi cek duplikasi username saat register
bool cekUsernameAda(string username) {
    ifstream file(dbUser.c_str());
    string line;
    while (getline(file, line)) {
        if (line.empty()) continue;
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

// Fungsi auto-increment ID untuk user baru
int userIdSelanjutnya() {
    ifstream file(dbUser.c_str());
    int lastId = 0;
    string line;

    while (getline(file, line)) {
        if (line.empty()) continue;
        stringstream ss(line);
        string id;
        getline(ss, id, ',');
        if(!id.empty()) lastId = stoi(id);
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

    // Cek apakah perlu baris baru (newline) di akhir file
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
    if (perluBarisBaru) file << "\n";
    
    file << userIdSelanjutnya() << "," << username << "," << password << ",user";
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
    string line;

    while (getline(file, line)) {
        if (line.empty()) continue;
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
    inisialisasiData();

    User userTerdaftar;
    bool programJalan = true;

    while (programJalan) {
        int pilihan;
        cout << "\n==============================\n";
        cout << "      SHOWROOM MOBIL UPI      \n";
        cout << "==============================\n";
        cout << "1. Login\n";
        cout << "2. Register\n";
        cout << "3. Keluar\n";
        cout << "Pilih menu: ";

        if (!(cin >> pilihan)) {
            cin.clear();
            cin.ignore(10000, '\n');
            cout << "Input harus berupa angka!\n";
            continue;
        }
        cin.ignore(10000, '\n'); 

        if (pilihan == 1) {
            if (loginUser(userTerdaftar)) {
                cout << "\nLogin Berhasil! Selamat Datang, " << userTerdaftar.username << ".\n";
                
                // 2. Percabangan Menu berdasarkan Role
                if (userTerdaftar.role == "admin") {
                    menuUtamaAdmin(userTerdaftar.role); // Masuk ke folder admin
                } else {
                    menuUtama(userTerdaftar.role);      // Masuk ke folder user
                }
            } else {
                cout << "Username atau password salah!\n";
            }
        } else if (pilihan == 2) {
            registerUser();
        } else if (pilihan == 3) {
            cout << "Terima kasih telah menggunakan layanan kami.\n";
            programJalan = false;
        } else {
            cout << "Pilihan tidak tersedia.\n";
        }
    }

    return 0;
}