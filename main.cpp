#include <iostream>
#include "app/auths/auth.h"

using namespace std;

struct Mobil {
    string merk;
    string model;
    int Tahun;
    string kondisi;
    Mobil* next;
};

Mobil* loadCSV(string path);
void saveCSV(string path, Mobil* head);

void tampilkanKatalog(Mobil* head);
void tambahMobilAdmin(Mobil*& head);
void updateMobilAdmin(Mobil* head);
void hapusMobilAdmin(Mobil*& head);

int main() {

    User userTerdaftar;
    string path = "data/Admin/data.csv";

    while (true) {
        int pilihan;

        cout << "\n=== CAR SHOWROOM ===\n";
        cout << "1. Login\n";
        cout << "2. Register\n";
        cout << "3. Keluar\n";
        cout << "Pilih: ";

        if (!(cin >> pilihan)) {
            cin.clear();
            cin.ignore(10000, '\n');
            cout << "Input harus angka!\n";
            continue;
        }
        cin.ignore();

        if (pilihan == 1) {

            if (loginUser(userTerdaftar)) {

                cout << "Login sebagai: " << userTerdaftar.role << endl;

                Mobil* head = loadCSV(path);

                int menu;
                do {
                    cout << "\n=== MENU SHOWROOM ===\n";
                    cout << "1. Lihat mobil\n";

                    if (userTerdaftar.role == "admin") {
                        cout << "2. Tambah mobil\n";
                        cout << "3. Update mobil\n";
                        cout << "4. Hapus mobil\n";
                    }

                    cout << "0. Logout\n";
                    cout << "Pilih: ";

                    if (!(cin >> menu)) {
                        cin.clear();
                        cin.ignore(10000, '\n');
                        cout << "Input harus angka!\n";
                        continue;
                    }

                    switch (menu) {
                        case 1:
                            tampilkanKatalog(head);
                            break;

                        case 2:
                            if (userTerdaftar.role == "admin") {
                                tambahMobilAdmin(head);
                                saveCSV(path, head);
                            }
                            break;

                        case 3:
                            if (userTerdaftar.role == "admin") {
                                tampilkanKatalog(head);
                                updateMobilAdmin(head);
                                saveCSV(path, head);
                            }
                            break;

                        case 4:
                            if (userTerdaftar.role == "admin") {
                                tampilkanKatalog(head);
                                hapusMobilAdmin(head);
                                saveCSV(path, head);
                            }
                            break;
                    }

                } while (menu != 0);

            } else {
                cout << "Login gagal!\n";
            }

        } else if (pilihan == 2) {
            registerUser();
        } else {
            break;
        }
    }

    return 0;
}