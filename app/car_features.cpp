#include <iostream>
using namespace std;

struct Mobil {
    string merk;
    string model;
    int Tahun;
    string kondisi;
    Mobil* next;
};

void tampilkanKatalog(Mobil* head) {
    Mobil* temp = head;
    int i = 1;

    while (temp != NULL) {
        cout << i++ << ". "
             << temp->Tahun << " | "
             << temp->merk << " | "
             << temp->model << " | "
             << temp->kondisi << endl;

        temp = temp->next;
    }
}

void tambahMobilAdmin(Mobil*& head) {
    Mobil* baru = new Mobil;

    cin.ignore();

    cout << "Merk: ";
    getline(cin, baru->merk);

    cout << "Model: ";
    getline(cin, baru->model);

    cout << "Tahun: ";
    cin >> baru->Tahun;
    cin.ignore();

    do {
        cout << "Kondisi (baru/bekas): ";
        getline(cin, baru->kondisi);

        if (baru->kondisi != "baru" && baru->kondisi != "bekas") {
            cout << "Input hanya boleh 'baru' atau 'bekas'!\n";
        }

    } while (baru->kondisi != "baru" && baru->kondisi != "bekas");

    baru->next = NULL;

    if (head == NULL) {
        head = baru;
    } else {
        Mobil* temp = head;
        while (temp->next != NULL)
            temp = temp->next;

        temp->next = baru;
    }

    cout << "Mobil berhasil ditambahkan!\n";
}

void updateMobilAdmin(Mobil* head) {
    int index;
    cout << "Pilih nomor mobil: ";

    if (!(cin >> index)) {
        cin.clear();
        cin.ignore(10000, '\n');
        cout << "Input harus angka!\n";
        return;
    }

    Mobil* temp = head;
    int i = 1;

    while (temp != NULL && i < index) {
        temp = temp->next;
        i++;
    }

    if (temp == NULL) {
        cout << "Data tidak ditemukan!\n";
        return;
    }

    cout << "Data berhasil diupdate!\n";
}

void hapusMobilAdmin(Mobil*& head) {
    int index;
    cout << "Pilih nomor mobil: ";

    if (!(cin >> index)) {
        cin.clear();
        cin.ignore(10000, '\n');
        cout << "Input harus angka!\n";
        return;
    }

    if (head == NULL) return;

    if (index == 1) {
        Mobil* del = head;
        head = head->next;
        delete del;
        cout << "Data terhapus!\n";
        return;
    }

    Mobil* temp = head;
    for (int i = 1; i < index - 1; i++) {
        temp = temp->next;
    }

    if (temp == NULL || temp->next == NULL) {
        cout << "Data tidak ditemukan!\n";
        return;
    }

    Mobil* del = temp->next;
    temp->next = del->next;
    delete del;

    cout << "Data terhapus!\n";
}