#include <iostream>
#include <string>
#include <algorithm>
#include <iomanip>

using namespace std;

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

string keHurufKecil(string teks) {
    transform(teks.begin(), teks.end(), teks.begin(), ::tolower);
    return teks;
}

void tambahUnit(Kategori &kat, string model, int tahun, double harga) {
    Mobil* baru = new Mobil;
    baru->Model = model;
    baru->Tahun = tahun;
    baru->Harga = harga;
    baru->next = kat.head;
    kat.head = baru;
}

int main() {
    
    Kategori showroom[3];
    showroom[0] = {"Toyota", nullptr};
    showroom[1] = {"Honda", nullptr};
    showroom[2] = {"Suzuki", nullptr};

    tambahUnit(showroom[0], "GR Supra", 2023, 2100.5);
    tambahUnit(showroom[0], "Avanza", 2022, 250.0);
    tambahUnit(showroom[1], "Civic Type R", 2024, 1400.0);
    tambahUnit(showroom[1], "Brio", 2021, 180.0);
    tambahUnit(showroom[2], "Jimny", 2023, 450.0);

    // Input User
    string key;
    cout << "Masukkan nama mobil (Merk atau Model): ";
    getline(cin >> ws, key);
    string keyKecil = keHurufKecil(key);

    double budgetMaks;
    cout << "Masukkan budget maksimal (Juta): ";
    cin >> budgetMaks;

    int tahunMin;
    cout << "Masukkan minimal tahun mobil: ";
    cin >> tahunMin;

    cout << "\n" << setfill('=') << setw(60) << "=" << endl;
    cout << left << setw(15) << "MERK" << setw(15) << "MODEL" << setw(10) << "TAHUN" << "HARGA" << endl;
    cout << setfill('-') << setw(60) << "-" << setfill(' ') << endl;

    int counter = 0;

    // --- LOGIKA SEARCH & FILTER LENGKAP ---
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
                     << setw(15) << temp->Model 
                     << setw(10) << temp->Tahun 
                     << fixed << setprecision(1) << temp->Harga << " Jt" << endl;
            }
            temp = temp->next; 
        }
    }

    if (counter > 0) {
        cout << setfill('=') << setw(60) << "=" << setfill(' ') << endl;
        cout << "Total ditemukan: " << counter << " mobil." << endl;
    } else {
        cout << "\nMobil dengan kriteria tersebut tidak ditemukan!" << endl;
    }

    return 0;
}