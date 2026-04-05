#ifndef FEATURES_H
#define FEATURES_H

#include <string>
using namespace std;

// 1. STRUKTUR DATA
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

// 2. FUNGSI KHUSUS USER
void inisialisasiData();
void tambahUnit(Kategori &kat, string model, int tahun, string kondisi);
void tampilkanKatalog();
void cariMobil();
void filterMobil();

// 3. FUNGSI KHUSUS ADMIN
void tambahMobilAdmin();
void tampilkanKatalogAdmin();
void hapusMobilAdmin();
void updateMobilAdmin();
void searchFilterAdmin();
void sinkronisasiKeCSV();
string keHurufKecil(string str);

#endif