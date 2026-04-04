#include <iostream>
#include <string>
#include <iomanip>
#include "features.h"

using namespace std;
extern Kategori showroom[3]; 


void tampilkanKatalogAdmin() {
 
    bool adaData = false;
    for (int i = 0; i < 3; i++) {
        if (showroom[i].head != nullptr) adaData = true;
    }

    if (!adaData) {
        cout << "\n[!] Katalog Kosong. Pastikan inisialisasiData() sudah dipanggil.\n";
        return;
    }

    cout << "\n" << left << setw(5) << "ID" << setw(15) << "MERK" << setw(20) << "MODEL" << setw(10) << "THN" << "KONDISI" << endl;
    for (int i = 0; i < 3; i++) { 
        Mobil* temp = showroom[i].head; 
        while (temp != nullptr) { 
            cout << left << setw(5) << temp->id 
                 << setw(15) << showroom[i].NamaMerk 
                 << setw(20) << temp->Model 
                 << setw(10) << temp->Tahun 
                 << temp->Kondisi << endl;
            temp = temp->next;
        }
    }
}