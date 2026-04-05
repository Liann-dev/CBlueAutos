#include <iostream>
#include <iomanip>
#include <string>
#include <fstream>
#include <sstream>
#include "features.h"

using namespace std;

void tampilkanKatalogAdmin() {
    cout << "\n===========================================================================\n";
    cout << "                           KATALOG MOBIL (ADMIN)                           \n";
    cout << "===========================================================================\n";
    
    // Header Tabel
    cout << left 
         << setw(6)  << "ID" 
         << setw(15) << "MERK" 
         << setw(25) << "MODEL" 
         << setw(10) << "TAHUN" 
         << "KONDISI" << endl;
         
    cout << setfill('-') << setw(75) << "-" << setfill(' ') << endl;

    ifstream file("database_mobil.csv");
    string line;
    bool adaData = false;

    if (file.is_open()) {
        // Melewati baris pertama karena itu adalah Header CSV (ID,Merk,Model,Tahun,Kondisi)
        getline(file, line); 

        // Membaca data baris demi baris dari CSV
        while (getline(file, line)) {
            if (line.empty()) continue;

            stringstream ss(line);
            string idStr, merk, model, tahunStr, kondisi;

            getline(ss, idStr, ',');
            getline(ss, merk, ',');
            getline(ss, model, ',');
            getline(ss, tahunStr, ',');
            getline(ss, kondisi, ',');

            adaData = true;

            // Mencegah nama model yang terlalu panjang merusak layout tabel
            if (model.length() > 22) {
                model = model.substr(0, 19) + "...";
            }

            // Menampilkan Isi Tabel
            cout << left 
                 << setw(6)  << idStr 
                 << setw(15) << merk 
                 << setw(25) << model 
                 << setw(10) << tahunStr 
                 << kondisi << endl;
        }
        file.close();
    }

    if (!adaData) {
        cout << " [!] Katalog masih kosong atau gagal membaca file database." << endl;
    }
    
    cout << setfill('=') << setw(75) << "=" << setfill(' ') << endl;
}