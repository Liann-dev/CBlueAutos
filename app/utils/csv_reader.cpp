#include <iostream>
#include <fstream>
#include <sstream>
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

void insert(Node*& head, Car car) {
    Node* newNode = new Node{car, NULL};

    if (head == NULL) {
        head = newNode;
        return;
    }

    Node* temp = head;
    while (temp->next != NULL)
        temp = temp->next;

    temp->next = newNode;
}

Node* loadCSV(string path) {
    ifstream file(path);
    if (!file.is_open()) {
        cout << "File gagal dibuka!\n";
        return NULL;
    }

    Node* head = NULL;
    string line;

    getline(file, line); // skip header

    while (getline(file, line)) {
        stringstream ss(line);
        string year, brand, model;

        getline(ss, year, ',');
        getline(ss, brand, ',');
        getline(ss, model, ',');

        Car car;
        car.year = stoi(year);
        car.brand = brand;
        car.model = model;

        insert(head, car);
    }

    return head;
}

void saveCSV(string path, Node* head) {
    ofstream file(path);

    file << "Tahun Rilis,Pabrikan,Model Mobil\n";

    Node* temp = head;
    while (temp != NULL) {
        file << temp->data.year << ","
             << temp->data.brand << ","
             << temp->data.model << "\n";
        temp = temp->next;
    }

    file.close();
}