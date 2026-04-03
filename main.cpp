#include <iostream>
#include "app/auths/auth.h"

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


Node* loadCSV(string path);
void saveCSV(string path, Node* head);

void showCars(Node* head);
void addCar(Node*& head);
void updateCar(Node* head);
void deleteCar(Node*& head);

int main() {

    User userTerdaftar;
    string path = "data/Admin/data.csv";

    while (true) {
        int pilihan;

        cout << "\n=== CAR SHOWROOM ===\n";
        cout << "1. Login\n";
        cout << "2. Register\n";
        cout << "3. Keluar\n";
        cout << "Pilih: ";
        cin >> pilihan;
        cin.ignore();

        if (pilihan == 1) {

            if (loginUser(userTerdaftar)) {

                cout << "Login sebagai: " << userTerdaftar.role << endl;

                Node* head = loadCSV(path);

                int menu;
                do {
                    cout << "\n=== MENU SHOWROOM ===\n";
                    cout << "1. Lihat mobil\n";

                    if (userTerdaftar.role == "admin") {
                        cout << "2. Tambah mobil\n";
                        cout << "3. Update mobil\n";
                        cout << "4. Hapus mobil\n";
                    }

                    cout << "0. Logout\n";
                    cout << "Pilih: ";
                    cin >> menu;

                    switch (menu) {
                        case 1:
                            showCars(head);
                            break;

                        case 2:
                            if (userTerdaftar.role == "admin") {
                                addCar(head);
                                saveCSV(path, head);
                            }
                            break;

                        case 3:
                            if (userTerdaftar.role == "admin") {
                                showCars(head);
                                updateCar(head);
                                saveCSV(path, head);
                            }
                            break;

                        case 4:
                            if (userTerdaftar.role == "admin") {
                                showCars(head);
                                deleteCar(head);
                                saveCSV(path, head);
                            }
                            break;
                    }

                } while (menu != 0);

            } else {
                cout << "Login gagal!\n";
            }

        } else if (pilihan == 2) {
            registerUser();
        } else {
            break;
        }
    }

    return 0;
}