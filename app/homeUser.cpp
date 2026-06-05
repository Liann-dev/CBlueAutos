#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include <fstream>
#include <iomanip>
#include <thread>  
#include <chrono>  
#include <windows.h>
#include <cctype>
#include "homeUser.h"
#include "features.h"

using namespace std;
string namaFile = "database_prefensi.csv";

extern void tampilkanDetailMobil(int idTarget); 

void integrasiDatabase(int idUser, string referensi[3]) {
    ifstream fileBaca(namaFile);
    string line;
    int lastId = 0;

    getline(fileBaca, line);
    while (getline(fileBaca, line)) {
        if (!line.empty()) lastId++;
    }
    fileBaca.close();

    int id = lastId + 1;
    ofstream fileTulis(namaFile, ios::app);
    fileTulis << id << "," << idUser << ","
              << referensi[0] << "|" << referensi[1] << "|" << referensi[2] << "\n";
    fileTulis.close();
}

void tampilkanPreferensiTag(int id_user) {
    #ifdef _WIN32
        system("cls");
    #else
        system("clear");
    #endif

    cout << "\n=======================================================================\n";
    cout << "               WELCOME! LET'S BUILD YOUR DREAM GARAGE\n";
    cout << "=======================================================================\n";
    cout << "Select 1 to 3 tags that best describe your automotive taste\n";
    cout << "so we can recommend the perfect cars for you!\n\n";

    vector<string> styles = {
        "JDM", "Muscle", "Aero", "Relaxed", "Responsive",
        "City", "Family", "Modern Car", "Luxury", "Performance",
        "Classic Car", "National Car", "Aerodinamis", "Elegant", "For Hobbyists",
        "Like New", "High Ground"
    };

    int total    = styles.size();
    int rows     = 5;
    int colWidth = 22;
    int numCols  = (total + rows - 1) / rows;

    for (int r = 0; r < rows; r++) {
        for (int c = 0; c < numCols; c++) {
            int idx = c * rows + r;
            if (idx < total) {
                string entry = to_string(idx + 1) + ". " + styles[idx];
                cout << left << setw(colWidth) << entry;
            }
        }
        cout << "\n";
    }

    string input;
    cout << "\nChoices (Pilih 1 hingga 3 angka, pisahkan spasi, contoh: 1 5): ";
    getline(cin, input);

    while (true) {
        stringstream ss(input);
        int angka;
        int inputs[3];
        int jumlahTag = 0;
        bool valid = true;

        while (ss >> angka) {
            if (angka < 1 || angka > total) {
                valid = false;
                break;
            }
            if (jumlahTag < 3) {
                inputs[jumlahTag] = angka;
            }
            jumlahTag++;
        }

        if (!valid || jumlahTag == 0 || jumlahTag > 3) {
            cout << "\n[!] Input tidak valid! Anda harus memilih 1 hingga maksimal 3 angka (1-" << total << ").\n";
            cout << "Coba lagi: ";
            getline(cin, input);
            continue;
        }

        string tags[3] = {"", "", ""}; 
        for (int i = 0; i < jumlahTag; i++) {
            tags[i] = styles[inputs[i] - 1];
        }

        integrasiDatabase(id_user, tags);
        break;
    }
}

void menuUtama(string role, string login_count, int id_user) {
    string inputBuffer;

    if (login_count == "1") {
        tampilkanPreferensiTag(id_user);
        
        cout << "\n[+] Preferensi Anda berhasil disimpan!\n";
        cout << "\nMenyiapkan profil dan preferensi Anda...\n";
        Sleep(1000);
        
        #ifdef _WIN32
            system("cls");
        #else
            system("clear");
        #endif
        
        cout << "\n\n";
        string padding = "                    ";
        cout << padding << "Membangun Garasi Impian Anda...\n";
        cout << "\033[?25l"; 
        for(int i = 0; i <= 25; i++) {
            cout << "\r" << padding << "[" << string(i, '=') << string(25-i, ' ') << "] " << (i*4) << "%";
            cout.flush();
            Sleep(50);
        }
        cout << "\033[?25h\n\n"; 
    }

    bool tetapDiHome = true;

    while (tetapDiHome) {
        #ifdef _WIN32
            system("cls");
        #else
            system("clear");
        #endif

        recomendation(id_user);
        cout << "========================================================================\n";
        cout << "       CBLUEAUTOS - DASHBOARD UTAMA\n";
        cout << "========================================================================\n";
        cout << " [K] Lihat Semua Koleksi (Katalog)\n";
        cout << " [S] Search Mobil\n";
        cout << " [F] Filter Mobil\n";
        cout << " [L] Logout\n";
        cout << "========================================================================\n";
        cout << " Ketik ID Mobil untuk melihat spesifikasi detail, atau pilih menu (K/S/F/L): ";

        getline(cin, inputBuffer);
        if (inputBuffer.empty()) continue;

        bool isAngka = true;
        for(char c : inputBuffer) {
            if(!isdigit(c) && c != ' ') {
                isAngka = false;
                break;
            }
        }
        if (isAngka) {
            int idPilihan = -1;
            stringstream ss(inputBuffer);
            if (ss >> idPilihan) { 
                tampilkanDetailMobil(idPilihan); 
            }
        } else {
            char menu = toupper(inputBuffer[0]);
            if (menu == 'K') {
                tampilkanKatalog();
            }
            else if (menu == 'S') {
                cariMobil();
            }
            else if (menu == 'F') {
                filterMobil();
            }
            else if (menu == 'L') {
                cout << "\nMenyimpan sesi...\nLogout berhasil!\n";
                tetapDiHome = false;
            }
            else {
                cout << "[!] Pilihan tidak valid. Tekan Enter untuk mengulang...";
                getline(cin, inputBuffer);
            }
        }
    }
}