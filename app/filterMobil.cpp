#include <iostream>
#include <string>
#include <algorithm>
#include <iomanip>
#include <vector>
#include <set>
#include <fstream>
#include <sstream>
#include "features.h"

using namespace std;

extern Kategori showroom[3];

vector<string> ambilOpsiDinamis(int indeksKolom) {
    set<string> dataUnik;
    ifstream file("database_mobil.csv");
    string line;

    if (!file.is_open()) return {};

    getline(file, line); 
    while (getline(file, line)) {
        stringstream ss(line);
        string segmen;
        int kolomSekarang = 0;
        
        while (getline(ss, segmen, ',')) {
            if (kolomSekarang == indeksKolom && !segmen.empty()) {
                dataUnik.insert(segmen);
            }
            kolomSekarang++;
        }
    }
    file.close();
    return vector<string>(dataUnik.begin(), dataUnik.end());
}

void filterMobil() {
    while (true) {
        int pilihanFilter;
        cout << "\n========================================" << endl;
        cout << "           FILTER KATALOG MOBIL         " << endl;
        cout << "========================================" << endl;
        cout << "  [1] Berdasarkan Tahun" << endl;
        cout << "  [2] Berdasarkan Merk" << endl;
        cout << "  [3] Berdasarkan Kondisi" << endl;
        cout << "  [0] Keluar ke Beranda" << endl;
        cout << "----------------------------------------" << endl;
        cout << "Pilihan: ";
        
        if (!(cin >> pilihanFilter)) {
            cin.clear();
            cin.ignore(1000, '\n');
            continue;
        }

        if (pilihanFilter == 0) break;

        string kriteriaPilihan = "";
        int    pilihanTahun    = 0;
        int    indeksKolomTabel = -1;
        bool   isFilterTahun   = false;
        bool   lanjutProses    = false;

        if (pilihanFilter == 1) {
            cout << "\n>>> FILTER TAHUN" << endl;
            cout << "  [1] Semua" << endl;
            cout << "  [2] Mobil Baru (Tahun >= 2000)" << endl;
            cout << "  [3] Mobil Lama (Tahun < 2000)" << endl;
            cout << "  [0] Kembali" << endl;
            cout << "Pilihan: ";
            cin >> pilihanTahun;
            if (pilihanTahun != 0) {
                lanjutProses = true;
                isFilterTahun = true;
            }
        } 
        else if (pilihanFilter == 2 || pilihanFilter == 3) {
            int kolom = (pilihanFilter == 2) ? 1 : 4;
            string label = (pilihanFilter == 2) ? "MERK" : "KONDISI";
            
            vector<string> opsi = ambilOpsiDinamis(kolom);
            if (opsi.empty()) {
                cout << "[!] Data " << label << " tidak ditemukan di database." << endl;
                continue;
            }

            cout << "\n>>> FILTER " << label << endl;
            cout << "  [1] Tampilkan Semua" << endl;
            for (size_t i = 0; i < opsi.size(); i++) {
                cout << "  [" << i + 2 << "] " << opsi[i] << endl;
            }
            cout << "  [0] Kembali" << endl;
            
            int pil;
            cout << "Pilihan: ";
            cin >> pil;
            
            if (pil == 0) continue;
            lanjutProses = true;
            indeksKolomTabel = kolom;
            if (pil > 1 && pil <= (int)opsi.size() + 1) {
                kriteriaPilihan = opsi[pil - 2];
            }
        }

        if (lanjutProses) {
            #ifdef _WIN32
                system("cls");
            #else
                system("clear");
            #endif

            cout << "\n" << setfill('=') << setw(78) << "=" << setfill(' ') << endl;
            cout << left << " " << setw(6) << "ID" << setw(15) << "MERK" << setw(25) << "MODEL" << setw(10) << "TAHUN" << "KONDISI" << endl;
            cout << setfill('-') << setw(78) << "-" << setfill(' ') << endl;

            int counter = 0;
            ifstream file("database_mobil.csv");
            string line;
            getline(file, line);

            while (getline(file, line)) {
                stringstream ss(line);
                string k[5]; 
                for(int j=0; j<5; j++) getline(ss, k[j], ',');

                bool lolos = false;
                if (isFilterTahun) {
                    int thn = stoi(k[3]);
                    if (pilihanTahun == 1) lolos = true;
                    else if (pilihanTahun == 2) lolos = (thn >= 2000);
                    else if (pilihanTahun == 3) lolos = (thn < 2000);
                } else {
                    if (kriteriaPilihan == "") lolos = true;
                    else lolos = (k[indeksKolomTabel] == kriteriaPilihan);
                }

                if (lolos) {
                    counter++;
                    string modelTeks = k[2];
                    if (modelTeks.length() > 22) modelTeks = modelTeks.substr(0, 19) + "...";
                    cout << left << " " << setw(6) << k[0] << setw(15) << k[1] << setw(25) << modelTeks << setw(10) << k[3] << k[4] << endl;
                }
            }
            file.close();

            cout << setfill('=') << setw(78) << "=" << setfill(' ') << endl;
            cout << " Berhasil menemukan " << counter << " unit." << endl;
            cout << " Tekan Enter untuk kembali ke Menu Filter...";
            cin.ignore(1000, '\n');
            cin.get();
        }
    }
}