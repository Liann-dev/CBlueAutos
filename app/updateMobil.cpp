#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <iomanip>
#include <ctime> 
#include "features.h"
#include <cctype> 

using namespace std;

const string dbMobil = "database_mobil.csv";

struct DataSortTemp {
    int id;
    string merk;
    string model;
    int tahun;
    string kondisi;
    string benua;     
    string transmisi; 
    string tipe;      
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
        if (file.is_open()) file << "ID,Merk,Model,Tahun,Kondisi,Benua,Transmisi,Tipe\n";
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
            arr[idx].benua = temp->Benua;         
            arr[idx].transmisi = temp->Transmisi; 
            arr[idx].tipe = temp->Tipe;           
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
        file << "ID,Merk,Model,Tahun,Kondisi,Benua,Transmisi,Tipe\n";
        for (int i = 0; i < totalData; i++) {
            file << arr[i].id << "," 
                 << arr[i].merk << "," 
                 << arr[i].model << ","
                 << arr[i].tahun << "," 
                 << arr[i].kondisi << ","
                 << arr[i].benua << ","
                 << arr[i].transmisi << ","
                 << arr[i].tipe << "\n";
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
            // AMBIL 3 DATA BARU UNTUK DITAMPILKAN
            arr[idx].benua = temp->Benua;
            arr[idx].transmisi = temp->Transmisi;
            arr[idx].tipe = temp->Tipe;
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

        cout << "\n=========================================================================================================\n";
        cout << "                                       UPDATE UNIT MOBIL (ADMIN)                                         \n";
        cout << "=========================================================================================================\n";
        
        // --- PERBAIKAN HEADER TABEL UPDATE (8 KOLOM) ---
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
            
            // --- PERBAIKAN ISI TABEL UPDATE (8 KOLOM) ---
            cout << left << " " << setw(5) << arr[i].id << setw(15) << arr[i].merk 
                 << setw(20) << modelTeks << setw(8) << arr[i].tahun << setw(15) << arr[i].kondisi 
                 << setw(12) << arr[i].tipe << setw(12) << arr[i].transmisi << arr[i].benua << endl;
        }
        
        cout << setfill('=') << setw(105) << "=" << setfill(' ') << endl;
        cout << " Halaman " << halamanSekarang << " dari " << totalHalaman << " | Total Unit Aset: " << totalData << endl;
        cout << "---------------------------------------------------------------------------------------------------------\n";
        cout << "  [N] Next Page   |   [P] Prev Page   |   [X] Batal & Kembali\n";
        cout << "---------------------------------------------------------------------------------------------------------\n";
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
            // --- PERBAIKAN HEADER TABEL PENCARIAN (8 KOLOM) ---
            cout << left << " " << setw(5) << "ID" << setw(15) << "MERK" << setw(20) << "MODEL" 
                 << setw(8) << "TAHUN" << setw(15) << "KONDISI" << setw(12) << "TIPE" 
                 << setw(12) << "TRANSMISI" << "BENUA" << endl;
            cout << setfill('-') << setw(105) << "-" << setfill(' ') << endl;

            for (Kategori *currKat = headKategori; currKat != nullptr; currKat = currKat->next) {
                for (Mobil *temp = currKat->head; temp != nullptr; temp = temp->next) {
                    if (keHurufKecil(temp->Model).find(targetModel) != string::npos) {
                        string modelTeks = temp->Model;
                        if (modelTeks.length() > 18) modelTeks = modelTeks.substr(0, 15) + "...";
                        
                        // --- PERBAIKAN ISI TABEL PENCARIAN (8 KOLOM) ---
                        cout << left << " " << setw(5) << temp->id << setw(15) << currKat->NamaMerk 
                             << setw(20) << modelTeks << setw(8) << temp->Tahun << setw(15) << temp->Kondisi 
                             << setw(12) << temp->Tipe << setw(12) << temp->Transmisi << temp->Benua << endl;
                    }
                }
            }
            cout << setfill('-') << setw(105) << "-" << setfill(' ') << endl;
            
            cout << "Pilih angka ID mobil yang mana yang ingin diupdate (Ketik 0 untuk Batal): ";
            string inputPilihId;
            cin >> inputPilihId;
            
            stringstream ss(inputPilihId);
            if (!(ss >> targetId)) {
                cout << "[Error] Input tidak valid! Update dibatalkan.\n";
                return;
            }
            if (targetId == 0) return; 

            cin.ignore(1000, '\n'); 
        }
    }

    time_t t = time(0);
    tm* now = localtime(&t);
    int tahunSekarang = now->tm_year + 1900;

    bool ditemukan = false;
    bool dibatalkan = false;

    for (Kategori *currKat = headKategori; currKat != nullptr; currKat = currKat->next) {
        for (Mobil *temp = currKat->head; temp != nullptr; temp = temp->next) {
            
            if (temp->id == targetId) {
                int historyArray[10];
                int topIndex = -1;
                
                int step = 1;
                string inputBuffer;

                string merkBaru = "", modelBaru = "", kondisiBaru = "";
                string benuaBaru = "", transmisiBaru = "", tipeBaru = ""; 
                int tahunBaru = 0;

                while (step <= 8) {
                    #ifdef _WIN32
                        system("cls");
                    #else
                        system("clear");
                    #endif

                    cout << "\n========================================================================\n";
                    cout << "            UPDATE WIZARD - UNIT ID: " << temp->id << " (" << temp->Model << ") \n";
                    cout << "========================================================================\n";
                    cout << " [INFO] Ketik 'B' lalu Enter untuk KEMBALI (Back) ke langkah sebelumnya.\n";
                    cout << " [INFO] Tekan ENTER (Kosong) untuk mempertahankan data lama.\n";
                    cout << "------------------------------------------------------------------------\n";
                    
                    cout << left;
                    cout << " [1] Merk      (Lama: " << setw(13) << currKat->NamaMerk << ") -> " << (step > 1 ? merkBaru : "") << "\n";
                    cout << " [2] Model     (Lama: " << setw(13) << temp->Model << ") -> " << (step > 2 ? modelBaru : "") << "\n";
                    cout << " [3] Tahun     (Lama: " << setw(13) << temp->Tahun << ") -> " << (step > 3 ? to_string(tahunBaru) : "") << "\n";
                    cout << " [4] Kondisi   (Lama: " << setw(13) << temp->Kondisi << ") -> " << (step > 4 ? kondisiBaru : "") << "\n";
                    cout << " [5] Benua     (Lama: " << setw(13) << temp->Benua << ") -> " << (step > 5 ? benuaBaru : "") << "\n";
                    cout << " [6] Transmisi (Lama: " << setw(13) << temp->Transmisi << ") -> " << (step > 6 ? transmisiBaru : "") << "\n";
                    cout << " [7] Tipe Bodi (Lama: " << setw(13) << temp->Tipe << ") -> " << (step > 7 ? tipeBaru : "") << "\n";
                    cout << "------------------------------------------------------------------------\n\n";
                    if (step == 1) {
                        cout << ">>> Masukkan Merk Baru: ";
                        getline(cin, inputBuffer);
                        if (inputBuffer == "B" || inputBuffer == "b") {
                            cout << "\n[!] Ini langkah pertama. Batalkan proses update? (Y/N): ";
                            string batal; getline(cin, batal);
                            if(batal == "Y" || batal == "y") {
                                dibatalkan = true;
                                break;
                            }
                            continue;
                        }
                        merkBaru = inputBuffer.empty() ? currKat->NamaMerk : inputBuffer;
                        historyArray[++topIndex] = step; step = 2;
                    }
                    
                    else if (step == 2) {
                        cout << ">>> Masukkan Model Baru: ";
                        getline(cin, inputBuffer);
                        if (inputBuffer == "B" || inputBuffer == "b") {
                            step = historyArray[topIndex--]; continue;
                        }
                        string tempModel = inputBuffer.empty() ? temp->Model : inputBuffer;
                        
                        if (keHurufKecil(tempModel) == keHurufKecil(merkBaru)) {
                            cout << "  [ERROR] Merk dan Model tidak boleh sama!\n  Tekan Enter...";
                            getline(cin, inputBuffer);
                            continue;
                        }
                        modelBaru = tempModel;
                        historyArray[++topIndex] = step; step = 3;
                    }

                    else if (step == 3) {
                        cout << ">>> Masukkan Tahun Rilis Baru (1886 - " << tahunSekarang << "): ";
                        getline(cin, inputBuffer);
                        if (inputBuffer == "B" || inputBuffer == "b") {
                            step = historyArray[topIndex--]; continue;
                        }
                        if (inputBuffer.empty()) {
                            tahunBaru = temp->Tahun;
                            historyArray[++topIndex] = step; step = 4;
                        } else {
                            stringstream ss(inputBuffer);
                            int tempTahun;
                            if (ss >> tempTahun) {
                                if (tempTahun < 1886 || tempTahun > tahunSekarang) {
                                    cout << "  [ERROR] Tahun tidak valid!\n  Tekan Enter...";
                                    getline(cin, inputBuffer);
                                } else {
                                    tahunBaru = tempTahun;
                                    historyArray[++topIndex] = step; step = 4;
                                }
                            } else {
                                cout << "  [ERROR] Harus berupa angka valid!\n  Tekan Enter...";
                                getline(cin, inputBuffer);
                            }
                        }
                    }

                    else if (step == 4) {
                        cout << "Pilih Kondisi Baru:\n1. Brand New\n2. Mint\n3. Excellent\n4. Good\n5. Project Car\n";
                        cout << ">>> Pilihan (1-5), B (Back), atau Enter (tetap): ";
                        getline(cin, inputBuffer);
                        
                        if (inputBuffer == "B" || inputBuffer == "b") {
                            step = historyArray[topIndex--]; continue;
                        }
                        if (inputBuffer.empty()) {
                            kondisiBaru = temp->Kondisi;
                            historyArray[++topIndex] = step; step = 5;
                        } else if (inputBuffer.length() == 1 && isdigit(inputBuffer[0])) {
                            int pilihan = inputBuffer[0] - '0';
                            switch (pilihan) {
                                case 1: kondisiBaru = "Brand New"; break;
                                case 2: kondisiBaru = "Mint"; break;
                                case 3: kondisiBaru = "Excellent"; break;
                                case 4: kondisiBaru = "Good"; break;
                                case 5: kondisiBaru = "Project Car"; break;
                                default: kondisiBaru = ""; break;
                            }
                            if (kondisiBaru != "") {
                                historyArray[++topIndex] = step; step = 5;
                            } else {
                                cout << "  [ERROR] Pilihan tidak valid!\n  Tekan Enter...";
                                getline(cin, inputBuffer);
                            }
                        } else {
                            cout << "  [ERROR] Masukkan satu angka saja!\n  Tekan Enter...";
                            getline(cin, inputBuffer);
                        }
                    }

                    else if (step == 5) {
                        cout << "Pilih Benua Baru:\n1. Asia\n2. Eropa\n3. Amerika\n";
                        cout << ">>> Pilihan (1-3), B (Back), atau Enter (tetap): ";
                        getline(cin, inputBuffer);
                        
                        if (inputBuffer == "B" || inputBuffer == "b") {
                            step = historyArray[topIndex--]; continue;
                        }
                        if (inputBuffer.empty()) {
                            benuaBaru = temp->Benua;
                            historyArray[++topIndex] = step; step = 6;
                        } else if (inputBuffer.length() == 1 && isdigit(inputBuffer[0])) {
                            int pilihan = inputBuffer[0] - '0';
                            switch (pilihan) {
                                case 1: benuaBaru = "Asia"; break;
                                case 2: benuaBaru = "Eropa"; break;
                                case 3: benuaBaru = "Amerika"; break;
                                default: benuaBaru = ""; break;
                            }
                            if (benuaBaru != "") {
                                historyArray[++topIndex] = step; step = 6;
                            } else {
                                cout << "  [ERROR] Pilihan tidak valid!\n  Tekan Enter...";
                                getline(cin, inputBuffer);
                            }
                        } else {
                            cout << "  [ERROR] Masukkan satu angka saja!\n  Tekan Enter...";
                            getline(cin, inputBuffer);
                        }
                    }

                    else if (step == 6) {
                        cout << "Pilih Transmisi Baru:\n1. Manual\n2. Auto\n";
                        cout << ">>> Pilihan (1-2), B (Back), atau Enter (tetap): ";
                        getline(cin, inputBuffer);
                        
                        if (inputBuffer == "B" || inputBuffer == "b") {
                            step = historyArray[topIndex--]; continue;
                        }
                        if (inputBuffer.empty()) {
                            transmisiBaru = temp->Transmisi;
                            historyArray[++topIndex] = step; step = 7;
                        } else if (inputBuffer.length() == 1 && isdigit(inputBuffer[0])) {
                            int pilihan = inputBuffer[0] - '0';
                            switch (pilihan) {
                                case 1: transmisiBaru = "Manual"; break;
                                case 2: transmisiBaru = "Auto"; break;
                                default: transmisiBaru = ""; break;
                            }
                            if (transmisiBaru != "") {
                                historyArray[++topIndex] = step; step = 7;
                            } else {
                                cout << "  [ERROR] Pilihan tidak valid!\n  Tekan Enter...";
                                getline(cin, inputBuffer);
                            }
                        } else {
                            cout << "  [ERROR] Masukkan satu angka saja!\n  Tekan Enter...";
                            getline(cin, inputBuffer);
                        }
                    }

                    else if (step == 7) {
                        cout << "Pilih Tipe Bodi Baru:\n1. SUV\n2. Sedan\n3. Hatchback\n4. MPV\n5. Sport\n";
                        cout << ">>> Pilihan (1-5), B (Back), atau Enter (tetap): ";
                        getline(cin, inputBuffer);
                        
                        if (inputBuffer == "B" || inputBuffer == "b") {
                            step = historyArray[topIndex--]; continue;
                        }
                        if (inputBuffer.empty()) {
                            tipeBaru = temp->Tipe;
                            historyArray[++topIndex] = step; step = 8; // PERUBAHAN: Maju ke State 8
                        } else if (inputBuffer.length() == 1 && isdigit(inputBuffer[0])) {
                            int pilihan = inputBuffer[0] - '0';
                            switch (pilihan) {
                                case 1: tipeBaru = "SUV"; break;
                                case 2: tipeBaru = "Sedan"; break;
                                case 3: tipeBaru = "Hatchback"; break;
                                case 4: tipeBaru = "MPV"; break;
                                case 5: tipeBaru = "Sport"; break;
                                default: tipeBaru = ""; break;
                            }
                            if (tipeBaru != "") {
                                historyArray[++topIndex] = step; step = 8; // PERUBAHAN: Maju ke State 8
                            } else {
                                cout << "  [ERROR] Pilihan tidak valid!\n  Tekan Enter...";
                                getline(cin, inputBuffer);
                            }
                        } else {
                            cout << "  [ERROR] Masukkan satu angka saja!\n  Tekan Enter...";
                            getline(cin, inputBuffer);
                        }
                    }


                    else if (step == 8) {
                        cout << ">>> [INFO] Semua data telah diisi.\n";
                        cout << ">>> Tekan Enter untuk MENYIMPAN perubahan, atau ketik 'B' untuk kembali mengubah Tipe: ";
                        getline(cin, inputBuffer);
                        
                        if (inputBuffer == "B" || inputBuffer == "b") {
                            step = historyArray[topIndex--]; continue;
                        }
                        break; 
                    }
                } 

                if (!dibatalkan && step >= 8) {
                    temp->Kondisi = kondisiBaru;
                    temp->Model = modelBaru;
                    temp->Tahun = tahunBaru;
                    currKat->NamaMerk = merkBaru;
                    temp->Benua = benuaBaru;         
                    temp->Transmisi = transmisiBaru; 
                    temp->Tipe = tipeBaru;           
                    ditemukan = true;
                }
                
                break; 
            }
        }
        if (ditemukan || dibatalkan) break; 
    }

    if (ditemukan) {
        sinkronisasiKeCSV(); 
        cout << "\n[Sukses] Data unit dengan ID " << targetId << " berhasil diperbarui!\n";
        cout << "Tekan Enter untuk kembali...";
        string pauseBuffer;
        getline(cin, pauseBuffer);
    } else if (dibatalkan) {
        cout << "\n[Info] Update unit telah dibatalkan oleh Admin.\n";
        cout << "Tekan Enter untuk kembali...";
        string pauseBuffer;
        getline(cin, pauseBuffer);
    } else {
        cout << "\n[Error] Unit dengan ID " << targetId << " tidak ditemukan di sistem!\n";
    }
}