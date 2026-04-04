#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
using namespace std;

struct Mobil {
    string merk;
    string model;
    int Tahun;
    string kondisi;
    Mobil* next;
};

void insert(Mobil*& head, string merk, string model, int tahun) {
    Mobil* baru = new Mobil;

    baru->merk = merk;
    baru->model = model;
    baru->Tahun = tahun;
    baru->next = NULL;

    if (head == NULL) {
        head = baru;
        return;
    }

    Mobil* temp = head;
    while (temp->next != NULL)
        temp = temp->next;

    temp->next = baru;
}

Mobil* loadCSV(string path) {
    ifstream file(path);

    if (!file.is_open()) {
        cout << "File gagal dibuka!\n";
        return NULL;
    }

    Mobil* head = NULL;
    string line;

    getline(file, line); // skip header

    while (getline(file, line)) {
        stringstream ss(line);
        string tahun, merk, model, kondisi;

        getline(ss, tahun, ',');
        getline(ss, merk, ',');
        getline(ss, model, ',');
        getline(ss, kondisi, ',');

        Mobil* baru = new Mobil;

        baru->Tahun = stoi(tahun);
        baru->merk = merk;
        baru->model = model;
        baru->kondisi = kondisi;
        baru->next = NULL;

        if (head == NULL) {
            head = baru;
        } else {
            Mobil* temp = head;
            while (temp->next != NULL)
                temp = temp->next;

            temp->next = baru;
        }
    }

    return head;
}

void saveCSV(string path, Mobil* head) {
    ofstream file(path);

    file << "Tahun Rilis,Pabrikan,Model Mobil,Kondisi\n";

    Mobil* temp = head;
    while (temp != NULL) {
        file << temp->Tahun << ","
             << temp->merk << ","
             << temp->model << ","
             << temp->kondisi << "\n";
        temp = temp->next;
    }

    file.close();
}