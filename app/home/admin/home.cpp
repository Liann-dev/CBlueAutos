#include <iostream>
#include <string>
#include "home.h"
#include "../../features/features.h"


using namespace std;

void menuUtamaAdmin(string role) {
    int pilihan;
    bool tetapDiHome = true;

    while (tetapDiHome) {
        cout << "\n=== SISTEM MANAJEMEN (ADMIN ONLY) ===" << endl;
        cout << "1. Tambah Stok Mobil Baru" << endl;
        cout << "2. Update Data/Harga Mobil" << endl;
        cout << "3. Hapus Unit (Sold Out)" << endl;
        cout << "4. Cari & Filter Stok" << endl;
        cout << "5. Lihat Laporan Inventaris (Katalog)" << endl;
        cout << "6. Keluar" << endl;
        cout << " Pilih opsi (1-6): ";
        cin >> pilihan;
        
        if (pilihan == 1){
            tambahMobilAdmin();
        
        } else if (pilihan == 2){
             updateMobilAdmin();
        } else if (pilihan == 3){
             hapusMobilAdmin();
        } else if (pilihan == 4){
            searchFilterAdmin();
        } else if (pilihan == 5){
            tampilkanKatalogAdmin();
        } else if (pilihan == 6){
            cout << "\nLogging out... Kembali ke menu utama.\n";
            tetapDiHome = false; 
        } else {
           cout << "Pilihan tidak valid.\n"; 
        }
    }
}