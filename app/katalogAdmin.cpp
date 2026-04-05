#include <iostream>
#include <iomanip>
#include <string>
#include <fstream>
#include <sstream>

using namespace std;

struct DataKatalogAdmin {
    string id;
    string merk;
    string model;
    string tahun;
    string kondisi;
};
void bersihkanTeks(string& str) {
    if (str.empty()) return;
    size_t start = str.find_first_not_of(" \t\r\n");
    size_t end = str.find_last_not_of(" \t\r\n");
    if (start == string::npos) {
        str = "";
    } else {
        str = str.substr(start, end - start + 1);
    }
}

// Fungsi bantuan untuk mengubah string ID menjadi integer dengan aman
int konversiKeAngka(string teks) {
    if (teks.empty()) return 0;
    int hasil = 0;
    try {
        hasil = stoi(teks); // Mengubah teks "15" menjadi angka 15
    } catch (...) {
        hasil = 0; // Jika error/bukan angka, jadikan 0
    }
    return hasil;
}

void tampilkanKatalogAdmin() {
    int totalData = 0;
    ifstream fileHitung("database_mobil.csv");
    string line;
    
    // 1. Hitung total data
    if (fileHitung.is_open()) {
        getline(fileHitung, line); 
        while (getline(fileHitung, line)) {
            if (!line.empty()) totalData++; 
        }
        fileHitung.close();
    }

    if (totalData == 0) {
        cout << "\n===========================================================================\n";
        cout << "                           KATALOG MOBIL (ADMIN)                           \n";
        cout << "===========================================================================\n";
        cout << " [!] Katalog masih kosong. Belum ada data di dalam database.\n";
        cout << "===========================================================================\n";
        return;
    }

    DataKatalogAdmin* listMobil = new DataKatalogAdmin[totalData];
    
    // 3. Masukkan data ke array dan bersihkan teks
    ifstream fileData("database_mobil.csv");
    int index = 0;
    if (fileData.is_open()) {
        getline(fileData, line); 
        while (getline(fileData, line) && index < totalData) {
            if (line.empty()) continue;
            
            stringstream ss(line);
            getline(ss, listMobil[index].id, ',');
            getline(ss, listMobil[index].merk, ',');
            getline(ss, listMobil[index].model, ',');
            getline(ss, listMobil[index].tahun, ',');
            getline(ss, listMobil[index].kondisi, ',');

            bersihkanTeks(listMobil[index].id);
            bersihkanTeks(listMobil[index].merk);
            bersihkanTeks(listMobil[index].model);
            bersihkanTeks(listMobil[index].tahun);
            bersihkanTeks(listMobil[index].kondisi);

            index++;
        }
        fileData.close();
    }

    for (int i = 0; i < totalData - 1; i++) {
        for (int j = 0; j < totalData - i - 1; j++) {
            int idKiri = konversiKeAngka(listMobil[j].id);
            int idKanan = konversiKeAngka(listMobil[j + 1].id);

            if (idKiri > idKanan) {
                // Tukar posisi seluruh data baris tersebut
                DataKatalogAdmin temp = listMobil[j];
                listMobil[j] = listMobil[j + 1];
                listMobil[j + 1] = temp;
            }
        }
    }
    int itemPerHalaman = 10; 
    int totalHalaman = (totalData + itemPerHalaman - 1) / itemPerHalaman;
    int halamanSekarang = 1;
    char pilihan;

    while (true) {
        #ifdef _WIN32
            system("cls");
        #else
            system("clear");
        #endif

        cout << "\n===========================================================================\n";
        cout << "                           KATALOG MOBIL (ADMIN)                           \n";
        cout << "===========================================================================\n";
        
        cout << left 
             << setw(6)  << "ID" 
             << setw(15) << "MERK" 
             << setw(25) << "MODEL" 
             << setw(10) << "TAHUN" 
             << "KONDISI" << endl;
             
        cout << setfill('-') << setw(75) << "-" << setfill(' ') << endl;

        int startIdx = (halamanSekarang - 1) * itemPerHalaman;
        int endIdx = startIdx + itemPerHalaman;
        if (endIdx > totalData) endIdx = totalData; 

        for (int i = startIdx; i < endIdx; i++) {
            string modelTeks = listMobil[i].model;
            if (modelTeks.length() > 22) {
                modelTeks = modelTeks.substr(0, 19) + "...";
            }

            cout << left 
                 << setw(6)  << listMobil[i].id 
                 << setw(15) << listMobil[i].merk 
                 << setw(25) << modelTeks 
                 << setw(10) << listMobil[i].tahun 
                 << listMobil[i].kondisi << endl;
        }

        cout << setfill('=') << setw(75) << "=" << setfill(' ') << endl;
        
        cout << " Halaman " << halamanSekarang << " dari " << totalHalaman << " | Total Unit Aset: " << totalData << endl;
        cout << "---------------------------------------------------------------------------\n";
        cout << "  [N] Next Page   |   [P] Prev Page   |   [X] Keluar ke Menu Admin\n";
        cout << "---------------------------------------------------------------------------\n";
        cout << "Pilihan: ";
        cin >> pilihan;

        if (pilihan == 'X' || pilihan == 'x') {
            break; 
        } else if (pilihan == 'N' || pilihan == 'N') {
            if (halamanSekarang < totalHalaman) halamanSekarang++;
        } else if (pilihan == 'p' || pilihan == 'P') {
            if (halamanSekarang > 1) halamanSekarang--;
        } else {
            cout << "Pilihan tidak valid. Inputkan 'N', 'P', atau '0' saja!.\n";
        } 
    }

    // 6. Hapus dari memori
    delete[] listMobil; 
}