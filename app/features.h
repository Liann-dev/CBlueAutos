#ifndef FEATURES_H
#define FEATURES_H

#include <string>
using namespace std;
struct Mobil
{
    int id;
    string Merk;
    string Model;
    int Tahun;
    string Kondisi;
    Mobil *next;
    Mobil *prev;
};

struct Kategori
{
    string NamaMerk;
    Mobil *head;
    Kategori *next;
    Kategori *prev;
};

struct Page
{
    Mobil *items[10];
    string merkItems[10];
    int jumlah;
    int nomorHalaman;
    Page *next;
    Page *prev;
};

// ==========================================
// VARIABEL GLOBAL (Agar dikenali semua file)
// ==========================================
// Di dalam features.h
extern Kategori *headKategori;

// ==========================================
// FUNGSI BANTUAN (UTILITY)
// ==========================================
string keHurufKecil(string str);

Kategori *cariAtauBuatKategori(string merk);
void inisialisasiData();
void tambahUnit(Kategori &kat, string model, int tahun, string kondisi);
void tampilkanKatalog();
void cariMobil();
void filterMobil();

void tambahMobilAdmin();
void tampilkanKatalogAdmin();
void hapusMobilAdmin();
void updateMobilAdmin();
void searchFilterAdmin();
void sinkronisasiKeCSV();
void showTableData();

#endif