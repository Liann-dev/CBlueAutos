#include <iostream>
#include "auth.h"
#include "homeAdmin.h"
#include "homeUser.h"
#include "features.h"

using namespace std;
void efekNgetik(string teks, int jedaMs = 30);
void tampilkanLoading(string pesan = "Memuat", int iterasi = 3);

int main() {
    inisialisasiData(); 

    User userTerdaftar;
    int mulai = 1;

    cout << "\n";
    tampilkanLoading("Menyalakan mesin C-BlueAutos...", 4);
    efekNgetik("Memuat database kendaraan...", 40);
    efekNgetik("Sistem Siap Digunakan!", 60);
    cout << "===========================\n";

    for (; mulai == 1; ) {
        int pilihan;
        
        efekNgetik("\n=== C-BlueAutos ===", 10);
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
                tampilkanLoading("Memverifikasi kredensial...", 3);
                cout << "Login berhasil.\n";
                cout << "Login sebagai: " << userTerdaftar.role << "\n";

                if (userTerdaftar.role == "admin") {
                    menuUtamaAdmin(userTerdaftar.role);
                } else if (userTerdaftar.role == "user") {
                    menuUtama(userTerdaftar.role);
                } else {
                    cout << "Role tidak dikenali. Kembali ke menu utama.\n";
                }
            } else {
                cout << "Kembali ke menu utama.\n"; 
            }
        } else if (pilihan == 2) {
            registerUser();
        } else if (pilihan == 3) {
            efekNgetik("Menutup program... Sampai jumpa!", 40);
            mulai = 0;
        } else {
            cout << "Pilihan tidak valid.\n";
        }
    }
    return 0;
} 