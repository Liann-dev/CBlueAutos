#include <iostream>
#include <string>
#include <algorithm>
#include <iomanip>
#include <fstream>
#include "features.h"

using namespace std;

extern Kategori showroom[3]; 
const string dbMobil = "database_mobil.csv"; 
int getNextMobilId() {
    ifstream file("database_mobil.csv");
    string line;
    int lastId = 0;
    getline(file, line);
    while (getline(file, line)) {
        stringstream ss(line);
        string idStr;
        if (getline(ss, idStr, ',')) {
            try { lastId = stoi(idStr); } catch(...) {}
        }
    }
    return lastId + 1;
}
void tambahMobilAdmin() {
    int indeks;
    string modelBaru;
    int tahunBaru;

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

    string kondisiBaru;
    
    cout << "Nama Model  : ";
    cin.ignore(10000, '\n'); 
    getline(cin, modelBaru);

    cout << "Tahun Rilis : ";
    cin >> tahunBaru;

    bool perlubarisbaru = false;
    ifstream checkakhir(dbMobil.c_str (), ios::binary);
    if (checkakhir.good()) {
        checkakhir.seekg(0, ios::end);
        if (checkakhir.tellg() > 0) {
            checkakhir.seekg(-1, ios::end);
            char lastChar;
            checkakhir.get(lastChar);
            if (lastChar != '\n' && lastChar != '\r') {
                perlubarisbaru = true;
            }
        checkakhir.close();
        }
    }


    cout << "Kondisi (Baru/Bekas): ";
    cin.ignore();
    getline(cin, kondisiBaru);

    int idBaru = getNextMobilId();

    ofstream file(dbMobil.c_str(), ios::app);
    if(file.is_open()) {
        file << idBaru << "," 
             << showroom[indeks].NamaMerk << "," 
             << modelBaru << "," 
             << tahunBaru << "," 
             << kondisiBaru << "\n";
        file.close();
        tambahUnit(showroom[indeks], modelBaru, tahunBaru, kondisiBaru);
        cout << "\n[SUKSES] Unit dengan ID " << idBaru << " berhasil ditambahkan!" << endl;
    }
    else {
        cout << "\n[ERROR] Gagal membuka file database_mobil.csv!" << endl;
    }
}