#include <iostream>
#include <string>
#include <algorithm>
#include <iomanip>
#include <fstream>
#include <sstream>
#include <vector>
#include <set>
#include "features.h"

using namespace std;

// ======================
// SEARCH ADMIN
// ======================
void cariMobilAdmin() {
    string key;

    cout << "\n=== SEARCH STOK MOBIL (ADMIN) ===\n";
    cout << "Masukkan Merk/Model (atau '0' untuk semua): ";
    getline(cin >> ws, key);
    string keyKecil = keHurufKecil(key);

    cout << "\n" << setfill('=') << setw(75) << "=" << endl;
    cout << left << setw(5) << "ID"
         << setw(15) << "MERK"
         << setw(20) << "MODEL"
         << setw(10) << "TAHUN"
         << "KONDISI" << endl;
    cout << setfill('-') << setw(75) << "-" << setfill(' ') << endl;

    int counter = 0;

    for (Kategori* currKat = headKategori; currKat != nullptr; currKat = currKat->next) {
        string merkKecil = keHurufKecil(currKat->NamaMerk);

        for (Mobil* temp = currKat->head; temp != nullptr; temp = temp->next) {
            string modelKecil = keHurufKecil(temp->Model);

            if (keyKecil == "0" || keyKecil == "" ||
                merkKecil.find(keyKecil) != string::npos ||
                modelKecil.find(keyKecil) != string::npos) {

                counter++;
                cout << left
                     << setw(5) << temp->id
                     << setw(15) << currKat->NamaMerk
                     << setw(20) << temp->Model
                     << setw(10) << temp->Tahun
                     << temp->Kondisi << endl;
            }
        }
    }

    if (counter > 0) {
        cout << setfill('=') << setw(75) << "=" << setfill(' ') << endl;
        cout << "Total ditemukan: " << counter << " unit.\n";
    } else {
        cout << "\n[!] Data tidak ditemukan.\n";
    }
}


// ======================
// FILTER ADMIN
// ======================

// ambil opsi unik dari CSV (kayak user)
vector<string> ambilOpsiAdmin(int kolom) {
    set<string> unik;
    ifstream file("database_mobil.csv");
    string line;

    if (!file.is_open()) return {};

    getline(file, line); // skip header

    while (getline(file, line)) {
        stringstream ss(line);
        string temp;
        int i = 0;

        while (getline(ss, temp, ',')) {
            if (i == kolom && !temp.empty()) {
                unik.insert(temp);
            }
            i++;
        }
    }

    return vector<string>(unik.begin(), unik.end());
}

void filterMobilAdmin() {
    int pilihan;

    cout << "\n=== FILTER STOK MOBIL (ADMIN) ===\n";
    cout << "1. Berdasarkan Tahun\n";
    cout << "2. Berdasarkan Merk\n";
    cout << "3. Berdasarkan Kondisi\n";
    cout << "0. Kembali\n";
    cout << "Pilih: ";
    cin >> pilihan;

    if (pilihan == 0) return;

    string kriteria = "";
    int kolom = -1;
    bool filterTahun = false;
    int pilihanTahun = 0;

    if (pilihan == 1) {
        cout << "\n1. Semua\n";
        cout << "2. Tahun >= 2000\n";
        cout << "3. Tahun < 2000\n";
        cout << "Pilih: ";
        cin >> pilihanTahun;
        filterTahun = true;
    }

    else if (pilihan == 2) {
        vector<string> opsi = ambilOpsiAdmin(1);

        if (opsi.empty()) {
            cout << "[!] Data merk tidak ada.\n";
            return;
        }

        cout << "\nPilih Merk:\n";
        for (int i = 0; i < opsi.size(); i++) {
            cout << i + 1 << ". " << opsi[i] << endl;
        }

        int pilih;
        cout << "Pilih: ";
        cin >> pilih;

        kriteria = opsi[pilih - 1];
        kolom = 1;
    }

    else if (pilihan == 3) {
        cout << "\n1. Brand New\n2. Mint\n3. Excellent\n4. Good\n5. Project Car\n";
        int pilih;
        cout << "Pilih: ";
        cin >> pilih;

        string kondisi[] = {"Brand New","Mint","Excellent","Good","Project Car"};
        kriteria = kondisi[pilih - 1];
        kolom = 4;
    }

    cout << "\n" << setfill('=') << setw(75) << "=" << endl;
    cout << left << setw(5) << "ID"
         << setw(15) << "MERK"
         << setw(20) << "MODEL"
         << setw(10) << "TAHUN"
         << "KONDISI" << endl;
    cout << setfill('-') << setw(75) << "-" << setfill(' ') << endl;

    ifstream file("database_mobil.csv");
    string line;
    getline(file, line);

    int count = 0;

    while (getline(file, line)) {
        stringstream ss(line);
        string data[5];

        for (int i = 0; i < 5; i++) getline(ss, data[i], ',');

        bool cocok = false;

        if (filterTahun) {
            int tahun = stoi(data[3]);
            if (pilihanTahun == 1) cocok = true;
            else if (pilihanTahun == 2) cocok = (tahun >= 2000);
            else if (pilihanTahun == 3) cocok = (tahun < 2000);
        } else {
            cocok = (data[kolom] == kriteria);
        }

        if (cocok) {
            count++;
            cout << left
                 << setw(5) << data[0]
                 << setw(15) << data[1]
                 << setw(20) << data[2]
                 << setw(10) << data[3]
                 << data[4] << endl;
        }
    }

    cout << setfill('=') << setw(75) << "=" << setfill(' ') << endl;
    cout << "Total: " << count << " unit\n";
}