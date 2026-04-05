#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <iomanip>
#include "features.h"
#include "cctype" 

using namespace std;

const string dbMobil = "database_mobil.csv";
struct DataSortTemp {
    int id;
    string merk;
    string model;
    int tahun;
    string kondisi;
    Mobil* ptrAsli; 
};

void sinkronisasiKeCSV() {
    int totalData = 0;
    for (Kategori *currKat = headKategori; currKat != nullptr; currKat = currKat->next) {
        for (Mobil *temp = currKat->head; temp != nullptr; temp = temp->next) {
            totalData++;
        }
    }
    if (totalData == 0) {
        ofstream file(dbMobil.c_str(), ios::trunc);
        if (file.is_open()) file << "ID,Merk,Model,Tahun,Kondisi\n";
        return;
    }

    DataSortTemp* arr = new DataSortTemp[totalData];
    int idx = 0;
    for (Kategori *currKat = headKategori; currKat != nullptr; currKat = currKat->next) {
        for (Mobil *temp = currKat->head; temp != nullptr; temp = temp->next) {
            arr[idx].id = temp->id;
            arr[idx].merk = currKat->NamaMerk;
            arr[idx].model = temp->Model;
            arr[idx].tahun = temp->Tahun;
            arr[idx].kondisi = temp->Kondisi;
            arr[idx].ptrAsli = temp; 
            idx++;
        }
    }

 
    for (int i = 0; i < totalData - 1; i++) {
        for (int j = 0; j < totalData - i - 1; j++) {
            if (arr[j].id > arr[j + 1].id) {
                DataSortTemp temp = arr[j];
                arr[j] = arr[j + 1];
                arr[j + 1] = temp;
            }
        }
    }
    for (int i = 0; i < totalData; i++) {
        arr[i].id = i + 1;              
        arr[i].ptrAsli->id = i + 1;     
    }

    ofstream file(dbMobil.c_str(), ios::trunc);
    if (file.is_open()) {
        file << "ID,Merk,Model,Tahun,Kondisi\n";
        for (int i = 0; i < totalData; i++) {
            file << arr[i].id << "," << arr[i].merk << "," << arr[i].model << ","
                 << arr[i].tahun << "," << arr[i].kondisi << "\n";
        }
        file.close();
    }
    
    delete[] arr; 
}

void updateMobilAdmin()
{
    int totalData = 0;
    for (Kategori *currKat = headKategori; currKat != nullptr; currKat = currKat->next) {
        for (Mobil *temp = currKat->head; temp != nullptr; temp = temp->next) {
            totalData++;
        }
    }

    if (totalData == 0) {
        cout << "\n[!] Data kosong. Tidak ada unit yang bisa diupdate.\n";
        return;
    }

    DataSortTemp* arr = new DataSortTemp[totalData];
    int idx = 0;
    for (Kategori *currKat = headKategori; currKat != nullptr; currKat = currKat->next) {
        for (Mobil *temp = currKat->head; temp != nullptr; temp = temp->next) {
            arr[idx].id = temp->id;
            arr[idx].merk = currKat->NamaMerk;
            arr[idx].model = temp->Model;
            arr[idx].tahun = temp->Tahun;
            arr[idx].kondisi = temp->Kondisi;
            idx++;
        }
    }

    for (int i = 0; i < totalData - 1; i++) {
        for (int j = 0; j < totalData - i - 1; j++) {
            if (arr[j].id > arr[j + 1].id) {
                DataSortTemp temp = arr[j];
                arr[j] = arr[j + 1];
                arr[j + 1] = temp;
            }
        }
    }

    int itemPerHalaman = 10;
    int totalHalaman = (totalData + itemPerHalaman - 1) / itemPerHalaman;
    int halamanSekarang = 1;
    
    int targetId = -1;
    string targetModel = "";
    string pilihan;

    while (true) {
        #ifdef _WIN32
            system("cls");
        #else
            system("clear");
        #endif

        cout << "\n===========================================================================\n";
        cout << "                         UPDATE UNIT MOBIL (ADMIN)                         \n";
        cout << "===========================================================================\n";
        
        cout << left << setw(6) << "ID" << setw(15) << "MERK" << setw(25) << "MODEL" 
             << setw(10) << "TAHUN" << "KONDISI" << endl;
        cout << setfill('-') << setw(75) << "-" << setfill(' ') << endl;

        int startIdx = (halamanSekarang - 1) * itemPerHalaman;
        int endIdx = startIdx + itemPerHalaman;
        if (endIdx > totalData) endIdx = totalData;

        for (int i = startIdx; i < endIdx; i++) {
            string modelTeks = arr[i].model;
            if (modelTeks.length() > 22) modelTeks = modelTeks.substr(0, 19) + "...";
            
            cout << left << setw(6) << arr[i].id << setw(15) << arr[i].merk 
                 << setw(25) << modelTeks << setw(10) << arr[i].tahun << arr[i].kondisi << endl;
        }
        
        cout << setfill('=') << setw(75) << "=" << setfill(' ') << endl;
        cout << " Halaman " << halamanSekarang << " dari " << totalHalaman << " | Total Unit Aset: " << totalData << endl;
        cout << "---------------------------------------------------------------------------\n";
        cout << "  [N] Next Page   |   [P] Prev Page   |   [X] Batal & Kembali\n";
        cout << "---------------------------------------------------------------------------\n";
        cout << "Ketik 'N' / 'P', masukkan ID, atau ketik kata kunci nama Model: ";
        
        getline(cin >> ws, pilihan);

        if (pilihan == "X" || pilihan == "x") {
            delete[] arr; 
            return; 
        } else if (pilihan == "n" || pilihan == "N") {
            if (halamanSekarang < totalHalaman) halamanSekarang++;
        } else if (pilihan == "p" || pilihan == "P") {
            if (halamanSekarang > 1) halamanSekarang--;
        } else {
            bool isAngka = true;
            for (char c : pilihan) {
                if (!isdigit(c)) {
                    isAngka = false;
                    break;
                }
            }

            if (isAngka) {
                targetId = stoi(pilihan);
            } else {
                targetModel = keHurufKecil(pilihan);
            }
            break; 
        }
    }
    delete[] arr;

    // =========================================================
    // LOGIKA PENCARIAN FLEKSIBEL (PARTIAL MATCH UNTUK STRING)
    // =========================================================
    if (targetId == -1 && targetModel != "") {
        int matchCount = 0;
        
        for (Kategori *currKat = headKategori; currKat != nullptr; currKat = currKat->next) {
            for (Mobil *temp = currKat->head; temp != nullptr; temp = temp->next) {
                if (keHurufKecil(temp->Model).find(targetModel) != string::npos) {
                    matchCount++;
                }
            }
        }

        if (matchCount == 0) {
            cout << "\n[Error] Tidak ada unit dengan nama model yang mengandung '" << pilihan << "'!\n";
            return;
        } 
        else if (matchCount == 1) {
            // Jika cuma ada 1 yang cocok, langsung ambil ID-nya otomatis!
            for (Kategori *currKat = headKategori; currKat != nullptr; currKat = currKat->next) {
                for (Mobil *temp = currKat->head; temp != nullptr; temp = temp->next) {
                    if (keHurufKecil(temp->Model).find(targetModel) != string::npos) {
                        targetId = temp->id;
                    }
                }
            }
        } 
        else {
            cout << "\n[Info] Ditemukan " << matchCount << " unit yang mirip dengan kata kunci '" << pilihan << "':\n";
            cout << left << setw(6) << "ID" << setw(15) << "MERK" << setw(25) << "MODEL" 
                 << setw(10) << "TAHUN" << "KONDISI" << endl;
            cout << setfill('-') << setw(75) << "-" << setfill(' ') << endl;

            for (Kategori *currKat = headKategori; currKat != nullptr; currKat = currKat->next) {
                for (Mobil *temp = currKat->head; temp != nullptr; temp = temp->next) {
                    if (keHurufKecil(temp->Model).find(targetModel) != string::npos) {
                        cout << left << setw(6) << temp->id << setw(15) << currKat->NamaMerk 
                             << setw(25) << temp->Model << setw(10) << temp->Tahun << temp->Kondisi << endl;
                    }
                }
            }
            cout << setfill('-') << setw(75) << "-" << setfill(' ') << endl;
            
            cout << "Pilih angka ID mobil yang mana yang ingin diupdate (Ketik 0 untuk Batal): ";
            string inputPilihId;
            cin >> inputPilihId;
            try {
                targetId = stoi(inputPilihId);
                if (targetId == 0) return; 
            } catch (...) {
                cout << "[Error] Input tidak valid! Update dibatalkan.\n";
                return;
            }
            cin.ignore(1000, '\n'); 
        }
    }

    string kondisiBaru, modelBaru, inputTahun, merkBaru;
    int tahunBaru;
    bool ditemukan = false;

    for (Kategori *currKat = headKategori; currKat != nullptr; currKat = currKat->next) {
        for (Mobil *temp = currKat->head; temp != nullptr; temp = temp->next) {
            
            if (temp->id == targetId) {
                cout << "\n" << setfill('-') << setw(80) << "-" << setfill(' ') << endl;
                cout << left << "UBAH DATA UNIT (ID: " << temp->id << " | " << temp->Model << ") (Kosongkan jika tidak diubah)" << endl;
                cout << setfill('-') << setw(80) << "-" << setfill(' ') << endl;

                cout << "\nData Saat Ini:" << endl;
                cout << "Merk    : " << currKat->NamaMerk << endl;
                cout << "Model   : " << temp->Model << endl;
                cout << "Tahun   : " << temp->Tahun << endl;
                cout << "Kondisi : " << temp->Kondisi << endl << endl;

                cout << "Masukkan Merk Baru: ";
                getline(cin, merkBaru);
                if (merkBaru == "") merkBaru = currKat->NamaMerk;

                cout << "Masukan Model Baru: ";
                getline(cin, modelBaru);
                if (modelBaru == "") modelBaru = temp->Model;

                cout << "Masukan Tahun Pembuatan Baru: ";
                getline(cin, inputTahun);
                if (inputTahun == "") tahunBaru = temp->Tahun;
                else {
                    try { tahunBaru = stoi(inputTahun); } 
                    catch (...) { cout << "[Error] Tahun harus berupa angka valid!\n"; return; }
                }

                bool KondisiValid = false;
                int pilihanKondisi;
                while (!KondisiValid) {
                    cout << "\nPilih Kondisi Mobil:\n";
                    cout << "1. Brand New\n2. Mint\n3. Excellent\n4. Good\n5. Project Car\n";
                    cout << "0. Pertahankan Kondisi Lama (" << temp->Kondisi << ")\n";
                    cout << "Masukkan pilihan (0-5): ";

                    cin >> pilihanKondisi;

                    if (cin.fail()) {
                        cin.clear(); cin.ignore(10000, '\n');
                        cout << "[ERROR] Input harus berupa angka!\n";
                        continue;
                    } else {
                        switch (pilihanKondisi) {
                            case 1: kondisiBaru = "Brand New"; KondisiValid = true; break;
                            case 2: kondisiBaru = "Mint"; KondisiValid = true; break;
                            case 3: kondisiBaru = "Excellent"; KondisiValid = true; break;
                            case 4: kondisiBaru = "Good"; KondisiValid = true; break;
                            case 5: kondisiBaru = "Project Car"; KondisiValid = true; break;
                            case 0: kondisiBaru = temp->Kondisi; KondisiValid = true; break;
                            default: cout << "[ERROR] Pilihan tidak valid!\n";
                        }
                    }
                }
                cin.ignore(1000, '\n'); 

                temp->Kondisi = kondisiBaru;
                temp->Model = modelBaru;
                temp->Tahun = tahunBaru;
                currKat->NamaMerk = merkBaru;

                ditemukan = true;
                break; 
            }
        }
        if (ditemukan) break; 
    }

    if (ditemukan) {
        sinkronisasiKeCSV();
        cout << "\n[Sukses] Data unit dengan ID " << targetId << " berhasil diperbarui!\n";
    } else {
        cout << "\n[Error] Unit dengan ID " << targetId << " tidak ditemukan di sistem!\n";
    }
}