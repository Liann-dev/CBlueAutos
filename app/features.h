#ifndef FEATURES_H
#define FEATURES_H

#include <string>
using namespace std;
// ==========================================
// 1. STRUKTUR DATA (HANYA BOLEH DI SINI)
// ==========================================
struct Mobil {
    string Model;
    int Tahun;
    double Harga;
    Mobil* next;
};

struct Kategori {
    string NamaMerk;
    Mobil* head;
};


// 2. FUNGSI KHUSUS USESR

void inisialisasiData();
void tambahUnit(Kategori &kat, std::string model, int tahun, double harga);
void tampilkanKatalog();
void cariMobil(); // Fungsi search untuk user
void inisialisasiData();

// ==========================================
// 3. FUNGSI KHUSUS ADMIN
// ==========================================
void tambahMobilAdmin();       // Tambah unit baru
void tampilkanKatalogAdmin();  // Lihat inventaris + total aset
void hapusMobilAdmin();        // Hapus unit berdasarkan model
void updateMobilAdmin();       // Update harga unit
void searchFilterAdmin();      // Filter berdasarkan tahun
string keHurufKecil(std::string str);
#endif