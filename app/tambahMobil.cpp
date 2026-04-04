#include <iostream>
#include <string>
#include <algorithm>
#include <iomanip>
#include <fstream>
#include "features.h"

using namespace std;

extern Kategori showroom[3]; 

const string dbMobil = "database_mobil.csv"; 

void tambahMobilAdmin() {
    int indeks;
    string modelBaru;
    int tahunBaru;
    double hargaBaru;

    cout << "\n======================================" << endl;
    cout << "     TAMBAH UNIT MOBIL (ADMIN)        " << endl;
    cout << "======================================" << endl;
    
    cout << "Pilih Merk Unit:" << endl;
    for (int i = 0; i < 3; i++) {
        cout << i << ". " << showroom[i].NamaMerk << endl;
    }
    cout << "Pilih (0-2): ";
    
    if (!(cin >> indeks) || indeks < 0 || indeks > 2) {
        cin.clear();
        cin.ignore(10000, '\n');
        cout << "\n[Error] Indeks merk tidak valid!" << endl;
        return;
    }

    cout << "Nama Model  : ";
    cin.ignore(10000, '\n'); 
    getline(cin, modelBaru);

    cout << "Tahun Rilis : ";
    cin >> tahunBaru;

    cout << "Harga (Jt)  : ";
    cin >> hargaBaru;

    // --- TAMBAHAN PELACAK DEBUG ---
    cout << "\n[DEBUG 1] Input harga berhasil diterima." << endl;

    // 1. Simpan ke dalam memori (Linked List)
    tambahUnit(showroom[indeks], modelBaru, tahunBaru, hargaBaru);

    cout << "[DEBUG 2] Penyimpanan ke memori (tambahUnit) berhasil." << endl;

    // 2. Simpan ke dalam file CSV agar permanen
    ofstream file(dbMobil.c_str(), ios::app);
    if(file.is_open()) {
        file << showroom[indeks].NamaMerk << "," 
             << modelBaru << "," 
             << tahunBaru << "," 
             << hargaBaru << "\n";
        file.close();
        cout << "\n[SUKSES] " << modelBaru << " berhasil ditambahkan!" << endl;
    } else {
        cout << "\n[Error] Gagal membuka database_mobil.csv!" << endl;
    }
    
    cout << "======================================" << endl;
}