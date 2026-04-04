#include <iostream>
#include <string>
#include <algorithm>
#include <iomanip>
#include "features.h"

using namespace std;

extern Kategori showroom[3];

// Fungsi pembantu untuk pencarian case-insensitive
string keHurufKecil(string teks) {
    transform(teks.begin(), teks.end(), teks.begin(), ::tolower);
    return teks;
}

void cariMobil() {
    string key;
    int tahunMin;

    cout << "\n=== PENCARIAN KOLEKSI MOBIL ===\n";
    cout << "Masukkan Merk atau Model (atau '0' untuk semua): ";
    getline(cin >> ws, key);
    string keyKecil = keHurufKecil(key);

    cout << "Masukkan minimal tahun (atau '0'): ";
    cin >> tahunMin;

    cout << "\n" << setfill('=') << setw(70) << "=" << endl;
    cout << left << setw(15) << "MERK" << setw(20) << "MODEL" << setw(10) << "TAHUN" << "KONDISI" << endl;
    cout << setfill('-') << setw(70) << "-" << setfill(' ') << endl;

    int counter = 0;
    for (int i = 0; i < 3; i++) {
        // Patokan utama: Nama Merk dari kategori
        string merkKecil = keHurufKecil(showroom[i].NamaMerk);
        Mobil* temp = showroom[i].head;

        while (temp != nullptr) {
            string modelKecil = keHurufKecil(temp->Model);

            // Logika filter: Cek kecocokan merk, model, dan tahun
            if ((keyKecil == "0" || keyKecil == "" || merkKecil.find(keyKecil) != string::npos || modelKecil.find(keyKecil) != string::npos)
                && (tahunMin == 0 || temp->Tahun >= tahunMin)) {
                
                counter++;
                cout << left << setw(15) << showroom[i].NamaMerk 
                     << setw(20) << temp->Model 
                     << setw(10) << temp->Tahun 
                     << temp->Kondisi << endl;
            }
            temp = temp->next;
        }
    }

    if (counter > 0) {
        cout << setfill('=') << setw(70) << "=" << setfill(' ') << endl;
        cout << "Berhasil menemukan " << counter << " unit." << endl;
    } else {
        cout << "\n[!] Tidak ada mobil yang sesuai dengan kriteria tersebut." << endl;
    }
}