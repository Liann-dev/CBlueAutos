#include <iostream>
#include <string>
#include "homeUser.h"
#include "features.h"

using namespace std;

void menuUtama(string role) {
    int pilihan;
    bool tetapDiHome = true;

    while (tetapDiHome) {
        cout << "\n==========================================" << endl;
        cout << "       CBLUEAUTOS - USER MENU          " << endl;
        cout << "==========================================" << endl;
        cout << " 1. Lihat Semua Koleksi (Katalog)         " << endl;
        cout << " 2. Search                                 " << endl;
        cout << " 3. Filter                                 " << endl;
        cout << " 4. Logout (Kembali ke Login)             " << endl;
        cout << "==========================================" << endl;
        cout << " Pilih opsi (1-3): ";
        cin >> pilihan;
        
        if (pilihan == 1){
            tampilkanKatalog();
        
        } else if (pilihan == 2){
            cariMobil();
          
        } else if (pilihan == 3){
             filterMobil();
        }else if (pilihan == 4){
            cout << "\nLogging out... Kembali ke menu utama.\n";
            tetapDiHome = false; 
        } else {
            cout << "Pilihan tidak valid.\n";
        }
    }
}