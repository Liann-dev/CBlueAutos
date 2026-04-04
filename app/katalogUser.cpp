#include <iostream>
#include <string>
#include <iomanip>
#include <fstream>
#include <sstream>
#include "features.h"

using namespace std;
Kategori showroom[3];
const string dbMobil = "database_mobil.csv";

void tambahUnit(Kategori &kat, string model, int tahun, string kondisi) {
    Mobil* baru = new Mobil;
    baru->Model = model;
    baru->Tahun = tahun;
    baru->Kondisi = kondisi;
    baru->next = kat.head;
    kat.head = baru;
}

void inisialisasiData() {
    showroom[0].NamaMerk = "Toyota"; 
    showroom[1].NamaMerk = "Honda";
    showroom[2].NamaMerk = "Suzuki";
    
    for(int i = 0; i < 3; i++) showroom[i].head = nullptr;

    ifstream file(dbMobil.c_str());
    string line;
    getline(file, line); // Melewati baris header (ID,Merk,Model,Tahun,Kondisi)

    while (getline(file, line)) {
        if(line.empty()) continue;
        
        stringstream ss(line);
        string idStr, merkStr, modelStr, tahunStr, kondisiStr;

        getline(ss, idStr, ',');    // Ambil ID
        getline(ss, merkStr, ',');  // Ambil Merk
        getline(ss, modelStr, ','); // Ambil Model
        getline(ss, tahunStr, ','); // Ambil Tahun
        getline(ss, kondisiStr, ','); // Ambil Kondisi

        Mobil* baru = new Mobil;
        baru->id = stoi(idStr);
        baru->Model = modelStr;
        baru->Tahun = stoi(tahunStr);
        baru->Kondisi = kondisiStr;
        
        // Masukkan ke kategori yang sesuai
        for(int i = 0; i < 3; i++) {
            if(showroom[i].NamaMerk == merkStr) {
                baru->next = showroom[i].head;
                showroom[i].head = baru;
                break;
            }
        }
    }
    file.close();
}

void tampilkanKatalog() {
    // Header tabel disesuaikan: Harga dihapus, Kondisi ditambah
    cout << "\n" << setfill('=') << setw(65) << "=" << endl;
    cout << left << setw(15) << "MERK" << setw(20) << "MODEL" << setw(10) << "TAHUN" << "KONDISI" << endl;
    cout << setfill('-') << setw(65) << "-" << setfill(' ') << endl;

    for (int i = 0; i < 3; i++) { 
        Mobil* temp = showroom[i].head; 
        while (temp != nullptr) { 
            cout << left << setw(15) << showroom[i].NamaMerk 
                 << setw(20) << temp->Model 
                 << setw(10) << temp->Tahun 
                 << temp->Kondisi << endl;
            temp = temp->next;
        }
    }
    cout << setfill('=') << setw(65) << "=" << setfill(' ') << endl;
}