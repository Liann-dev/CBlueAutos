#include <iostream>
#include <string>
#include <cctype> 
#include "homeAdmin.h"
#include "features.h"

using namespace std;

void menuUtamaAdmin(string role) {
    string inputBuffer;
    bool tetapDiHome = true;

    while (tetapDiHome) {
        #ifdef _WIN32
            system("cls");
        #else
            system("clear");
        #endif

        cout << "\n==========================================" << endl;
        cout << "         CBLUEAUTOS - ADMIN MENU          " << endl;
        cout << "==========================================" << endl;
        cout << " 1. Tambah Stok Mobil Baru" << endl;
        cout << " 2. Update Data Mobil" << endl;
        cout << " 3. Hapus Stok Mobil" << endl;
        cout << " 4. Search Stok" << endl;
        cout << " 5. Filter Stok" << endl;
        cout << " 6. Lihat Inventaris (Katalog)" << endl;
        cout << " 7. Keluar" << endl;
        cout << "==========================================" << endl;
        cout << " Pilih opsi (1-7): ";
        
        getline(cin, inputBuffer);
        
        if (inputBuffer.empty()) continue; 

        int pilihan = -1;
        
        // --- LOGIKA PENGGANTI TRY-CATCH ---
        // Cek apakah input hanya 1 karakter dan berupa angka
        if (inputBuffer.length() == 1 && isdigit(inputBuffer[0])) {
            pilihan = inputBuffer[0] - '0'; // Mengubah karakter '1'-'7' menjadi angka integer 1-7
        }
        
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
            cout << "\n[!] Pilihan tidak valid. Tekan Enter untuk mengulang..."; 
            string pauseBuffer;
            getline(cin, pauseBuffer);
        }
    }
}