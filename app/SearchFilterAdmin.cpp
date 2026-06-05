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
        cout << " [1] Cari Mobil (Berdasarkan Model)\n";
        cout << "----------------------------------------\n";
        cout << " Pilih (0 atau Enter untuk Kembali): ";

        getline(cin, inputBuffer);
        if (inputBuffer.empty() || inputBuffer == "0") return;

        int pilihanMenu = -1;
        try {
            pilihanMenu = stoi(inputBuffer);
        } catch (...) {
            continue;
        }

        if (pilihanMenu == 1) {
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
                cout << " Berhasil menemukan " << counter << " unit." << endl;
            } else {
                cout << setfill('=') << setw(105) << "=" << setfill(' ') << endl;
                cout << " [!] Tidak ada mobil yang sesuai dengan kriteria tersebut." << endl;
            }

            cout << "\n>> Tekan Enter untuk kembali ke Menu Pencarian...";
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
    getline(file, line); // Skip Header

    while (getline(file, line)) {
        // Lewati baris kosong
        if (line.empty() || line.find_first_not_of("\r\n \t") == string::npos) continue;
        
        stringstream ss(line);
        string temp;
        int i = 0;

        while (getline(ss, temp, ',')) {
            if (i == kolom && !temp.empty()) {
                // Buang enter bayangan di ujung kata
                if (temp.back() == '\r') temp.pop_back(); 
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
        cocok = (pohon->benua == kriteria);
    } 
    else if (pilihanFilter == 5) {
        cocok = (pohon->transmisi == kriteria);
    } 
    else if (pilihanFilter == 6) {
        cocok = (pohon->tipe == kriteria);
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
    string inputBuffer;
    while (true) {
        #ifdef _WIN32
            system("cls");
        #else
            system("clear");
        #endif

        cout << "\n========================================\n";
        cout << "       FILTER STOK MOBIL (ADMIN)        \n";
        cout << "========================================\n";
        cout << " [1] Berdasarkan Tahun\n";
        cout << " [2] Berdasarkan Merk\n";
        cout << " [3] Berdasarkan Kondisi\n";
        cout << " [4] Berdasarkan Benua\n";
        cout << " [5] Berdasarkan Transmisi\n";
        cout << " [6] Berdasarkan Tipe\n";
        cout << "----------------------------------------\n";
        cout << " Pilih (0 atau Enter untuk kembali): ";
        
        getline(cin, inputBuffer);
        
        if (inputBuffer.empty() || inputBuffer == "0") {
            return;
        }

        int pilihan = -1;
        try { pilihan = stoi(inputBuffer); } catch (...) { continue; }
        if (pilihan < 1 || pilihan > 6) continue;

        string kriteria = "";
        int pilihanTahun = 0;

        if (pilihan == 1) {
            cout << "\n>>> FILTER TAHUN\n";
            cout << " [1] Semua Tahun\n";
            cout << " [2] Tahun >= 2000 (Mobil Modern)\n";
            cout << " [3] Tahun < 2000 (Mobil Klasik)\n";
            cout << " Pilih (Enter untuk batal): ";
            getline(cin, inputBuffer);
            if (inputBuffer.empty()) continue;
            try { pilihanTahun = stoi(inputBuffer); } catch(...) { continue; }
            if (pilihanTahun < 1 || pilihanTahun > 3) continue;
        }
        else if (pilihan == 3) {
            cout << "\n>>> FILTER KONDISI\n";
            cout << " [1] Brand New\n [2] Mint\n [3] Excellent\n [4] Good\n [5] Project Car\n";
            cout << " Pilih (Enter untuk batal): ";
            getline(cin, inputBuffer);
            if (inputBuffer.empty()) continue;
            int pilihKondisi = 0;
            try { pilihKondisi = stoi(inputBuffer); } catch(...) { continue; }
            if (pilihKondisi < 1 || pilihKondisi > 5) continue;
            string kondisi[] = {"Brand New", "Mint", "Excellent", "Good", "Project Car"};
            kriteria = kondisi[pilihKondisi - 1];
        }
        else {
            int kolomPencarian = -1;
            string namaFilter = "";
            
            if (pilihan == 2) { kolomPencarian = 1; namaFilter = "MERK"; }
            else if (pilihan == 4) { kolomPencarian = 5; namaFilter = "BENUA"; }
            else if (pilihan == 5) { kolomPencarian = 6; namaFilter = "TRANSMISI"; }
            else if (pilihan == 6) { kolomPencarian = 7; namaFilter = "TIPE"; }

            vector<string> opsi = ambilOpsiAdmin(kolomPencarian);
            if (opsi.empty()) {
                cout << "[!] Data " << namaFilter << " tidak tersedia di database saat ini.\n";
                cout << "Tekan Enter untuk lanjut...";
                getline(cin, inputBuffer);
                continue;
            }
            
            cout << "\n>>> FILTER " << namaFilter << "\n";
            
            int kolomGrid = 0;
            for (size_t i = 0; i < opsi.size(); i++) {
                string teksOpsi = "[" + to_string(i + 1) + "] " + opsi[i];
                cout << left << setw(25) << teksOpsi;
                
                kolomGrid++;
                if (kolomGrid == 4) { 
                    cout << "\n";
                    kolomGrid = 0;
                }
            }
            if (kolomGrid != 0) cout << "\n"; 
            cout << "\n Pilih (Enter untuk batal): ";
            getline(cin, inputBuffer);
            if (inputBuffer.empty()) continue;
            
            int pilihOpsi = 0;
            try { pilihOpsi = stoi(inputBuffer); } catch(...) { continue; }
            if (pilihOpsi < 1 || pilihOpsi > opsi.size()) continue;
            
            kriteria = opsi[pilihOpsi - 1];
        }
        TreeAdmin *pohonUtama;
        deklarasiTreeAdmin(pohonUtama);

        ifstream file("database_mobil.csv");
        string line;
        getline(file, line);

        while (getline(file, line)) {
            if (line.empty() || line.find_first_not_of("\r\n \t") == string::npos) continue;
            
            stringstream ss(line);
            string data[8];
            for (int i = 0; i < 8; i++) {
                getline(ss, data[i], ',');
                if (!data[i].empty() && data[i].back() == '\r') data[i].pop_back();
            }
            insertTreeAdmin(&pohonUtama, data[0], data[1], data[2], data[3], data[4], data[7], data[6], data[5]);
        }
        file.close();

        // Tampilkan Header Tabel
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

        int count = 0;
        traversalFilterAdmin(pohonUtama, pilihan, pilihanTahun, kriteria, count);

        // Tampilkan Footer Tabel
        cout << setfill('=') << setw(105) << "=" << setfill(' ') << endl;
        cout << " Total: " << count << " unit ditemukan.\n";

        deleteTreeAdmin(pohonUtama);

        cout << "\n>> Tekan Enter untuk kembali ke Menu Filter...";
        getline(cin, inputBuffer);
    }
}