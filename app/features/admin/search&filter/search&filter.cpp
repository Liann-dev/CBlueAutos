#include <iostream>
#include <string>
#include <algorithm>
#include <iomanip>
#include "../../features.h"

using namespace std;


extern Kategori showroom[3];



void searchFilterAdmin() {
    string key;
    double budgetMaks;
    int tahunMin;

    cout << "\n=== PENCARIAN MOBIL ===\n";
    cout << "Masukkan nama mobil (Merk/Model) atau '0' untuk semua: ";
    getline(cin >> ws, key);
    string keyKecil = keHurufKecil(key);

    cout << "Masukkan budget maksimal (Juta) atau '0': ";
    cin >> budgetMaks;

    cout << "Masukkan minimal tahun mobil atau '0': ";
    cin >> tahunMin;

    cout << "\n" << setfill('=') << setw(65) << "=" << endl;
    cout << left << setw(15) << "MERK" << setw(20) << "MODEL" << setw(10) << "TAHUN" << "HARGA" << endl;
    cout << setfill('-') << setw(65) << "-" << setfill(' ') << endl;

    int counter = 0;
    for (int i = 0; i < 3; i++) {
        string merkKecil = keHurufKecil(showroom[i].NamaMerk);
        Mobil* temp = showroom[i].head;

        while (temp != nullptr) {
            string modelKecil = keHurufKecil(temp->Model);

            if ((keyKecil == "" || keyKecil == "0" || merkKecil.find(keyKecil) != string::npos || modelKecil.find(keyKecil) != string::npos)
                && (budgetMaks == 0 || temp->Harga <= budgetMaks) 
                && (tahunMin == 0 || temp->Tahun >= tahunMin)) {
                
                counter++;
                cout << left << setw(15) << showroom[i].NamaMerk 
                     << setw(20) << temp->Model 
                     << setw(10) << temp->Tahun 
                     << fixed << setprecision(1) << "$" << temp->Harga << " Jt" << endl;
            }
            temp = temp->next;
        }
    }

    if (counter > 0) {
        cout << setfill('=') << setw(65) << "=" << setfill(' ') << endl;
        cout << "Total ditemukan: " << counter << " mobil." << endl;
    } else {
        cout << "\nMobil dengan kriteria tersebut tidak ditemukan!" << endl;
    }
}