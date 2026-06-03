#include <iostream>
#include <string>
#include <algorithm>
#include <iomanip>
#include "features.h"

using namespace std;

struct RiwayatPencarian {
    string kata;
    RiwayatPencarian *next;
};

RiwayatPencarian *topRiwayatPencarian = nullptr;

void simpanRiwayatPencarian(string kata) {
    if (kata == "") {
        return;
    }

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

void cariMobil() {
    while (true) {
        int pilihanMenu;

        cout << "\n========================================\n";
        cout << "         PENCARIAN KOLEKSI MOBIL       \n";
        cout << "========================================\n";
        cout << " 1. Cari Mobil\n";
        cout << " 2. Lihat Riwayat Pencarian\n";
        cout << " 3. Hapus Riwayat Pencarian\n";
        cout << " 0. Kembali ke Beranda\n";
        cout << "----------------------------------------\n";
        cout << "Pilihan: ";

        if (!(cin >> pilihanMenu)) {
            cin.clear();
            cin.ignore(1000, '\n');
            continue;
        }

        cin.ignore(1000, '\n');

        if (pilihanMenu == 0) {
            return;
        }

        if (pilihanMenu == 2) {
            tampilkanRiwayatPencarian();
            cout << "\nTekan Enter untuk kembali...";
            cin.get();
            continue;
        }

        if (pilihanMenu == 3) {
            hapusRiwayatPencarian();
            cout << "\n[+] Riwayat pencarian berhasil dihapus.\n";
            cout << "Tekan Enter untuk kembali...";
            cin.get();
            continue;
        }

        if (pilihanMenu != 1) {
            cout << "\n[!] Pilihan tidak valid.\n";
            continue;
        }

        string key;
        cout << "\nMasukkan Model (atau '0' untuk semua): ";
        getline(cin, key);

        if (key == "") {
            continue;
        }

        simpanRiwayatPencarian(key);

        string keyKecil = keHurufKecil(key);

        #ifdef _WIN32
            system("cls");
        #else
            system("clear");
        #endif

        cout << "\n" << setfill('=') << setw(70) << "=" << setfill(' ') << endl;
        cout << left
             << setw(5)  << "ID"
             << setw(12) << "MERK"
             << setw(22) << "MODEL"
             << setw(8)  << "TAHUN"
             << "KONDISI" << endl;
        cout << setfill('-') << setw(70) << "-" << setfill(' ') << endl;

        int counter = 0;

        for (Kategori* currKat = headKategori; currKat != nullptr; currKat = currKat->next) {
            for (Mobil* temp = currKat->head; temp != nullptr; temp = temp->next) {
                string modelKecil = keHurufKecil(temp->Model);

                if (keyKecil == "0" || keyKecil == "" || modelKecil.find(keyKecil) != string::npos) {
                    counter++;
                    cout << left
                         << setw(5)  << temp->id
                         << setw(12) << currKat->NamaMerk
                         << setw(22) << temp->Model
                         << setw(8)  << temp->Tahun
                         << temp->Kondisi << endl;
                }
            }
        }

        if (counter > 0) {
            cout << setfill('=') << setw(70) << "=" << setfill(' ') << endl;
            cout << "Berhasil menemukan " << counter << " unit." << endl;
        } else {
            cout << setfill('=') << setw(70) << "=" << setfill(' ') << endl;
            cout << "[!] Tidak ada mobil yang sesuai dengan kriteria tersebut." << endl;
        }

        cout << "\nTekan Enter untuk kembali ke menu search...";
        cin.get();
    }
}