#include <iostream>
#include <string>
#include <iomanip>
#include "features.h"

using namespace std;

// Memakai struct bantuan untuk Array dinamis
struct DataSortTempHapus {
    int id;
    string merk;
    string model;
    int tahun;
    string kondisi;
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

    // SISTEM PAGINATION + INPUT ID SEKALIGUS
    while (true) {
        #ifdef _WIN32
            system("cls");
        #else
            system("clear");
        #endif

        cout << "\n===========================================================================\n";
        cout << "                         HAPUS UNIT MOBIL (ADMIN)                          \n";
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
    
    delete[] arr; // Bebaskan memori array

    // --- PROSES HAPUS DIMULAI ---
    bool ditemukan = false;

    // Pencarian langsung di dalam Linked List memori
    for (Kategori *currKat = headKategori; currKat != nullptr; currKat = currKat->next) {
        Mobil *temp = currKat->head;
        Mobil *prev = nullptr;

        while (temp != nullptr) {
            if (temp->id == targetId) {
                // Proses hapus di Doubly Linked List
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
            break;
        }
    }

    if (!ditemukan) {
        cout << "\n[Error] Unit dengan ID " << targetId << " tidak ditemukan!\n";
    }
}