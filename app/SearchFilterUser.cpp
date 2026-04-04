#include <iostream>
#include <string>
#include <algorithm>
#include <iomanip>
#include "features.h"

using namespace std;

extern Kategori showroom[3];

string keHurufKecil(string teks) {
    transform(teks.begin(), teks.end(), teks.begin(), ::tolower);
    return teks;
}

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
    for (int i = 0; i < 3; i++) {
        string merkKecil = keHurufKecil(showroom[i].NamaMerk);
        Mobil* temp = showroom[i].head;

        while (temp != nullptr) {
            string modelKecil = keHurufKecil(temp->Model);

            if (keyKecil == "0" || keyKecil == "" || modelKecil.find(keyKecil) != string::npos) {
                counter++;
                cout << left
                     << setw(5)  << temp->id
                     << setw(12) << showroom[i].NamaMerk
                     << setw(22) << temp->Model
                     << setw(8)  << temp->Tahun
                     << temp->Kondisi << endl;
            }
            temp = temp->next;
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