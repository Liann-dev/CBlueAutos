#include <iostream>
#include <string>
#include <algorithm>
#include <iomanip>
#include "features.h"

using namespace std;


void searchFilterAdmin() {
    string key;
    string filterKondisi;

    cout << "\n=== MANAJEMEN STOK (SEARCH) ===\n";
    cout << "Cari Merk/Model: ";
    getline(cin >> ws, key);
    string keyKecil = keHurufKecil(key);

    cout << "Filter Kondisi (Baru/Bekas/0): ";
    getline(cin, filterKondisi);
    string kondKecil = keHurufKecil(filterKondisi);

    cout << "\n" << setfill('=') << setw(75) << "=" << endl;
    cout << left << setw(5) << "ID" << setw(15) << "MERK" << setw(20) << "MODEL" << setw(10) << "THN" << "KONDISI" << endl;
    cout << setfill('-') << setw(75) << "-" << setfill(' ') << endl;

    int counter = 0;
    
    for (Kategori* currKat = headKategori; currKat != nullptr; currKat = currKat->next) {
        string merkKecil = keHurufKecil(currKat->NamaMerk);

        for (Mobil* temp = currKat->head; temp != nullptr; temp = temp->next) {
            string modelKecil = keHurufKecil(temp->Model);
            string unitKondKecil = keHurufKecil(temp->Kondisi);

            bool cocokKeyword = (keyKecil == "0" || keyKecil == "" || 
                                 merkKecil.find(keyKecil) != string::npos || 
                                 modelKecil.find(keyKecil) != string::npos);
            bool cocokKondisi = (kondKecil == "0" || unitKondKecil == kondKecil);

            if (cocokKeyword && cocokKondisi) {
                counter++;
                cout << left << setw(5) << temp->id 
                     << setw(15) << currKat->NamaMerk 
                     << setw(20) << temp->Model 
                     << setw(10) << temp->Tahun 
                     << temp->Kondisi << endl;
            }
        }
    }

    if (counter > 0) {
        cout << setfill('=') << setw(75) << "=" << setfill(' ') << endl;
        cout << "Total aset ditemukan: " << counter << " unit." << endl;
    } else {
        cout << "\n[!] Data tidak ditemukan dalam database." << endl;
    }
}