#ifndef FEATURES_H
#define FEATURES_H

#include <string>
using namespace std;
struct Mobil {
    int id;
    string Merk;
    string Model;
    int Tahun;
    string Kondisi;
    string Benua;       
    string Transmisi; 
    string Tipe;        
    Mobil* prev;
    Mobil* next;
};

struct Kategori
{
    string NamaMerk;
    Mobil *head;
    Kategori *next;
    Kategori *prev;
};

struct ListMobilNode {
    Mobil* dataMobil;
    ListMobilNode* next;
};

struct TreeNodeAngka {
    int keyTahun;
    ListMobilNode* headMobil; 
    TreeNodeAngka* left;
    TreeNodeAngka* right;
};

struct TreeNodeTeks {
    string keyTeks; 
    ListMobilNode* headMobil; 
    TreeNodeTeks* left;
    TreeNodeTeks* right;
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

extern Kategori *headKategori;
extern TreeNodeAngka *rootTahun;        
extern TreeNodeTeks *rootMerk;          
extern TreeNodeTeks *rootKondisi;       
extern TreeNodeTeks *rootBenua;         
extern TreeNodeTeks *rootTransmisi;     
extern TreeNodeTeks *rootTipe;          

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
void cariMobilAdmin();
void filterMobilAdmin();
void sinkronisasiKeCSV();
void showTableData();
void insertTreeTahun(TreeNodeAngka*& root, Mobil* mobilBaru);
void insertTreeTeks(TreeNodeTeks*& root, Mobil* mobilBaru, string nilaiKey);
#endif