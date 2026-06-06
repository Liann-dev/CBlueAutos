#include <iostream>
#include <string>
#include <algorithm>
#include <iomanip>
#include <fstream>
#include <sstream>
#include <vector>
#include "features.h"

using namespace std;

struct RiwayatPencarian {
    string kata;
    RiwayatPencarian *next;
};
RiwayatPencarian *topRiwayatPencarian = nullptr;

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

void bersihkanLayar() {
#ifdef _WIN32
    system("cls");
#else
    system("clear");
#endif
}

void cetakHeaderTabel() {
    cout << "\n" << setfill('=') << setw(105) << "=" << setfill(' ') << endl;
    cout << left << " " << setw(5) << "ID" << setw(15) << "MERK" << setw(20) << "MODEL" 
         << setw(8) << "TAHUN" << setw(15) << "KONDISI" << setw(12) << "TIPE" 
         << setw(12) << "TRANSMISI" << "BENUA" << endl;
    cout << setfill('-') << setw(105) << "-" << setfill(' ') << endl;
}

string formatModelTeks(string model) {
    if (model.length() > 18) {
        return model.substr(0, 15) + "...";
    }
    return model;
}

void simpanRiwayatPencarian(string kata) {
    if (kata == "" || kata == "0") return;

    RiwayatPencarian *baru = new RiwayatPencarian;
    baru->kata = kata;
    baru->next = topRiwayatPencarian;
    topRiwayatPencarian = baru;
}

void tampilkanRiwayatPencarian() {
    if (topRiwayatPencarian == nullptr) {
        cout << "\n[!] Riwayat pencarian masih kosong.\n";
        return;
    }
    cout << "\n=== RIWAYAT PENCARIAN ===\n";
    int nomor = 1;
    for (RiwayatPencarian *temp = topRiwayatPencarian; temp != nullptr; temp = temp->next) {
        cout << nomor << ". " << temp->kata << endl;
        nomor++;
    }
}

void hapusRiwayatPencarian() {
    while (topRiwayatPencarian != nullptr) {
        RiwayatPencarian *hapus = topRiwayatPencarian;
        topRiwayatPencarian = topRiwayatPencarian->next;
        delete hapus;
    }
}

void insertTreeAdmin(TreeAdmin** pohon, string id, string merk, string model, string tahun, string kondisi, string tipe, string transmisi, string benua) {
    if (*pohon == nullptr) {
        TreeAdmin *new_node = new TreeAdmin{id, merk, model, tahun, kondisi, tipe, transmisi, benua, nullptr, nullptr};
        *pohon = new_node;
    } else {
        if (stoi(id) < stoi((*pohon)->id)) {
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

void traversalFilterAdmin(TreeAdmin* pohon, int pilihanFilter, int pilihanTahun, string kriteria, int &count) {
    if (pohon == nullptr) return;

    traversalFilterAdmin(pohon->left, pilihanFilter, pilihanTahun, kriteria, count);

    bool cocok = false;
    string kriteriaKecil = keHurufKecil(kriteria);

    if (pilihanFilter == 1) {
        int tahunMobil = stoi(pohon->tahun);
        if (pilihanTahun == 1) cocok = true;
        else if (pilihanTahun == 2) cocok = (tahunMobil >= 2000);
        else if (pilihanTahun == 3) cocok = (tahunMobil < 2000);
    } 
    else if (pilihanFilter == 2) cocok = (keHurufKecil(pohon->merk).find(kriteriaKecil) != string::npos);
    else if (pilihanFilter == 3) cocok = (keHurufKecil(pohon->kondisi).find(kriteriaKecil) != string::npos);
    else if (pilihanFilter == 4) cocok = (keHurufKecil(pohon->benua).find(kriteriaKecil) != string::npos);
    else if (pilihanFilter == 5) cocok = (keHurufKecil(pohon->transmisi).find(kriteriaKecil) != string::npos);
    else if (pilihanFilter == 6) cocok = (keHurufKecil(pohon->tipe).find(kriteriaKecil) != string::npos);

    if (cocok) {
        count++;
        cout << left << " " << setw(5) << pohon->id << setw(15) << pohon->merk 
             << setw(20) << formatModelTeks(pohon->model) << setw(8) << pohon->tahun << setw(15) << pohon->kondisi 
             << setw(12) << pohon->tipe << setw(12) << pohon->transmisi << pohon->benua << endl;
    }

    traversalFilterAdmin(pohon->right, pilihanFilter, pilihanTahun, kriteria, count);
}

void cariMobil(bool isAdmin) {
    string inputBuffer;

    if (isAdmin) {
        while (true) {
            bersihkanLayar();
            cout << "\n=======================================================================\n";
            cout << "                     PENCARIAN STOK MOBIL (ADMIN)                      \n";
            cout << "=======================================================================\n";
            cout << " Masukkan Model / Kata Kunci ('0' untuk semua stok)\n";
            cout << " >> [Tekan ENTER Langsung Untuk Kembali ke Dashboard]: ";

            getline(cin, inputBuffer);
            if (inputBuffer.empty()) break; 
            if (inputBuffer == "0") inputBuffer = "";

            string keyKecil = keHurufKecil(inputBuffer);
            bersihkanLayar();
            cetakHeaderTabel();

            int counter = 0;
            for (Kategori* currKat = headKategori; currKat != nullptr; currKat = currKat->next) {
                for (Mobil* temp = currKat->head; temp != nullptr; temp = temp->next) {
                    string modelKecil = keHurufKecil(temp->Model);

                    if (keyKecil.empty() || modelKecil.find(keyKecil) != string::npos) {
                        counter++;
                        cout << left << " " << setw(5) << temp->id << setw(15) << currKat->NamaMerk 
                             << setw(20) << formatModelTeks(temp->Model) << setw(8) << temp->Tahun << setw(15) << temp->Kondisi 
                             << setw(12) << temp->Tipe << setw(12) << temp->Transmisi << temp->Benua << endl;
                    }
                }
            }

            cout << setfill('=') << setw(105) << "=" << setfill(' ') << endl;
            if (counter > 0) cout << " Berhasil menemukan " << counter << " unit." << endl;
            else cout << " [!] Tidak ada mobil yang sesuai dengan kata kunci tersebut." << endl;

            cout << "\n>> Tekan Enter untuk mencari kembali...";
            getline(cin, inputBuffer);
        }
        return; 
    }

    while (true) {
        bersihkanLayar();
        cout << "\n========================================\n";
        cout << "         PENCARIAN KOLEKSI MOBIL        \n";
        cout << "========================================\n";
        cout << " 1. Cari Mobil\n";
        cout << " 2. Lihat Riwayat Pencarian\n";
        cout << " 3. Hapus Riwayat Pencarian\n";
        cout << "----------------------------------------\n";
        cout << "Pilihan (Tekan Enter untuk kembali): ";

        getline(cin, inputBuffer);
        if (inputBuffer.empty() || inputBuffer == "0") break;

        int pilihanMenu = -1;
        try { pilihanMenu = stoi(inputBuffer); } catch (...) { pilihanMenu = -1; }

        if (pilihanMenu == 2) {
            tampilkanRiwayatPencarian();
            cout << "\nTekan Enter untuk kembali...";
            getline(cin, inputBuffer);
            continue;
        } 
        else if (pilihanMenu == 3) {
            hapusRiwayatPencarian();
            cout << "\n[+] Riwayat pencarian berhasil dihapus.\nTekan Enter untuk kembali...";
            getline(cin, inputBuffer);
            continue;
        } 
        else if (pilihanMenu == 1) {
            cout << "\nMasukkan Model / Kata Kunci ('0' untuk semua stok)\n";
            cout << ">> [Tekan ENTER Langsung Untuk Batal]: ";
            
            getline(cin, inputBuffer);
            if (inputBuffer.empty()) continue; 
            if (inputBuffer == "0") inputBuffer = ""; 

            if (!inputBuffer.empty()) {
                simpanRiwayatPencarian(inputBuffer);
            }

            string keyKecil = keHurufKecil(inputBuffer);
            bersihkanLayar();
            cetakHeaderTabel();

            int counter = 0;
            for (Kategori* currKat = headKategori; currKat != nullptr; currKat = currKat->next) {
                for (Mobil* temp = currKat->head; temp != nullptr; temp = temp->next) {
                    string modelKecil = keHurufKecil(temp->Model);

                    if (keyKecil.empty() || modelKecil.find(keyKecil) != string::npos) {
                        counter++;
                        cout << left << " " << setw(5) << temp->id << setw(15) << currKat->NamaMerk 
                             << setw(20) << formatModelTeks(temp->Model) << setw(8) << temp->Tahun << setw(15) << temp->Kondisi 
                             << setw(12) << temp->Tipe << setw(12) << temp->Transmisi << temp->Benua << endl;
                    }
                }
            }

            cout << setfill('=') << setw(105) << "=" << setfill(' ') << endl;
            if (counter > 0) cout << " Berhasil menemukan " << counter << " unit." << endl;
            else cout << " [!] Tidak ada mobil yang sesuai dengan kata kunci tersebut." << endl;

            cout << "\n>> Tekan Enter untuk kembali ke Menu Pencarian...";
            getline(cin, inputBuffer);
        } 
        else {
            cout << "\n[!] Pilihan tidak valid. Tekan Enter untuk mengulang...";
            getline(cin, inputBuffer);
        }
    }
}

void filterMobil(bool isAdmin) {
    string inputBuffer;
    while (true) {
        bersihkanLayar();
        cout << "\n========================================\n";
        cout << (isAdmin ? "       FILTER STOK MOBIL (ADMIN)        \n" : "       FILTER STOK MOBIL (USER)         \n");
        cout << "========================================\n";
        cout << " [1] Berdasarkan Tahun\n [2] Berdasarkan Merk\n [3] Berdasarkan Kondisi\n"
             << " [4] Berdasarkan Benua\n [5] Berdasarkan Transmisi\n [6] Berdasarkan Tipe\n";
        cout << "----------------------------------------\n";
        cout << " Pilih (0 atau Enter untuk kembali): ";
        
        getline(cin, inputBuffer);
        if (inputBuffer.empty() || inputBuffer == "0") return;

        int pilihan = -1;
        try { pilihan = stoi(inputBuffer); } catch (...) { continue; }
        if (pilihan < 1 || pilihan > 6) continue;

        string kriteria = "";
        int pilihanTahun = 0;

        if (pilihan == 1) {
            cout << "\n>>> FILTER TAHUN\n [1] Semua Tahun\n [2] Tahun >= 2000 (Mobil Modern)\n [3] Tahun < 2000 (Mobil Klasik)\n Pilih (Enter untuk batal): ";
            getline(cin, inputBuffer);
            if (inputBuffer.empty()) continue;
            try { pilihanTahun = stoi(inputBuffer); } catch(...) { continue; }
            if (pilihanTahun < 1 || pilihanTahun > 3) continue;
        }
        else {
            if (pilihan == 2) {
                cout << "\n>>> FILTER MERK\n";
                cout << " Masukkan nama Merk (contoh: Toyota, Esemka, BMW, Etc..) atau Enter untuk batal: ";
            } 
            else if (pilihan == 3) {
                cout << "\n>>> FILTER KONDISI\n";
                cout << " Masukkan Kondisi (contoh: Brand New, Mint, Project Car, Excellent, Good) atau Enter untuk batal: ";
            } 
            else if (pilihan == 4) {
                cout << "\n>>> FILTER BENUA\n";
                cout << " Masukkan nama Benua (contoh: Asia, Amerika, Eropa) atau Enter untuk batal: ";
            } 
            else if (pilihan == 5) {
                cout << "\n>>> FILTER TRANSMISI\n";
                cout << " Masukkan jenis Transmisi (contoh: Auto, Manual) atau Enter untuk batal: ";
            } 
            else if (pilihan == 6) {
                cout << "\n>>> FILTER TIPE\n";
                cout << " Masukkan Tipe bodi (contoh: SUV, Sedan, Hatchback, MPV, Sport) atau Enter untuk batal: ";
            }

            getline(cin, kriteria);
            if (kriteria.empty()) continue; 
        }

        TreeAdmin *pohonUtama = nullptr;
        ifstream file("database_mobil.csv");
        string line;
        if (!file.is_open()) {
            cout << "\n[!] Gagal membuka file database_mobil.csv. Tekan Enter...";
            getline(cin, inputBuffer);
            return;
        }
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

        bersihkanLayar();
        cetakHeaderTabel();

        int count = 0;
        traversalFilterAdmin(pohonUtama, pilihan, pilihanTahun, kriteria, count);

        cout << setfill('=') << setw(105) << "=" << setfill(' ') << endl;
        cout << " Total: " << count << " unit ditemukan.\n";

        deleteTreeAdmin(pohonUtama);
        cout << "\n>> Tekan Enter untuk kembali ke Menu Filter...";
        getline(cin, inputBuffer);
    }
}