#include <iostream>
#include <string>
#include <iomanip>
#include <fstream>   // Untuk baca file
#include <sstream>   // Untuk memecah string (koma)
#include "features.h"

using namespace std;
Kategori showroom[3];
const string dbMobil = "database_mobil.csv";

void tambahUnit(Kategori &kat, string model, int tahun, double harga) {
    Mobil* baru = new Mobil;
    baru->Model = model;
    baru->Tahun = tahun;
    baru->Harga = harga;
    baru->next = kat.head;
    kat.head = baru;
}

void inisialisasiData() {
    showroom[0].NamaMerk = "Toyota"; 
    showroom[1].NamaMerk = "Honda";
    showroom[2].NamaMerk = "Suzuki";
    
    showroom[0].head = nullptr;
    showroom[1].head = nullptr;
    showroom[2].head = nullptr;

    ifstream file(dbMobil.c_str());
    if (!file.is_open()) {
        return; 
    }

    // Baca per baris
    for (string line; getline(file, line); ) {
        if(line.empty()) continue; // Abaikan baris kosong
        
        stringstream ss(line);
        string merkStr, modelStr, tahunStr, hargaStr;

        // Pisahkan berdasarkan koma
        getline(ss, merkStr, ',');
        getline(ss, modelStr, ',');
        getline(ss, tahunStr, ',');
        getline(ss, hargaStr, ',');

        int tahun = stoi(tahunStr);
        double harga = stod(hargaStr);

        // Masukkan data ke kategori merk yang tepat
        for(int i = 0; i < 3; i++) {
            if(showroom[i].NamaMerk == merkStr) {
                tambahUnit(showroom[i], modelStr, tahun, harga);
                break;
            }
        }
    }
    file.close();
}

void tampilkanKatalog() {
    bool adaData = false;
    for (int i = 0; i < 3; i++) {
        if (showroom[i].head != nullptr) adaData = true;
    }

    if (!adaData) {
        cout << "\n[!] Katalog Kosong. Belum ada mobil di dalam database.\n";
        return;
    }

    cout << "\n" << setfill('=') << setw(65) << "=" << endl;
    cout << left << setw(15) << "MERK" << setw(20) << "MODEL" << setw(10) << "TAHUN" << "HARGA" << endl;
    cout << setfill('-') << setw(65) << "-" << setfill(' ') << endl;

    for (int i = 0; i < 3; i++) { 
        Mobil* temp = showroom[i].head; 
        while (temp != nullptr) { 
            cout << left << setw(15) << showroom[i].NamaMerk 
                 << setw(20) << temp->Model 
                 << setw(10) << temp->Tahun 
                 << fixed << setprecision(1) << "$" << temp->Harga << " Jt" << endl;
            temp = temp->next;
        }
    }
    cout << setfill('=') << setw(65) << "=" << setfill(' ') << endl;
}