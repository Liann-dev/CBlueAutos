#include <iostream>
#include <string>
#include <algorithm>
#include <iomanip>
#include "features.h"

using namespace std;

extern string keHurufKecil(string teks);

// ==========================================
// STRUKTUR DATA RIWAYAT (Linked List)
// ==========================================
struct RiwayatPencarian {
    string kata;
    RiwayatPencarian *next;
};

RiwayatPencarian *topRiwayatPencarian = nullptr;

void simpanRiwayatPencarian(string kata) {
    // Sedikit perbaikan: Jangan simpan ke riwayat jika kata kosong atau sekadar "0"
    if (kata == "" || kata == "0") { 
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

// ==========================================
// FUNGSI UTAMA PENCARIAN (Sudah digabung)
// ==========================================
void cariMobil() {
    string inputBuffer;

    while (true) {
        #ifdef _WIN32
            system("cls");
        #else
            system("clear");
        #endif

        cout << "\n========================================\n";
        cout << "         PENCARIAN KOLEKSI MOBIL        \n";
        cout << "========================================\n";
        cout << " 1. Cari Mobil\n";
        cout << " 2. Lihat Riwayat Pencarian\n";
        cout << " 3. Hapus Riwayat Pencarian\n";
        cout << " 0. Kembali ke Beranda\n";
        cout << "----------------------------------------\n";
        cout << "Pilihan: ";

        // Membaca input menu menggunakan getline agar bebas bug Enter
        getline(cin, inputBuffer);
        if (inputBuffer.empty()) continue;

        int pilihanMenu = -1;
        try {
            pilihanMenu = stoi(inputBuffer);
        } catch (...) {
            continue; // Kalau ngetik huruf, refresh menu
        }

        // --- EKSEKUSI MENU ---
        if (pilihanMenu == 0) {
            return; // Keluar sepenuhnya dari fitur ini
        } 
        else if (pilihanMenu == 2) {
            tampilkanRiwayatPencarian();
            cout << "\nTekan Enter untuk kembali...";
            getline(cin, inputBuffer);
            continue;
        } 
        else if (pilihanMenu == 3) {
            hapusRiwayatPencarian();
            cout << "\n[+] Riwayat pencarian berhasil dihapus.\n";
            cout << "Tekan Enter untuk kembali...";
            getline(cin, inputBuffer);
            continue;
        } 
        else if (pilihanMenu == 1) {
            cout << "\nMasukkan Model ('0' untuk semua, atau tekan Enter untuk batal): ";
            getline(cin, inputBuffer);

            // Batal mencari jika cuma tekan Enter
            if (inputBuffer.empty()) {
                continue; 
            }

            // Simpan kata ke Linked List Riwayat
            simpanRiwayatPencarian(inputBuffer);

            string keyKecil = keHurufKecil(inputBuffer);

            // Bersihkan layar sebelum mencetak tabel
            #ifdef _WIN32
                system("cls");
            #else
                system("clear");
            #endif

            // Cetak Header Tabel Lebar (105 karakter)
            cout << "\n" << setfill('=') << setw(105) << "=" << setfill(' ') << endl;
            cout << left << " " << setw(5) << "ID" << setw(15) << "MERK" << setw(20) << "MODEL" 
                 << setw(8) << "TAHUN" << setw(15) << "KONDISI" << setw(12) << "TIPE" 
                 << setw(12) << "TRANSMISI" << "BENUA" << endl;
            cout << setfill('-') << setw(105) << "-" << setfill(' ') << endl;

            int counter = 0;

            // Proses Pencarian
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

            // Cetak Footer Tabel
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