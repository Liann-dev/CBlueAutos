#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include <fstream>
#include <iomanip>
#include "homeUser.h"
#include "features.h"

using namespace std;
string namaFile = "database_prefensi.csv";

void tampilkanPreferensiTag(int id_user) {

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
        int inputs[3];
        int jumlahTag = 0;
        string tags[3];

        while (ss >> angka) {
            if (jumlahTag < 3 ) {
                inputs[jumlahTag] = angka;
            }
            jumlahTag++;
        }

        if (jumlahTag > 3) {
            cout << "\nMaksimal hanya 3 tag! Coba lagi: ";
            getline(cin, input);
            continue;
        }

        cout << "\n" << "Preferensi yang dipilih adalah:\n";
        for (int i = 0; i < 3; i++) {
            cout << inputs[i] << ". " << styles[inputs[i] - 1] << endl;
        }

        for (int i = 0; i < 3; i++) {
            tags[i] = styles[inputs[i] - 1];
        }

        integrasiDatabase(id_user, tags);
        break;



    }
    

    cout << "\nPreferensi berhasil disimpan!\n";
}

// integrasi dengan database
void integrasiDatabase(int idUser, string referensi[3])
{

    // Membaca file untuk mencari id terakhir
    ifstream fileBaca(namaFile);
    string line;
    int lastId = 0;

    // Lewati header
    getline(fileBaca, line);

    while (getline(fileBaca, line))
    {
        if (!line.empty())
        {
            lastId++;
        }
    }

    fileBaca.close();

    int id = lastId + 1;

    // Append data baru
    ofstream fileTulis(namaFile, ios::app);

    fileTulis << id << ","
              << idUser << ","
              << referensi[0] << "|"
              << referensi[1] << "|"
              << referensi[2] << "\n";

    fileTulis.close();
}



void menuUtama(string role, string login_count, int id_user) {

    if (login_count == "1") {
        tampilkanPreferensiTag(id_user);
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