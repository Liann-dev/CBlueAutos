#include <iostream>
#include <string>
#include <algorithm>
#include <iomanip>
#include "features.h"

using namespace std;

extern string keHurufKecil(string teks);

void cariMobil() {
    string key;

    cout << "\n=== PENCARIAN KOLEKSI MOBIL ===\n";
    cout << "Masukkan Model ('0' untuk semua, atau tekan Enter untuk kembali): ";
    
    if (cin.peek() == '\n' || cin.peek() == '\r') {
        cin.ignore();
    }
    

    getline(cin, key);
    if (key.empty()) {
        return;
    }
    
    string keyKecil = keHurufKecil(key);

    #ifdef _WIN32
        system("cls");
    #else
        system("clear");
    #endif

    cout << "\n" << setfill('=') << setw(105) << "=" << setfill(' ') << endl;
    cout << left << " " << setw(5) << "ID" << setw(15) << "MERK" << setw(20) << "MODEL" 
         << setw(8) << "TAHUN" << setw(15) << "KONDISI" << setw(12) << "TIPE" 
         << setw(12) << "TRANSMISI" << "BENUA" << endl;
    cout << setfill('-') << setw(105) << "-" << setfill(' ') << endl;

    int counter = 0;

    for (Kategori* currKat = headKategori; currKat != nullptr; currKat = currKat->next) {
        
        for (Mobil* temp = currKat->head; temp != nullptr; temp = temp->next) {
            string modelKecil = keHurufKecil(temp->Model);

            if (keyKecil == "0" || modelKecil.find(keyKecil) != string::npos) {
                counter++;
                
                string modelTeks = temp->Model;
                if (modelTeks.length() > 18) modelTeks = modelTeks.substr(0, 15) + "...";

                cout << left << " " << setw(5) << temp->id << setw(15) << currKat->NamaMerk 
                     << setw(20) << modelTeks << setw(8) << temp->Tahun << setw(15) << temp->Kondisi 
                     << setw(12) << temp->Tipe << setw(12) << temp->Transmisi << temp->Benua << endl;
            }
        }
    }

    if (counter > 0) {
        cout << setfill('=') << setw(105) << "=" << setfill(' ') << endl;
        cout << "Berhasil menemukan " << counter << " unit." << endl;
    } else {
        cout << setfill('=') << setw(105) << "=" << setfill(' ') << endl;
        cout << "[!] Tidak ada mobil yang sesuai dengan kriteria tersebut." << endl;
    }

    cout << "\nTekan Enter untuk kembali..." << endl;
    string pauseBuffer;
    getline(cin, pauseBuffer);
}