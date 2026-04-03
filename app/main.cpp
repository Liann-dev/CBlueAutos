#include <iostream>
#include "auth.h"

using namespace std;

int main() {

    User userTerdaftar;
    int mulai = 1;

    for (; mulai == 1; ) {
        int pilihan;
        cout << "\n=== C-BlueAutos ===\n";
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
                cout << "Kembali ke menu utama.\n";
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