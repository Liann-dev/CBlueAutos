#include <iostream>
#include <string>
#include <iomanip>
#include "features.h"

using namespace std;

ListMobilNode* cariDiTreeTeks(TreeNodeTeks* node, string targetTeks) {
    if (node == nullptr) return nullptr;
    if (targetTeks == node->keyTeks) return node->headMobil;
    if (targetTeks < node->keyTeks) return cariDiTreeTeks(node->left, targetTeks);
    return cariDiTreeTeks(node->right, targetTeks);
}

void kumpulkanTahun(TreeNodeAngka* node, int tipeTahun, ListMobilNode*& hasil) {
    if (node == nullptr) return;

    kumpulkanTahun(node->left, tipeTahun, hasil);

    bool lolos = false;
    if (tipeTahun == 1 && node->keyTahun >= 2000) lolos = true; 
    else if (tipeTahun == 2 && node->keyTahun < 2000) lolos = true; 

    if (lolos) {
        ListMobilNode* temp = node->headMobil;
        while (temp != nullptr) {
            ListMobilNode* baru = new ListMobilNode;
            baru->dataMobil = temp->dataMobil;
            baru->next = hasil;
            hasil = baru;
            temp = temp->next;
        }
    }

    kumpulkanTahun(node->right, tipeTahun, hasil);
}

ListMobilNode* salinList(ListMobilNode* asli) {
    ListMobilNode* hasil = nullptr;
    ListMobilNode* curr = asli;
    while (curr != nullptr) {
        ListMobilNode* baru = new ListMobilNode;
        baru->dataMobil = curr->dataMobil;
        baru->next = hasil;
        hasil = baru;
        curr = curr->next;
    }
    return hasil;
}

void urutkanListMobil(ListMobilNode* head) {
    if (!head || !head->next) return;
    bool ditukar;
    do {
        ditukar = false;
        ListMobilNode* curr = head;
        while (curr->next != nullptr) {
            if (curr->dataMobil->id > curr->next->dataMobil->id) {
                Mobil* temp = curr->dataMobil;
                curr->dataMobil = curr->next->dataMobil;
                curr->next->dataMobil = temp;
                ditukar = true;
            }
            curr = curr->next;
        }
    } while (ditukar);
}

void hapusListBantuan(ListMobilNode* head) {
    while (head != nullptr) {
        ListMobilNode* temp = head;
        head = head->next;
        delete temp;
    }
}
void cetakHasilFilter(ListMobilNode* head) {
    if (head == nullptr) {
        cout << "\n[!] Tidak ada mobil yang sesuai dengan filter tersebut.\n";
        return;
    }

    cout << "\n" << setfill('=') << setw(95) << "=" << setfill(' ') << endl;
    cout << left << " " << setw(5) << "ID" << setw(15) << "MERK" << setw(20) << "MODEL" 
         << setw(8) << "TAHUN" << setw(15) << "KONDISI" << setw(15) << "TIPE" << "TRANSMISI" << endl;
    cout << setfill('-') << setw(95) << "-" << setfill(' ') << endl;

    int counter = 0;
    ListMobilNode* temp = head;
    while (temp != nullptr) {
        counter++;
        Mobil* m = temp->dataMobil;
        string modelTeks = m->Model;
        if (modelTeks.length() > 18) modelTeks = modelTeks.substr(0, 15) + "...";
        
        cout << left << " " << setw(5) << m->id << setw(15) << m->Merk 
             << setw(20) << modelTeks << setw(8) << m->Tahun << setw(15) << m->Kondisi 
             << setw(15) << m->Tipe << m->Transmisi << endl;
        
        temp = temp->next;
    }
    cout << setfill('=') << setw(95) << "=" << setfill(' ') << endl;
    cout << " Berhasil menemukan " << counter << " unit.\n";
}

void filterMobil() {
    if (cin.peek() == '\n' || cin.peek() == '\r') {
        cin.ignore();
    }
    string inputBuffer;

    while (true) {
        #ifdef _WIN32
            system("cls");
        #else
            system("clear");
        #endif

        cout << "\n========================================" << endl;

        cout << "\n========================================" << endl;
        cout << "           FILTER KATALOG MOBIL         " << endl;
        cout << "========================================" << endl;
        cout << "  [1] Berdasarkan Tahun" << endl;
        cout << "  [2] Berdasarkan Merk" << endl;
        cout << "  [3] Berdasarkan Kondisi" << endl;
        cout << "  [4] Berdasarkan Benua" << endl;
        cout << "  [5] Berdasarkan Transmisi" << endl;
        cout << "  [6] Berdasarkan Tipe" << endl;
        cout << "----------------------------------------" << endl;
        cout << "Pilihan (Tekan Enter untuk kembali): ";
        
        getline(cin, inputBuffer);
        
        if (inputBuffer.empty()) {
            break; 
        }

        int pilihanFilter = -1;
        try {
            pilihanFilter = stoi(inputBuffer); 
        } catch (...) {
            continue; 
        }

        ListMobilNode* hasilPencarian = nullptr; 

        if (pilihanFilter == 1) {
            cout << "\n>>> FILTER TAHUN\n";
            cout << "  [1] Mobil Modern (Tahun >= 2000)\n";
            cout << "  [2] Mobil Klasik (Tahun < 2000)\n";
            cout << "Pilihan (Tekan Enter untuk batal): ";
            
            getline(cin, inputBuffer);
            if (inputBuffer.empty()) continue;

            int tipeTahun = -1;
            try {
                tipeTahun = stoi(inputBuffer);
            } catch (...) {
                continue;
            }
            
            if (tipeTahun == 1 || tipeTahun == 2) {
                kumpulkanTahun(rootTahun, tipeTahun, hasilPencarian);
            } else {
                continue; 
            }
        } 
        else if (pilihanFilter >= 2 && pilihanFilter <= 6) {
            if (pilihanFilter == 2) {
                cout << "\n>>> FILTER MERK\n";
                cout << "Masukkan nama Merk (contoh: Toyota, Esemka, BMW, Etc..) atau Enter untuk batal: ";
            } else if (pilihanFilter == 3) {
                cout << "\n>>> FILTER KONDISI\n";
                cout << "Masukkan Kondisi (contoh: Brand New, Mint, Project Car, Excellent, Good) atau Enter untuk batal: ";
            } else if (pilihanFilter == 4) {
                cout << "\n>>> FILTER BENUA\n";
                cout << "Masukkan nama Benua (contoh: Asia, Amerika, Eropa) atau Enter untuk batal: ";
            } else if (pilihanFilter == 5) {
                cout << "\n>>> FILTER TRANSMISI\n";
                cout << "Masukkan jenis Transmisi (contoh: Auto, Manual) atau Enter untuk batal: ";
            } else if (pilihanFilter == 6) {
                cout << "\n>>> FILTER TIPE\n";
                cout << "Masukkan Tipe bodi (contoh: SUV, Sedan, Hatchback, MPV, Sport) atau Enter untuk batal: ";
            }
            
            getline(cin, inputBuffer);
            if (inputBuffer.empty()) continue; 

            string kataKunci = keHurufKecil(inputBuffer);
            ListMobilNode* nodeKetemu = nullptr;

            if (pilihanFilter == 2) nodeKetemu = cariDiTreeTeks(rootMerk, kataKunci);
            else if (pilihanFilter == 3) nodeKetemu = cariDiTreeTeks(rootKondisi, kataKunci);
            else if (pilihanFilter == 4) nodeKetemu = cariDiTreeTeks(rootBenua, kataKunci);
            else if (pilihanFilter == 5) nodeKetemu = cariDiTreeTeks(rootTransmisi, kataKunci);
            else if (pilihanFilter == 6) nodeKetemu = cariDiTreeTeks(rootTipe, kataKunci);

            hasilPencarian = salinList(nodeKetemu);
        } else {
            continue;
        }

        urutkanListMobil(hasilPencarian); 
        cetakHasilFilter(hasilPencarian); 
        hapusListBantuan(hasilPencarian); 
        
        cout << "\nTekan Enter untuk kembali ke Menu Filter..." << endl;
        string pauseBuffer;
        getline(cin, pauseBuffer); 
    } 
}