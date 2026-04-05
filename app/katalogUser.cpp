#include <iostream>
#include <string>
#include <iomanip>
#include <fstream>
#include <sstream>
#include <cctype>
#include "features.h"

using namespace std;
Kategori showroom[3];
const string dbMobil = "database_mobil.csv";

// ==========================================
// TAMBAH UNIT
// ==========================================
void tambahUnit(Kategori &kat, string model, int tahun, string kondisi) {
    Mobil* baru   = new Mobil;
    baru->Model   = model;
    baru->Tahun   = tahun;
    baru->Kondisi = kondisi;
    baru->next    = kat.head;
    baru->prev    = nullptr;
    if (kat.head != nullptr) kat.head->prev = baru;
    kat.head = baru;
}

// ==========================================
// INISIALISASI DATA DARI CSV
// ==========================================
void inisialisasiData() {
    showroom[0].NamaMerk = "Toyota"; 
    showroom[1].NamaMerk = "Honda";
    showroom[2].NamaMerk = "Suzuki";
    
    for(int i = 0; i < 3; i++) showroom[i].head = nullptr;

    ifstream file(dbMobil.c_str());
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
        
        for(int i = 0; i < 3; i++) {
            if(showroom[i].NamaMerk == merkStr) {
                baru->next = showroom[i].head;
                if (showroom[i].head != nullptr) showroom[i].head->prev = baru;
                showroom[i].head = baru;
                break;
            }
        }
    }
    file.close();
}

// ==========================================
// MERGE SORT - Doubly Linked List by ID
// ==========================================
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

// ==========================================
// PAGINATION - Doubly Linked List of Pages
// ==========================================
Page* bangunHalaman() {

    Mobil* allHead = nullptr;
    Mobil* allTail = nullptr;

    for (int i = 0; i < 3; i++) {
        Mobil* temp = showroom[i].head;
        while (temp != nullptr) {
            Mobil* nextNode = temp->next;

            temp->next = nullptr;
            temp->prev = nullptr;

            if (allHead == nullptr) {
                allHead = allTail = temp;
            } else {
                allTail->next = temp;
                temp->prev    = allTail;
                allTail       = temp;
            }
            temp = nextNode;
        }
    }

    allHead = mergeSort(allHead);

    Page* headPage    = nullptr;
    Page* tailPage    = nullptr;
    Page* halamanSaat = nullptr;
    int   nomorHal    = 1;

    Mobil* curr = allHead;
    while (curr != nullptr) {
        if (halamanSaat == nullptr || halamanSaat->jumlah == 10) {
            Page* hal         = new Page;
            hal->jumlah       = 0;
            hal->nomorHalaman = nomorHal++;
            hal->next         = nullptr;
            hal->prev         = tailPage;

            if (tailPage != nullptr) tailPage->next = hal;
            else headPage = hal;

            tailPage    = hal;
            halamanSaat = hal;
        }

        halamanSaat->items[halamanSaat->jumlah]     = curr;
        halamanSaat->merkItems[halamanSaat->jumlah] = curr->Merk;
        halamanSaat->jumlah++;

        curr = curr->next;
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

    if (hal->prev) cout << "  << Hal " << hal->prev->nomorHalaman;
    else           cout << "  << (awal)  ";
    cout << "                        ";
    if (hal->next) cout << "Hal " << hal->next->nomorHalaman << " >>";
    else           cout << "  (akhir) >>";

    cout << "\n  [n] Next   [p] Prev   [x] Kembali ke Menu" << endl;
    cout << setfill('=') << setw(70) << "=" << setfill(' ') << endl;
}

void hapusHalaman(Page* head) {
    while (head != nullptr) {
        Page* tmp = head;
        head      = head->next;
        delete tmp;
    }
}

void tampilkanKatalog() {
    Page* headPage = bangunHalaman();

    if (headPage == nullptr) {
        cout << "  Tidak ada data mobil.\n";
        return;
    }


    int   totalHalaman = 0;
    Page* hitung       = headPage;
    while (hitung != nullptr) { totalHalaman++; hitung = hitung->next; }

    Page* current = headPage;
    char  input;

    while (true) {
        cetakHalaman(current, totalHalaman);
        cout << "  Input: ";
        cin  >> input;
        input = tolower(input);

        if (input == 'n') {
            if (current->next) current = current->next;
            else cout << "  [!] Sudah di halaman terakhir!\n";
        } else if (input == 'p') {
            if (current->prev) current = current->prev;
            else cout << "  [!] Sudah di halaman pertama!\n";
        } else if (input == 'x') {
            break;
        } else {
            cout << "  [!] Input tidak valid! Gunakan n / p / x\n";
        }
    }

    hapusHalaman(headPage);
}