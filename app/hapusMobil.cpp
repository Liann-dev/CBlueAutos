#include <iostream>
#include <string>
#include "features.h"

using namespace std;

extern Kategori showroom[3];

void hapusMobilAdmin() {
    string target;
    cout << "\n=== HAPUS UNIT MOBIL ===" << endl;
    cout << "Masukkan Nama Model yang akan dihapus: ";
    cin.ignore(); getline(cin, target);

    bool ditemukan = false;
    for (int i = 0; i < 3; i++) {
        Mobil* temp = showroom[i].head;
        Mobil* prev = nullptr;

        while (temp != nullptr) {
            if (temp->Model == target) {
          
                if (prev == nullptr) {
                    showroom[i].head = temp->next;
                } else {
             
                    prev->next = temp->next;
                }
                delete temp;
                ditemukan = true;
                break;
            }
            prev = temp;
            temp = temp->next;
        }
        if (ditemukan) break;
    }

    if (ditemukan) cout << "[Sukses] Unit '" << target << "' berhasil dihapus.\n";
    else cout << "[Error] Unit tidak ditemukan!\n";
}