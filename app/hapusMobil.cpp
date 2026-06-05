#include <iostream>
#include <string>
#include <iomanip>
#include "features.h"

using namespace std;

struct DataSortTempHapus {
    int id;
    string merk;
    string model;
    int tahun;
    string kondisi;
    string benua;     
    string transmisi; 
    string tipe;      
};

void hapusMobilAdmin()
{
    int totalData = 0;
    for (Kategori *currKat = headKategori; currKat != nullptr; currKat = currKat->next) {
        for (Mobil *temp = currKat->head; temp != nullptr; temp = temp->next) {
            totalData++;
        }
    }

    if (totalData == 0) {
        cout << "[Info] Tidak ada data mobil di dalam database/showroom.\n";
        return; 
    }

    DataSortTempHapus* arr = new DataSortTempHapus[totalData];
    int idx = 0;
    for (Kategori *currKat = headKategori; currKat != nullptr; currKat = currKat->next) {
        for (Mobil *temp = currKat->head; temp != nullptr; temp = temp->next) {
            arr[idx].id = temp->id;
            arr[idx].merk = currKat->NamaMerk;
            arr[idx].model = temp->Model;
            arr[idx].tahun = temp->Tahun;
            arr[idx].kondisi = temp->Kondisi;
            arr[idx].benua = temp->Benua;
            arr[idx].transmisi = temp->Transmisi;
            arr[idx].tipe = temp->Tipe;
            idx++;
        }
    }

    // Bubble Sort
    for (int i = 0; i < totalData - 1; i++) {
        for (int j = 0; j < totalData - i - 1; j++) {
            if (arr[j].id > arr[j + 1].id) {
                DataSortTempHapus temp = arr[j];
                arr[j] = arr[j + 1];
                arr[j + 1] = temp;
            }
        }
    }

    int itemPerHalaman = 10;
    int totalHalaman = (totalData + itemPerHalaman - 1) / itemPerHalaman;
    int halamanSekarang = 1;
    int targetId = -1;
    string pilihan;

    while (true) {
        #ifdef _WIN32
            system("cls");
        #else
            system("clear");
        #endif

        cout << "\n=========================================================================================================\n";
        cout << "                                       HAPUS UNIT MOBIL (ADMIN)                                          \n";
        cout << "=========================================================================================================\n";
        
        // --- PERBAIKAN HEADER TABEL (8 KOLOM) ---
        cout << left << " " << setw(5) << "ID" << setw(15) << "MERK" << setw(20) << "MODEL" 
             << setw(8) << "TAHUN" << setw(15) << "KONDISI" << setw(12) << "TIPE" 
             << setw(12) << "TRANSMISI" << "BENUA" << endl;
        cout << setfill('-') << setw(105) << "-" << setfill(' ') << endl;

        int startIdx = (halamanSekarang - 1) * itemPerHalaman;
        int endIdx = startIdx + itemPerHalaman;
        if (endIdx > totalData) endIdx = totalData;

        for (int i = startIdx; i < endIdx; i++) {
            string modelTeks = arr[i].model;
            if (modelTeks.length() > 18) modelTeks = modelTeks.substr(0, 15) + "...";
            
            // --- PERBAIKAN ISI TABEL (8 KOLOM) ---
            cout << left << " " << setw(5) << arr[i].id << setw(15) << arr[i].merk 
                 << setw(20) << modelTeks << setw(8) << arr[i].tahun << setw(15) << arr[i].kondisi 
                 << setw(12) << arr[i].tipe << setw(12) << arr[i].transmisi << arr[i].benua << endl;
        }
        
        cout << setfill('=') << setw(105) << "=" << setfill(' ') << endl;
        cout << " Halaman " << halamanSekarang << " dari " << totalHalaman << " | Total Unit Aset: " << totalData << endl;
        cout << "---------------------------------------------------------------------------------------------------------\n";
        cout << "  [N] Next Page   |   [P] Prev Page   |   [X] Batal & Kembali\n";
        cout << "---------------------------------------------------------------------------------------------------------\n";
        cout << "Ketik 'N' / 'P' atau masukkan angka ID untuk dihapus: ";
        cin >> pilihan;

        if (pilihan == "X" || pilihan == "x") {
            delete[] arr; 
            return; 
        } else if (pilihan == "n" || pilihan == "N") {
            if (halamanSekarang < totalHalaman) halamanSekarang++;
        } else if (pilihan == "p" || pilihan == "P") {
            if (halamanSekarang > 1) halamanSekarang--;
        } else {
            try {
                targetId = stoi(pilihan);
                break;
            } catch (...) {
                
            }
        }
    }
    
    delete[] arr; 

    bool ditemukan = false;

    for (Kategori *currKat = headKategori; currKat != nullptr; currKat = currKat->next) {
        Mobil *temp = currKat->head;
        Mobil *prev = nullptr;

        while (temp != nullptr) {
            if (temp->id == targetId) {
                if (prev == nullptr) {
                    currKat->head = temp->next;
                    if (currKat->head != nullptr) {
                        currKat->head->prev = nullptr;
                    }
                } else {
                    prev->next = temp->next;
                    if (temp->next != nullptr) {
                        temp->next->prev = prev;
                    }
                }
                
                string modelDihapus = temp->Model; 
                delete temp;
                ditemukan = true;
                
                cout << "\n[Sukses] Unit '" << modelDihapus << "' (ID: " << targetId << ") berhasil dihapus.\n";
                break;
            }
            prev = temp;
            temp = temp->next;
        }
        
        if (ditemukan) {
            sinkronisasiKeCSV(); 
            
            cout << "Tekan Enter untuk kembali...";
            string pauseBuffer;
            cin.ignore(1000, '\n');
            getline(cin, pauseBuffer);
            break;
        }
    }

    if (!ditemukan) {
        cout << "\n[Error] Unit dengan ID " << targetId << " tidak ditemukan!\n";
        cout << "Tekan Enter untuk kembali...";
        string pauseBuffer;
        cin.ignore(1000, '\n');
        getline(cin, pauseBuffer);
    }
}