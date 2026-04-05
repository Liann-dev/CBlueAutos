#include <iostream>
#include <string>
#include "homeAdmin.h"
#include "features.h"


using namespace std;

void menuUtamaAdmin(string role) {
    int pilihan;
    bool tetapDiHome = true;

    while (tetapDiHome) {
        cout << "\n==========================================" << endl;
        cout << "       CBLUEAUTOS - ADMIN MENU        " << endl;
        cout << "==========================================" << endl;
        cout << "1. Tambah Stok Mobil Baru" << endl;
        cout << "2. Update Data Mobil" << endl;
        cout << "3. Hapus Stok Mobil" << endl;
        cout << "4. Search Stok" << endl;
        cout << "5. Filter Stok" << endl;
        cout << "6. Lihat Inventaris (Katalog)" << endl;
        cout << "7. Keluar" << endl;
        cout << " Pilih opsi (1-7): ";
        cin >> pilihan;
        
        if (pilihan == 1){
            tambahMobilAdmin();

        } else if (pilihan == 2){
            updateMobilAdmin();

        } else if (pilihan == 3){
            hapusMobilAdmin();

        } else if (pilihan == 4){
            cariMobilAdmin();   

        } else if (pilihan == 5){
            filterMobilAdmin(); 

        } else if (pilihan == 6){
            tampilkanKatalogAdmin();

        } else if (pilihan == 7){
            cout << "\nLogging out...\n";
            tetapDiHome = false;

        } else {
           cout << "Pilihan tidak valid.\n"; 
        }
    }
}