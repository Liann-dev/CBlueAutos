#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include <iomanip>
#include "homeUser.h"
#include "features.h"

using namespace std;

void tampilkanPreferensiTag() {

    cout << "\n=======================================================================\n";
    cout << "               WELCOME! LET'S BUILD YOUR DREAM GARAGE\n";
    cout << "=======================================================================\n";
    cout << "Select at least 3 tags that best describe your automotive taste\n";
    cout << "so we can recommend the perfect cars for you!\n\n";

    vector<string> styles = {
        "JDM", "Muscle", "Aero", "Relaxed", "Responsive",
        "City", "Family", "Modern Car", "Luxury", "Performance",
        "Classic Car", "National Car", "Aerodinamis", "Elegant", "For Hobbyists",
        "Like New", "High Ground"
    };

    int total    = styles.size();
    int rows     = 5;
    int colWidth = 22;
    int numCols  = (total + rows - 1) / rows;

    for (int r = 0; r < rows; r++) {
        for (int c = 0; c < numCols; c++) {
            int idx = c * rows + r;
            if (idx < total) {
                string entry = to_string(idx + 1) + ". " + styles[idx];
                cout << left << setw(colWidth) << entry;
            }
        }
        cout << "\n";
    }

    string input;
    cout << "\nChoices (min 3, pisah spasi): ";
    getline(cin, input);

    while (true) {
        stringstream ss(input);
        int angka;
        int jumlahTag = 0;

        while (ss >> angka) {
            jumlahTag++;
        }

        if (jumlahTag > 3) {
            cout << "\nMaksimal hanya 3 tag! Coba lagi: ";
            getline(cin, input);
            continue;
        }

        break;
    }

    cout << "\nPreferensi berhasil disimpan!\n";
}


void menuUtama(string role, string login_count) {

    if (login_count == "1") {
        tampilkanPreferensiTag();
    }

    int pilihan;
    bool tetapDiHome = true;

    while (tetapDiHome) {

        cout << "\n==========================================\n";
        cout << "       CBLUEAUTOS - USER MENU\n";
        cout << "==========================================\n";
        cout << " 1. Lihat Semua Koleksi (Katalog)\n";
        cout << " 2. Search\n";
        cout << " 3. Filter\n";
        cout << " 4. Logout\n";
        cout << "==========================================\n";
        cout << " Pilih opsi (1-4): ";

        cin >> pilihan;

        if (pilihan == 1){
            tampilkanKatalog();
        }
        else if (pilihan == 2){
            cariMobil();
        }
        else if (pilihan == 3){
            filterMobil();
        }
        else if (pilihan == 4){
            cout << "\nLogout...\n";
            tetapDiHome = false;
        }
        else {
            cout << "Pilihan tidak valid.\n";
        }
    }
}