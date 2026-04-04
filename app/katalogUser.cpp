#include <iostream>
#include <string>
#include <iomanip>
#include "features.h"

using namespace std;


Kategori showroom[3];

void inisialisasiData() {
    showroom[0].NamaMerk = "Toyota"; 
    showroom[1].NamaMerk = "Honda";
    showroom[2].NamaMerk = "Suzuki";
    
    showroom[0].head = nullptr;
    showroom[1].head = nullptr;
    showroom[2].head = nullptr;
}
void tambahUnit(Kategori &kat, string model, int tahun, double harga) {
    Mobil* baru = new Mobil;
    baru->Model = model;
    baru->Tahun = tahun;
    baru->Harga = harga;
    baru->next = kat.head;
    kat.head = baru;
}


void tampilkanKatalog() {
 
    bool adaData = false;
    for (int i = 0; i < 3; i++) {
        if (showroom[i].head != nullptr) adaData = true;
    }

    if (!adaData) {
        cout << "\n[!] Katalog Kosong. Pastikan inisialisasiData() sudah dipanggil.\n";
        return;
    }

    cout << "\n" << setfill('=') << setw(65) << "=" << endl;
    cout << left << setw(15) << "MERK" << setw(20) << "MODEL" << setw(10) << "TAHUN" << "HARGA" << endl;
    cout << setfill('-') << setw(65) << "-" << setfill(' ') << endl;

    for (int i = 0; i < 3; i++) { 
        Mobil* temp = showroom[i].head; 
        while (temp != nullptr) { 
            cout << left << setw(15) << showroom[i].NamaMerk 
                 << setw(20) << temp->Model 
                 << setw(10) << temp->Tahun 
                 << fixed << setprecision(1) << "$" << temp->Harga << " Jt" << endl;
            temp = temp->next;
        }
    }
    cout << setfill('=') << setw(65) << "=" << setfill(' ') << endl;
}