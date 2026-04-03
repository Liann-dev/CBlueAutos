#include <iostream>
#include <string>
#include <algorithm>
#include <iomanip>
#include "../../features.h"

using namespace std;

extern Kategori showroom[3]; 

void tambahMobilAdmin() {
    int indeks;
    string modelBaru;
    int tahunBaru;
    double hargaBaru;

    cout << "\n======================================" << endl;
    cout << "     TAMBAH UNIT MOBIL (ADMIN)        " << endl;
    cout << "======================================" << endl;
    
    // 1. Pilih Kategori Merk
    cout << "Pilih Merk Unit:" << endl;
    for (int i = 0; i < 3; i++) {
        cout << i << ". " << showroom[i].NamaMerk << endl;
    }
    cout << "Pilih (0-2): ";
    
    if (!(cin >> indeks) || indeks < 0 || indeks > 2) {
        cin.clear();
        cin.ignore(10000, '\n');
        cout << "\n[Error] Indeks merk tidak valid!" << endl;
        return;
    }

    cout << "Nama Model  : ";
    cin.ignore(10000, '\n'); 
    getline(cin, modelBaru);

    cout << "Tahun Rilis : ";
    cin >> tahunBaru;

    cout << "Harga (Jt)  : ";
    cin >> hargaBaru;

    tambahUnit(showroom[indeks], modelBaru, tahunBaru, hargaBaru);

    cout << "\n[SUKSES] " << modelBaru << " berhasil ditambahkan ke " << showroom[indeks].NamaMerk << "!" << endl;
    cout << "======================================" << endl;
}