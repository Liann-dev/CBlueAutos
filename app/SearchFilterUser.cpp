#include <iostream>
#include <string>
#include <algorithm>
#include <iomanip>
#include "features.h"

using namespace std;

void cariMobil() {
    string key;

    cout << "\n=== PENCARIAN KOLEKSI MOBIL ===\n";
    cout << "Masukkan Model (atau '0' untuk semua): ";
    getline(cin >> ws, key);
    string keyKecil = keHurufKecil(key);

    // ── Clear screen setelah input selesai ────────────────
    #ifdef _WIN32
        system("cls");
    #else
        system("clear");
    #endif

    cout << "\n" << setfill('=') << setw(70) << "=" << setfill(' ') << endl;
    cout << left
         << setw(5)  << "ID"
         << setw(12) << "MERK"
         << setw(22) << "MODEL"
         << setw(8)  << "TAHUN"
         << "KONDISI" << endl;
    cout << setfill('-') << setw(70) << "-" << setfill(' ') << endl;

    int counter = 0;

    // Iterasi dinamis menggunakan FOR untuk Kategori (Merk)
    for (Kategori* currKat = headKategori; currKat != nullptr; currKat = currKat->next) {
        
        // Iterasi menggunakan FOR untuk Mobil di dalam Kategori tersebut
        for (Mobil* temp = currKat->head; temp != nullptr; temp = temp->next) {
            string modelKecil = keHurufKecil(temp->Model);

            // Logika pencarian tetap dipertahankan
            if (keyKecil == "0" || keyKecil == "" || modelKecil.find(keyKecil) != string::npos) {
                counter++;
                cout << left
                     << setw(5)  << temp->id
                     << setw(12) << currKat->NamaMerk 
                     << setw(22) << temp->Model
                     << setw(8)  << temp->Tahun
                     << temp->Kondisi << endl;
            }
        }
    }

    if (counter > 0) {
        cout << setfill('=') << setw(70) << "=" << setfill(' ') << endl;
        cout << "Berhasil menemukan " << counter << " unit." << endl;
    } else {
        cout << setfill('=') << setw(70) << "=" << setfill(' ') << endl;
        cout << "[!] Tidak ada mobil yang sesuai dengan kriteria tersebut." << endl;
    }
}