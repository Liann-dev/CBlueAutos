#include <iostream>
#include <string>
#include <algorithm>
#include <iomanip>
#include <fstream>
#include <sstream>
#include <ctime>
#include <cctype>
#include "features.h"

using namespace std;

const string dbMobil = "database_mobil.csv";

int getNextMobilId()
{
    ifstream file(dbMobil.c_str());
    string line;
    int jumlah = 0;

    if (!file.is_open()) return 1;

    getline(file, line);
    while (getline(file, line)) {
        jumlah++;
    }
    return jumlah + 1;
}

void tambahMobilAdmin()
{
    int historyArray[10]; 
    int topIndex = -1;    
    int step = 1;

    string merkBaru = "", modelBaru = "", kondisiBaru = "";
    string benuaBaru = "", transmisiBaru = "", tipeBaru = ""; 
    int tahunBaru = 0;
    
    string inputBuffer;

    time_t t = time(0);
    tm* now = localtime(&t);
    int tahunSekarang = now->tm_year + 1900; 

    while (step <= 7) {
        #ifdef _WIN32
            system("cls");
        #else
            system("clear");
        #endif

        cout << "\n======================================================\n";
        cout << "              TAMBAH UNIT MOBIL (ADMIN)               \n";
        cout << "======================================================\n";
        cout << " [INFO] Ketik 'B' lalu Enter untuk KEMBALI (Back).\n";
        cout << "------------------------------------------------------\n";
        
        if (step > 1) cout << " [1] Merk      : " << merkBaru << endl;
        if (step > 2) cout << " [2] Model     : " << modelBaru << endl;
        if (step > 3) cout << " [3] Tahun     : " << tahunBaru << endl;
        if (step > 4) cout << " [4] Kondisi   : " << kondisiBaru << endl;
        if (step > 5) cout << " [5] Benua     : " << benuaBaru << endl;
        if (step > 6) cout << " [6] Transmisi : " << transmisiBaru << endl;
        if (step > 7) cout << " [7] Tipe      : " << tipeBaru << endl;
        cout << "------------------------------------------------------\n\n";

        if (step == 1) {
            cout << ">>> Masukkan Nama Merk: ";
            getline(cin, inputBuffer);
            
            if (inputBuffer == "B" || inputBuffer == "b") {
                cout << "\n[!] Ini langkah pertama. Ingin batalkan tambah mobil? (Y/N): ";
                string batal;
                getline(cin, batal);
                if(batal == "Y" || batal == "y") return;
                continue;
            }
            if (inputBuffer.empty()) continue;
            
            merkBaru = inputBuffer;
            // PUSH ke custom stack
            historyArray[++topIndex] = step; 
            step = 2;           
        }
        
        else if (step == 2) {
            cout << ">>> Masukkan Nama Model: ";
            getline(cin, inputBuffer);

            if (inputBuffer == "B" || inputBuffer == "b") {
                // POP dari custom stack
                step = historyArray[topIndex--]; 
                modelBaru = "";       
                continue;
            }
            if (inputBuffer.empty()) continue;
            
            if (keHurufKecil(inputBuffer) == keHurufKecil(merkBaru)) {
                cout << "  [ERROR] Merk dan Model tidak boleh sama!\n  Tekan Enter...";
                getline(cin, inputBuffer);
                continue;
            }

            modelBaru = inputBuffer;
            historyArray[++topIndex] = step;
            step = 3;
        }
        else if (step == 3) {
            cout << ">>> Masukkan Tahun Rilis (1886 - " << tahunSekarang << "): ";
            getline(cin, inputBuffer);

            if (inputBuffer == "B" || inputBuffer == "b") {
                step = historyArray[topIndex--];
                tahunBaru = 0; 
                continue;
            }
            if (inputBuffer.empty()) continue;

            stringstream ss(inputBuffer);
            int tempTahun;
            if (ss >> tempTahun) {
                if (tempTahun < 1886 || tempTahun > tahunSekarang) {
                    cout << "  [ERROR] Tahun tidak valid!\n  Tekan Enter...";
                    getline(cin, inputBuffer);
                } else {
                    tahunBaru = tempTahun;
                    historyArray[++topIndex] = step;
                    step = 4;
                }
            } else {
                cout << "  [ERROR] Harus berupa angka!\n  Tekan Enter...";
                getline(cin, inputBuffer);
            }
        }

        else if (step == 4) {
            cout << "Pilih Kondisi Mobil:\n";
            cout << "1. Brand New\n2. Mint\n3. Excellent\n4. Good\n5. Project Car\n";
            cout << ">>> Masukkan pilihan (1-5) atau B: ";
            getline(cin, inputBuffer);

            if (inputBuffer == "B" || inputBuffer == "b") {
                step = historyArray[topIndex--];
                kondisiBaru = ""; 
                continue;
            }

            if (inputBuffer.length() == 1 && isdigit(inputBuffer[0])) {
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
                    historyArray[++topIndex] = step;
                    step = 5;
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
            cout << "Pilih Asal Benua:\n";
            cout << "1. Asia\n2. Eropa\n3. Amerika\n";
            cout << ">>> Masukkan pilihan (1-3) atau B: ";
            getline(cin, inputBuffer);

            if (inputBuffer == "B" || inputBuffer == "b") {
                step = historyArray[topIndex--];
                benuaBaru = ""; 
                continue;
            }

            if (inputBuffer.length() == 1 && isdigit(inputBuffer[0])) {
                int pilihan = inputBuffer[0] - '0';
                switch (pilihan) {
                    case 1: benuaBaru = "Asia"; break;
                    case 2: benuaBaru = "Eropa"; break;
                    case 3: benuaBaru = "Amerika"; break;
                    default: benuaBaru = ""; break;
                }
                if (benuaBaru != "") {
                    historyArray[++topIndex] = step;
                    step = 6;
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
            cout << "Pilih Jenis Transmisi:\n";
            cout << "1. Manual\n2. Auto\n";
            cout << ">>> Masukkan pilihan (1-2) atau B: ";
            getline(cin, inputBuffer);

            if (inputBuffer == "B" || inputBuffer == "b") {
                step = historyArray[topIndex--];
                transmisiBaru = ""; 
                continue;
            }

            if (inputBuffer.length() == 1 && isdigit(inputBuffer[0])) {
                int pilihan = inputBuffer[0] - '0';
                switch (pilihan) {
                    case 1: transmisiBaru = "Manual"; break;
                    case 2: transmisiBaru = "Auto"; break;
                    default: transmisiBaru = ""; break;
                }
                if (transmisiBaru != "") {
                    historyArray[++topIndex] = step;
                    step = 7;
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
            cout << "Pilih Tipe Bodi:\n";
            cout << "1. SUV\n2. Sedan\n3. Hatchback\n4. MPV\n5. Sport\n";
            cout << ">>> Masukkan pilihan (1-5) atau B: ";
            getline(cin, inputBuffer);

            if (inputBuffer == "B" || inputBuffer == "b") {
                step = historyArray[topIndex--];
                tipeBaru = ""; 
                continue;
            }

            if (inputBuffer.length() == 1 && isdigit(inputBuffer[0])) {
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
                    break; 
                } else {
                    cout << "  [ERROR] Pilihan tidak valid!\n  Tekan Enter...";
                    getline(cin, inputBuffer);
                }
            } else {
                cout << "  [ERROR] Masukkan satu angka saja!\n  Tekan Enter...";
                getline(cin, inputBuffer);
            }
        }
    }

    int idBaru = getNextMobilId();

    bool perluNewline = false;
    ifstream fileCek(dbMobil.c_str(), ios::binary);
    if (fileCek.is_open()) {
        fileCek.seekg(0, ios::end);
        if (fileCek.tellg() > 0) {
            fileCek.seekg(-1, ios::cur);
            char lastChar;
            fileCek.get(lastChar);
            if (lastChar != '\n') perluNewline = true;
        }
        fileCek.close();
    }

    ofstream file(dbMobil.c_str(), ios::app);
    if (file.is_open()) {
        if (perluNewline) file << "\n";

        file << idBaru << ","
             << merkBaru << ","
             << modelBaru << ","
             << tahunBaru << ","
             << kondisiBaru << ","
             << benuaBaru << ","
             << transmisiBaru << ","
             << tipeBaru << "\n";
        file.close();

        Kategori *kat = cariAtauBuatKategori(merkBaru);
        Mobil *baru = new Mobil;
        baru->id = idBaru;
        baru->Merk = merkBaru;
        baru->Model = modelBaru;
        baru->Tahun = tahunBaru;
        baru->Kondisi = kondisiBaru;
        baru->Benua = benuaBaru;         
        baru->Transmisi = transmisiBaru; 
        baru->Tipe = tipeBaru;           

        baru->next = kat->head;
        baru->prev = nullptr;
        if (kat->head != nullptr) kat->head->prev = baru;
        kat->head = baru;

        #ifdef _WIN32
            system("cls");
        #else
            system("clear");
        #endif
        cout << "\n======================================================\n";
        cout << " [SUKSES] Unit dengan ID " << idBaru << " berhasil ditambahkan!\n";
        cout << "======================================================\n";
        
        cout << "\nTekan Enter untuk kembali ke menu...";
        string pauseBuffer;
        getline(cin, pauseBuffer);
    }
    else {
        cout << "\n[ERROR] Gagal membuka file database_mobil.csv!" << endl;
    }
}