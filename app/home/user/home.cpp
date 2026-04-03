#include <iostream>
#include <string>
#include "home.h"
#include "../../features/features.h"

using namespace std;

void menuUtama(string role) {
    int pilihan;
    bool tetapDiHome = true;

    while (tetapDiHome) {
        cout << "\n==========================================" << endl;
        cout << "       SHOWROOM MOBIL - USER MENU         " << endl;
        cout << "==========================================" << endl;
        cout << " 1. Lihat Semua Koleksi (Katalog)         " << endl;
        cout << " 2. Cari & Filter Spesifik                " << endl;
        cout << " 3. Logout (Kembali ke Login)             " << endl;
        cout << "==========================================" << endl;
        cout << " Pilih opsi (1-3): ";
        cin >> pilihan;
        
        if (pilihan == 1){
            tampilkanKatalog();
        
        } else if (pilihan == 2){
            cariMobil();
          
        } else if (pilihan == 3){
            cout << "\nLogging out... Kembali ke menu utama.\n";
            tetapDiHome = false; 
        } else {
            cout << "Pilihan tidak valid.\n";
        }
    }
}