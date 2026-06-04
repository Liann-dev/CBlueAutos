#include <iostream>
#include <string>
#include <algorithm>
#include <iomanip>
#include <fstream>
#include <sstream>
#include <vector>
#include <set>
#include "features.h"

using namespace std;

struct TreeAdmin {
    string id;
    string merk;
    string model;
    string tahun;
    string kondisi;
    string tipe;
    string transmisi;
    string benua;
    
    TreeAdmin *left;
    TreeAdmin *right;
};

void deklarasiTreeAdmin(TreeAdmin* &pohon) {
    pohon = nullptr;
}

void insertTreeAdmin(TreeAdmin** pohon, string id, string merk, string model, string tahun, string kondisi, string tipe, string transmisi, string benua) {
    if (*pohon == nullptr) {
        TreeAdmin *new_node = new TreeAdmin;
        new_node->id = id;
        new_node->merk = merk;
        new_node->model = model;
        new_node->tahun = tahun;
        new_node->kondisi = kondisi;
        new_node->tipe = tipe;
        new_node->transmisi = transmisi;
        new_node->benua = benua;
        new_node->left = nullptr;
        new_node->right = nullptr;
        *pohon = new_node;
    } 
    else {
        int idBaru = stoi(id);
        int idCurr = stoi((*pohon)->id);
        
        if (idBaru < idCurr) {
            insertTreeAdmin(&(*pohon)->left, id, merk, model, tahun, kondisi, tipe, transmisi, benua);
        } else {
            insertTreeAdmin(&(*pohon)->right, id, merk, model, tahun, kondisi, tipe, transmisi, benua);
        }
    }
}

void deleteTreeAdmin(TreeAdmin* &pohon) {
    if (pohon != nullptr) {
        deleteTreeAdmin(pohon->left);
        deleteTreeAdmin(pohon->right);
        delete pohon;
        pohon = nullptr;
    }
}

void cariMobilAdmin() {
    string inputBuffer;

    while (true) {
        #ifdef _WIN32
            system("cls");
        #else
            system("clear");
        #endif

        cout << "\n========================================\n";
        cout << "         PENCARIAN STOK MOBIL           \n";
        cout << "========================================\n";
        cout << " 1. Cari Mobil (Berdasarkan Model)\n";
        cout << " 0. Kembali ke Beranda Admin\n";
        cout << "----------------------------------------\n";
        cout << "Pilihan: ";

        getline(cin, inputBuffer);
        if (inputBuffer.empty()) continue;

        int pilihanMenu = -1;
        try {
            pilihanMenu = stoi(inputBuffer);
        } catch (...) {
            continue;
        }

        if (pilihanMenu == 0) {
            return;
        } 
        else if (pilihanMenu == 1) {
            cout << "\nMasukkan Model ('0' untuk semua, atau tekan Enter untuk batal): ";
            getline(cin, inputBuffer);

            if (inputBuffer.empty()) {
                continue; 
            }

            string keyKecil = keHurufKecil(inputBuffer);

            #ifdef _WIN32
                system("cls");
            #else
                system("clear");
            #endif

            cout << "\n" << setfill('=') << setw(105) << "=" << setfill(' ') << endl;
            cout << left << " " << setw(5) << "ID" << setw(15) << "MERK" << setw(20) << "MODEL" 
                 << setw(8) << "TAHUN" << setw(15) << "KONDISI" << setw(12) << "TIPE" 
                 << setw(12) << "TRANSMISI" << "BENUA" << endl;
            cout << setfill('-') << setw(105) << "-" << setfill(' ') << endl;

            int counter = 0;

            for (Kategori* currKat = headKategori; currKat != nullptr; currKat = currKat->next) {
                for (Mobil* temp = currKat->head; temp != nullptr; temp = temp->next) {
                    string modelKecil = keHurufKecil(temp->Model);

                    if (keyKecil == "0" || modelKecil.find(keyKecil) != string::npos) {
                        counter++;
                        
                        string modelTeks = temp->Model;
                        if (modelTeks.length() > 18) modelTeks = modelTeks.substr(0, 15) + "...";

                        cout << left << " " << setw(5) << temp->id << setw(15) << currKat->NamaMerk 
                             << setw(20) << modelTeks << setw(8) << temp->Tahun << setw(15) << temp->Kondisi 
                             << setw(12) << temp->Tipe << setw(12) << temp->Transmisi << temp->Benua << endl;
                    }
                }
            }

            if (counter > 0) {
                cout << setfill('=') << setw(105) << "=" << setfill(' ') << endl;
                cout << "Berhasil menemukan " << counter << " unit." << endl;
            } else {
                cout << setfill('=') << setw(105) << "=" << setfill(' ') << endl;
                cout << "[!] Tidak ada mobil yang sesuai dengan kriteria tersebut." << endl;
            }

            cout << "\nTekan Enter untuk kembali ke Menu Pencarian...";
            getline(cin, inputBuffer);
        } 
        else {
            cout << "\n[!] Pilihan tidak valid. Tekan Enter untuk mengulang...";
            getline(cin, inputBuffer);
        }
    }
}

vector<string> ambilOpsiAdmin(int kolom) {
    set<string> unik;
    ifstream file("database_mobil.csv");
    string line;

    if (!file.is_open()) return {};

    getline(file, line);

    while (getline(file, line)) {
        stringstream ss(line);
        string temp;
        int i = 0;

        while (getline(ss, temp, ',')) {
            if (i == kolom && !temp.empty()) {
                unik.insert(temp);
            }
            i++;
        }
    }

    return vector<string>(unik.begin(), unik.end());
}

void traversalFilterAdmin(TreeAdmin* pohon, int pilihanFilter, int pilihanTahun, string kriteria, int &count) {
    if (pohon == nullptr) return;

    traversalFilterAdmin(pohon->left, pilihanFilter, pilihanTahun, kriteria, count);

    bool cocok = false;

    if (pilihanFilter == 1) {
        int tahunMobil = stoi(pohon->tahun);
        if (pilihanTahun == 1) cocok = true;
        else if (pilihanTahun == 2) cocok = (tahunMobil >= 2000);
        else if (pilihanTahun == 3) cocok = (tahunMobil < 2000);
    } 
    else if (pilihanFilter == 2) {
        cocok = (pohon->merk == kriteria);
    } 
    else if (pilihanFilter == 3) {
        cocok = (pohon->kondisi == kriteria);
    } 
    else if (pilihanFilter == 4) {
        cocok = (pohon->tipe == kriteria);
    } 
    else if (pilihanFilter == 5) {
        cocok = (pohon->transmisi == kriteria);
    } 
    else if (pilihanFilter == 6) {
        cocok = (pohon->benua == kriteria);
    }

    if (cocok) {
        count++;
        
        string modelTeks = pohon->model;
        if (modelTeks.length() > 18) modelTeks = modelTeks.substr(0, 15) + "...";

        cout << left << " " << setw(5) << pohon->id << setw(15) << pohon->merk 
             << setw(20) << modelTeks << setw(8) << pohon->tahun << setw(15) << pohon->kondisi 
             << setw(12) << pohon->tipe << setw(12) << pohon->transmisi << pohon->benua << endl;
    }

    traversalFilterAdmin(pohon->right, pilihanFilter, pilihanTahun, kriteria, count);
}

void filterMobilAdmin() {
    int pilihan;

    cout << "\n=== FILTER STOK MOBIL===\n";
    cout << "1. Berdasarkan Tahun\n";
    cout << "2. Berdasarkan Merk\n";
    cout << "3. Berdasarkan Kondisi\n";
    cout << "4. Berdasarkan Benua\n";
    cout << "5. Berdasarkan Transmisi\n";
    cout << "6. Berdasarkan Tipe\n";
    cout << "0. Kembali\n";
    cout << "Pilih: ";
    cin >> pilihan;

    if (pilihan == 0) return;

    string kriteria = "";
    int pilihanTahun = 0;

    if (pilihan == 1) {
        cout << "\n1. Semua\n";
        cout << "2. Tahun >= 2000\n";
        cout << "3. Tahun < 2000\n";
        cout << "Pilih: ";
        cin >> pilihanTahun;
    }
    else if (pilihan == 2) {
        vector<string> opsi = ambilOpsiAdmin(1);
        if (opsi.empty()) {
            cout << "[!] Data merk tidak ada.\n";
            return;
        }
        cout << "\nPilih Merk:\n";
        for (size_t i = 0; i < opsi.size(); i++) {
            cout << i + 1 << ". " << opsi[i] << endl;
        }
        int pilih;
        cout << "Pilih: ";
        cin >> pilih;
        kriteria = opsi[pilih - 1];
    }
    else if (pilihan == 3) {
        cout << "\n1. Brand New\n2. Mint\n3. Excellent\n4. Good\n5. Project Car\n";
        int pilih;
        cout << "Pilih: ";
        cin >> pilih;
        string kondisi[] = {"Brand New", "Mint", "Excellent", "Good", "Project Car"};
        kriteria = kondisi[pilih - 1];
    }
    else if (pilihan == 4) {
        vector<string> opsi = ambilOpsiAdmin(5);
        if (opsi.empty()) {
            cout << "[!] Data tipe tidak ada.\n";
            return;
        }
        cout << "\nPilih Tipe:\n";
        for (size_t i = 0; i < opsi.size(); i++) {
            cout << i + 1 << ". " << opsi[i] << endl;
        }
        int pilih;
        cout << "Pilih: ";
        cin >> pilih;
        kriteria = opsi[pilih - 1];
    }
    else if (pilihan == 5) {
        vector<string> opsi = ambilOpsiAdmin(6);
        if (opsi.empty()) {
            cout << "[!] Data transmisi tidak ada.\n";
            return;
        }
        cout << "\nPilih Transmisi:\n";
        for (size_t i = 0; i < opsi.size(); i++) {
            cout << i + 1 << ". " << opsi[i] << endl;
        }
        int pilih;
        cout << "Pilih: ";
        cin >> pilih;
        kriteria = opsi[pilih - 1];
    }
    else if (pilihan == 6) {
        vector<string> opsi = ambilOpsiAdmin(7);
        if (opsi.empty()) {
            cout << "[!] Data benua tidak ada.\n";
            return;
        }
        cout << "\nPilih Benua:\n";
        for (size_t i = 0; i < opsi.size(); i++) {
            cout << i + 1 << ". " << opsi[i] << endl;
        }
        int pilih;
        cout << "Pilih: ";
        cin >> pilih;
        kriteria = opsi[pilih - 1];
    }

    TreeAdmin *pohonUtama;
    deklarasiTreeAdmin(pohonUtama);

    ifstream file("database_mobil.csv");
    string line;
    getline(file, line);

    while (getline(file, line)) {
        stringstream ss(line);
        string data[8];

        for (int i = 0; i < 8; i++) {
            getline(ss, data[i], ',');
        }

        insertTreeAdmin(&pohonUtama, data[0], data[1], data[2], data[3], data[4], data[5], data[6], data[7]);
    }
    file.close();

    cout << "\n" << setfill('=') << setw(105) << "=" << endl;
    cout << left << " " << setw(5) << "ID" << setw(15) << "MERK" << setw(20) << "MODEL" 
         << setw(8) << "TAHUN" << setw(15) << "KONDISI" << setw(12) << "TIPE" 
         << setw(12) << "TRANSMISI" << "BENUA" << endl;
    cout << setfill('-') << setw(105) << "-" << setfill(' ') << endl;

    int count = 0;
    
    traversalFilterAdmin(pohonUtama, pilihan, pilihanTahun, kriteria, count);

    cout << setfill('=') << setw(105) << "=" << setfill(' ') << endl;
    cout << "Total: " << count << " unit\n";

    deleteTreeAdmin(pohonUtama);
}