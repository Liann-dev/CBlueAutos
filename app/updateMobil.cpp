#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <vector>
#include "features.h"

using namespace std;

extern Kategori showroom[3];
const string dbMobil = "database_mobil.csv";

// Fungsi pembantu untuk menulis ulang seluruh database dari linked list ke CSV
void sinkronisasiKeCSV() {
    ofstream file(dbMobil.c_str());
    if (!file.is_open()) return;

    file << "ID,Merk,Model,Tahun,Kondisi\n"; // Header
    for (int i = 0; i < 3; i++) {
        Mobil* temp = showroom[i].head;
        while (temp != nullptr) {
            file << temp->id << "," 
                 << showroom[i].NamaMerk << "," 
                 << temp->Model << "," 
                 << temp->Tahun << "," 
                 << temp->Kondisi << "\n";
            temp = temp->next;
        }
    }
    file.close();
}

void updateMobilAdmin() {
    int targetId;
    string kondisiBaru;
    bool ditemukan = false;

    cout << "\n=== UPDATE KONDISI UNIT (BY ID) ===" << endl;
    cout << "Masukkan ID Mobil yang ingin diupdate: ";
    if (!(cin >> targetId)) {
        cin.clear();
        cin.ignore(10000, '\n');
        cout << "[Error] Input ID harus berupa angka!\n";
        return;
    }

    // Mencari mobil berdasarkan ID di dalam linked list showroom
    for (int i = 0; i < 3; i++) {
        Mobil* temp = showroom[i].head;
        while (temp != nullptr) {
            if (temp->id == targetId) {
                cout << "\nData Ditemukan:" << endl;
                cout << "Merk    : " << showroom[i].NamaMerk << endl;
                cout << "Model   : " << temp->Model << endl;
                cout << "Kondisi : " << temp->Kondisi << endl;
                
                cout << "\nMasukkan Kondisi Baru (Baru/Bekas): ";
                cin.ignore();
                getline(cin, kondisiBaru);
                
                // Update data di memori
                temp->Kondisi = kondisiBaru;
                ditemukan = true;
                break;
            }
            temp = temp->next;
        }
        if (ditemukan) break;
    }

    if (ditemukan) {
        // Simpan perubahan permanen ke file CSV
        sinkronisasiKeCSV();
        cout << "[Sukses] Kondisi unit dengan ID " << targetId << " berhasil diperbarui!\n";
    } else {
        cout << "[Error] Unit dengan ID " << targetId << " tidak ditemukan!\n";
    }
}