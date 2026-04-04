#include <iostream>
#include <string>
#include <algorithm>
#include <iomanip>
#include "features.h"

using namespace std;

extern Kategori showroom[3];

void filterMobil() {
    int pilihanFilter;

    cout << "\n=== FILTER MOBIL ===\n";
    cout << "  [1] Tahun\n";
    cout << "  [2] Merk\n";
    cout << "  [3] Kondisi\n";
    cout << "Pilihan: ";
    cin >> pilihanFilter;

    // ── Tentukan kriteria filter ──────────────────────────
    int    pilihanTahun   = 0;
    int    pilihanMerk    = 0;
    string pilihanKondisi = "";

    if (pilihanFilter == 1) {
        cout << "\nFilter Tahun:\n";
        cout << "  [1] Semua\n";
        cout << "  [2] Mobil Baru  (diatas tahun 2000)\n";
        cout << "  [3] Mobil Lama  (dibawah tahun 2000)\n";
        cout << "Pilihan: ";
        cin >> pilihanTahun;

    } else if (pilihanFilter == 2) {
        cout << "\nFilter Merk:\n";
        cout << "  [1] Semua\n";
        cout << "  [2] Toyota\n";
        cout << "  [3] Honda\n";
        cout << "  [4] Suzuki\n";
        cout << "Pilihan: ";
        cin >> pilihanMerk;

    } else if (pilihanFilter == 3) {
        cout << "\nFilter Kondisi:\n";
        cout << "  [1] Semua\n";
        cout << "  [2] Baru\n";
        cout << "  [3] Bekas\n";
        cout << "Pilihan: ";
        int pilihanK;
        cin >> pilihanK;
        if      (pilihanK == 2) pilihanKondisi = "Baru";
        else if (pilihanK == 3) pilihanKondisi = "Bekas";

    } else {
        cout << "[!] Pilihan tidak valid.\n";
        return;
    }

    // ── Clear screen setelah semua input selesai ──────────
    #ifdef _WIN32
        system("cls");
    #else
        system("clear");
    #endif

    // ── Cetak header tabel ────────────────────────────────
    cout << "\n" << setfill('=') << setw(70) << "=" << setfill(' ') << endl;
    cout << left
         << setw(5)  << "ID"
         << setw(12) << "MERK"
         << setw(22) << "MODEL"
         << setw(8)  << "TAHUN"
         << "KONDISI" << endl;
    cout << setfill('-') << setw(70) << "-" << setfill(' ') << endl;

    // ── Loop data & terapkan filter ───────────────────────
    int counter = 0;
    for (int i = 0; i < 3; i++) {
        Mobil* temp = showroom[i].head;

        while (temp != nullptr) {
            bool lolos = false;

            if (pilihanFilter == 1) {
                if      (pilihanTahun == 1) lolos = true;
                else if (pilihanTahun == 2) lolos = (temp->Tahun >= 2000);
                else if (pilihanTahun == 3) lolos = (temp->Tahun <  2000);
                else                        lolos = true;

            } else if (pilihanFilter == 2) {
                if      (pilihanMerk == 1) lolos = true;
                else if (pilihanMerk == 2) lolos = (showroom[i].NamaMerk == "Toyota");
                else if (pilihanMerk == 3) lolos = (showroom[i].NamaMerk == "Honda");
                else if (pilihanMerk == 4) lolos = (showroom[i].NamaMerk == "Suzuki");
                else                       lolos = true;

            } else if (pilihanFilter == 3) {
                if (pilihanKondisi.empty()) lolos = true;
                else lolos = (temp->Kondisi == pilihanKondisi);
            }

            if (lolos) {
                counter++;
                cout << left
                     << setw(5)  << temp->id
                     << setw(12) << showroom[i].NamaMerk
                     << setw(22) << temp->Model
                     << setw(8)  << temp->Tahun
                     << temp->Kondisi << endl;
            }
            temp = temp->next;
        }
    }

    // ── Footer ────────────────────────────────────────────
    cout << setfill('=') << setw(70) << "=" << setfill(' ') << endl;
    if (counter > 0)
        cout << "Berhasil menemukan " << counter << " unit." << endl;
    else
        cout << "[!] Tidak ada mobil yang sesuai dengan kriteria tersebut." << endl;
}