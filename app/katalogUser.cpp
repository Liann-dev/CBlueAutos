#include <iostream>
#include <string>
#include <iomanip>
#include <fstream>
#include <sstream>
#include <cctype>
#include "features.h"

using namespace std;

Kategori* headKategori = nullptr;
const string dbMobil = "database_mobil.csv";
Kategori* cariAtauBuatKategori(string merk) {
    Kategori* temp = headKategori;
    Kategori* tail = nullptr;

    while (temp != nullptr) {
        if (temp->NamaMerk == merk) return temp;
        tail = temp;
        temp = temp->next;
    }

    Kategori* baru = new Kategori;
    baru->NamaMerk = merk;
    baru->head = nullptr;
    baru->next = nullptr;
    baru->prev = tail;

    if (tail != nullptr) {
        tail->next = baru;
    } else {
        headKategori = baru;
    }
    return baru;
}


void inisialisasiData() {
    ifstream file(dbMobil.c_str());
    if (!file.is_open()) return;

    string line;
    getline(file, line); 

    while (getline(file, line)) {
        if(line.empty()) continue;
        
        stringstream ss(line);
        string idStr, merkStr, modelStr, tahunStr, kondisiStr;

        getline(ss, idStr,      ','); 
        getline(ss, merkStr,    ','); 
        getline(ss, modelStr,   ','); 
        getline(ss, tahunStr,   ',');
        getline(ss, kondisiStr, ','); 

        Mobil* baru   = new Mobil;
        baru->id      = stoi(idStr);
        baru->Merk    = merkStr;         
        baru->Model   = modelStr;
        baru->Tahun   = stoi(tahunStr);
        baru->Kondisi = kondisiStr;
        baru->next    = nullptr;
        baru->prev    = nullptr;
        
        // Cari atau buat kategori secara dinamis
        Kategori* kat = cariAtauBuatKategori(merkStr);
        baru->next = kat->head;
        if (kat->head != nullptr) kat->head->prev = baru;
        kat->head = baru;
    }
    file.close();
}

Mobil* merge(Mobil* a, Mobil* b) {
    if (!a) return b;
    if (!b) return a;

    if (a->id <= b->id) {
        a->next = merge(a->next, b);
        if (a->next) a->next->prev = a;
        a->prev = nullptr;
        return a;
    } else {
        b->next = merge(a, b->next);
        if (b->next) b->next->prev = b;
        b->prev = nullptr;
        return b;
    }
}

Mobil* mergeSort(Mobil* head) {
    if (!head || !head->next) return head;

    Mobil* slow = head;
    Mobil* fast = head->next;
    while (fast && fast->next) {
        slow = slow->next;
        fast = fast->next->next;
    }

    Mobil* mid = slow->next;
    slow->next = nullptr;
    if (mid) mid->prev = nullptr;

    Mobil* left  = mergeSort(head);
    Mobil* right = mergeSort(mid);

    return merge(left, right);
}


Page* bangunHalaman() {
    Mobil* allHead = nullptr;
    Mobil* allTail = nullptr;

    Kategori* currKat = headKategori;
    while (currKat != nullptr) {
        Mobil* temp = currKat->head;
        while (temp != nullptr) {
            Mobil* baru = new Mobil(*temp); 
            baru->next = nullptr;
            baru->prev = nullptr;

            if (allHead == nullptr) {
                allHead = allTail = baru;
            } else {
                allTail->next = baru;
                baru->prev    = allTail;
                allTail       = baru;
            }
            temp = temp->next;
        }
        currKat = currKat->next; 
    }

    if (allHead == nullptr) return nullptr;

    
    allHead = mergeSort(allHead);

    Page* headPage    = nullptr;
    Page* tailPage    = nullptr;
    int   nomorHal    = 1;
    Mobil* curr = allHead;

    while (curr != nullptr) {
        Page* hal         = new Page;
        hal->jumlah       = 0;
        hal->nomorHalaman = nomorHal++;
        hal->next         = nullptr;
        hal->prev         = tailPage;

        if (tailPage != nullptr) tailPage->next = hal;
        else headPage = hal;
        tailPage = hal;


        for (int i = 0; i < 10 && curr != nullptr; i++) {
            hal->items[i]     = curr;
            hal->merkItems[i] = curr->Merk; 
            hal->jumlah++;
            curr = curr->next;
        }
    }

    return headPage;
}

void cetakHalaman(Page* hal, int totalHalaman) {
    #ifdef _WIN32
        system("cls");
    #else
        system("clear");
    #endif

    cout << "\n" << setfill('=') << setw(70) << "=" << setfill(' ') << endl;
    cout << "  KATALOG MOBIL  |  Halaman " << hal->nomorHalaman
         << " dari " << totalHalaman << endl;
    cout << setfill('=') << setw(70) << "=" << setfill(' ') << endl;
    cout << left
         << setw(5)  << "ID"
         << setw(12) << "MERK"
         << setw(22) << "MODEL"
         << setw(8)  << "TAHUN"
         << "KONDISI" << endl;
    cout << setfill('-') << setw(70) << "-" << setfill(' ') << endl;

    for (int i = 0; i < hal->jumlah; i++) {
        cout << left
             << setw(5)  << hal->items[i]->id
             << setw(12) << hal->merkItems[i]
             << setw(22) << hal->items[i]->Model
             << setw(8)  << hal->items[i]->Tahun
             << hal->items[i]->Kondisi << endl;
    }

    cout << setfill('-') << setw(70) << "-" << setfill(' ') << endl;

    if (hal->prev) cout << "  << [P] Prev (Hal " << hal->prev->nomorHalaman << ")";
    else           cout << "  << (Awal)          ";
    
    cout << "    |    ";
    
    if (hal->next) cout << "[N] Next (Hal " << hal->next->nomorHalaman << ") >>";
    else           cout << "          (Akhir) >>";

    cout << "\n  [X] Kembali ke Menu" << endl;
    cout << setfill('=') << setw(70) << "=" << setfill(' ') << endl;
}

void hapusHalaman(Page* head) {
    while (head != nullptr) {
        Page* tmp = head;
        head      = head->next;
        
        for(int i = 0; i < tmp->jumlah; i++) {
            delete tmp->items[i];
        }
        
        delete tmp;
    }
}

void tampilkanKatalog() {
    Page* headPage = bangunHalaman();

    if (headPage == nullptr) {
        cout << "  >> Tidak ada data mobil dalam database.\n";
        return;
    }

    int   totalHalaman = 0;
    Page* hitung       = headPage;
    while (hitung != nullptr) { totalHalaman++; hitung = hitung->next; }

    Page* current = headPage;
    char  input;

    while (true) {
        cetakHalaman(current, totalHalaman);
        cout << "  Input (n/p/x): ";
        cin  >> input;
        
        // Memaksa apapun inputnya (n kecil atau N besar) menjadi N besar
        input = toupper(input);

        if (input == 'N') {
            if (current->next) {
                current = current->next;
            } else {
                cout << "  >> Sudah di halaman terakhir!\n";
                cin.ignore(1000, '\n'); cin.get(); // Jeda agar pesan terbaca
            }
        } else if (input == 'P') {
            if (current->prev) {
                current = current->prev;
            } else {
                cout << "  >> Sudah di halaman pertama!\n";
                cin.ignore(1000, '\n'); cin.get(); // Jeda agar pesan terbaca
            }
        } else if (input == 'X') {
            break;
        } else {
            cout << "  >> Input tidak valid! Gunakan N / P / X\n";
            cin.ignore(1000, '\n'); cin.get(); // Jeda agar pesan terbaca
        }
    }

    hapusHalaman(headPage);
}