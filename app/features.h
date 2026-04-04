#ifndef FEATURES_H
#define FEATURES_H

#include <string>
using namespace std;

// ==========================================
// 1. STRUKTUR DATA
// ==========================================
struct Mobil {
    int id;          // Unique Key baru
    string Model;
    int Tahun;
    string Kondisi; 
    Mobil* next;
};

struct Kategori {
    string NamaMerk;
    Mobil* head;
};

// 2. FUNGSI KHUSUS USER
void inisialisasiData();
void tambahUnit(Kategori &kat, string model, int tahun, string kondisi);
void tampilkanKatalog();
void cariMobil();

// 3. FUNGSI KHUSUS ADMIN
void tambahMobilAdmin();
void tampilkanKatalogAdmin();
void hapusMobilAdmin();
void updateMobilAdmin(); // Sekarang mengupdate kondisi
void searchFilterAdmin();
string keHurufKecil(string str);
#endif