#include <iostream>
#include <string>
#include <algorithm>
#include <iomanip>
#include <fstream>
#include <sstream>
#include "features.h"

using namespace std;

extern Kategori showroom[3];
const int jumlahMerk = sizeof(showroom) / sizeof(showroom[0]);
const string dbMobil = "database_mobil.csv";

int getNextMobilId()
{
    ifstream file(dbMobil.c_str());
    string line;
    int lastId = 0;
    if (!file.is_open())
        return 1;

    getline(file, line);
    while (getline(file, line))
    {
        stringstream ss(line);
        string idStr;
        if (getline(ss, idStr, ','))
        {
            try
            {
                lastId = stoi(idStr);
            }
            catch (...)
            {
            }
        }
    }
    return lastId + 1;
}

void tambahMobilAdmin()
{
    string merkBaru, modelBaru, kondisiBaru;
    int tahunBaru;

    cout << "\n======================================" << endl;
    cout << "     TAMBAH UNIT MOBIL (ADMIN)        " << endl;
    cout << "======================================" << endl;

    cout << "Masukkan Nama Merk: ";
    cin.ignore(10000, '\n');
    getline(cin, merkBaru);

    cout << "Nama Model        : ";
    getline(cin, modelBaru);

    string merkKecil = keHurufKecil(merkBaru);
    string modelKecil = keHurufKecil(modelBaru);

    if (merkKecil == modelKecil)
    {
        cout << "\n[ERROR] Merk dan model tidak boleh sama!" << endl;
        return tambahMobilAdmin();
    }

    cout << "Tahun Rilis       : ";
    cin >> tahunBaru;

    bool kondisiValid = false;
    int pilihanKondisi;

    while (!kondisiValid)
    {
        cout << "\nPilih Kondisi Mobil:\n";
        cout << "1. Brand New\n";
        cout << "2. Mint\n";
        cout << "3. Excellent\n";
        cout << "4. Good\n";
        cout << "5. Project Car\n";
        cout << "Masukkan pilihan (1-5): ";

        cin >> pilihanKondisi;

        if (cin.fail())
        { // Jika user memasukkan huruf/karakter selain angka
            cin.clear();
            cin.ignore(10000, '\n');
            cout << "[ERROR] Input harus berupa angka (1-5)!\n";
        }
        else
        {
            switch (pilihanKondisi)
            {
            case 1:
                kondisiBaru = "Brand New";
                kondisiValid = true;
                break;
            case 2:
                kondisiBaru = "Mint";
                kondisiValid = true;
                break;
            case 3:
                kondisiBaru = "Excellent";
                kondisiValid = true;
                break;
            case 4:
                kondisiBaru = "Good";
                kondisiValid = true;
                break;
            case 5:
                kondisiBaru = "Project Car";
                kondisiValid = true;
                break;
            default:
                cout << "[ERROR] Pilihan tidak valid! Silakan pilih angka 1 sampai 5.\n";
            }
        }
    }

    int idBaru = getNextMobilId();

    bool perluNewline = false;
    ifstream fileCek(dbMobil.c_str(), ios::binary);
    if (fileCek.is_open())
    {
        fileCek.seekg(0, ios::end);
        if (fileCek.tellg() > 0)
        {
            fileCek.seekg(-1, ios::cur);
            char lastChar;
            fileCek.get(lastChar);
            if (lastChar != '\n')
            {
                perluNewline = true;
            }
        }
        fileCek.close();
    }

    ofstream file(dbMobil.c_str(), ios::app);
    if (file.is_open())
    {
        if (perluNewline)
            file << "\n";

        file << idBaru << ","
             << merkBaru << ","
             << modelBaru << ","
             << tahunBaru << ","
             << kondisiBaru << "\n";
        file.close();

        for (int i = 0; i < 3; i++)
        {
            if (keHurufKecil(showroom[i].NamaMerk) == keHurufKecil(merkBaru))
            {
                tambahUnit(showroom[i], modelBaru, tahunBaru, kondisiBaru);
                break;
            }
        }

        cout << "\n[SUKSES] Unit dengan ID " << idBaru << " berhasil ditambahkan!" << endl;
    }
    else
    {
        cout << "\n[ERROR] Gagal membuka file database_mobil.csv!" << endl;
    }
}