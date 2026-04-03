#include <iostream>
using namespace std;

struct Car {
    int year;
    string brand;
    string model;
};

struct Node {
    Car data;
    Node* next;
};

void showCars(Node* head) {
    Node* temp = head;
    int i = 1;

    while (temp != NULL) {
        cout << i++ << ". "
             << temp->data.year << " | "
             << temp->data.brand << " | "
             << temp->data.model << endl;
        temp = temp->next;
    }
}

void addCar(Node*& head) {
    Car car;

    cout << "Tahun: ";
    cin >> car.year;
    cin.ignore();

    cout << "Brand: ";
    getline(cin, car.brand);

    cout << "Model: ";
    getline(cin, car.model);

    Node* newNode = new Node{car, NULL};

    if (head == NULL) {
        head = newNode;
    } else {
        Node* temp = head;
        while (temp->next != NULL)
            temp = temp->next;

        temp->next = newNode;
    }

    cout << "Mobil berhasil ditambahkan!\n";
}

void updateCar(Node* head) {
    int index;
    cout << "Pilih nomor mobil: ";
    cin >> index;

    Node* temp = head;
    int i = 1;

    while (temp != NULL && i < index) {
        temp = temp->next;
        i++;
    }

    if (temp == NULL) {
        cout << "Data tidak ditemukan!\n";
        return;
    }

    cin.ignore();
    cout << "Brand baru: ";
    getline(cin, temp->data.brand);

    cout << "Model baru: ";
    getline(cin, temp->data.model);

    cout << "Tahun baru: ";
    cin >> temp->data.year;

    cout << "Data berhasil diupdate!\n";
}

void deleteCar(Node*& head) {
    int index;
    cout << "Pilih nomor mobil: ";
    cin >> index;

    if (head == NULL) return;

    if (index == 1) {
        Node* del = head;
        head = head->next;
        delete del;
        cout << "Data terhapus!\n";
        return;
    }

    Node* temp = head;
    for (int i = 1; i < index - 1; i++) {
        temp = temp->next;
    }

    if (temp == NULL || temp->next == NULL) {
        cout << "Data tidak ditemukan!\n";
        return;
    }

    Node* del = temp->next;
    temp->next = del->next;
    delete del;

    cout << "Data terhapus!\n";
}