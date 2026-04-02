#include <iostream>
#include <string>
#include "../../features.h"
using namespace std;

extern Kategori showroom[3];

void updateMobilAdmin() {
    string target;
    double hargaBaru;
    cout << "\n=== UPDATE HARGA UNIT ===" << endl;
    cout << "Masukkan Nama Model: ";
    cin.ignore(); getline(cin, target);

    for (int i = 0; i < 3; i++) {
        Mobil* temp = showroom[i].head;
        while (temp != nullptr) {
            if (temp->Model == target) {
                cout << "Harga Lama: " << temp->Harga << " Jt" << endl;
                cout << "Masukkan Harga Baru (Jt): "; cin >> hargaBaru;
                temp->Harga = hargaBaru;
                cout << "[Sukses] Harga " << target << " berhasil diperbarui!\n";
                return;
            }
            temp = temp->next;
        }
    }
    cout << "[Error] Unit tidak ditemukan!\n";
}