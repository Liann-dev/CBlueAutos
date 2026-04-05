#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <vector>
#include <optional>
#include <iomanip>
#include "features.h"

using namespace std;

extern Kategori showroom[3];
const string dbMobil = "database_mobil.csv";

// Fungsi pembantu untuk menulis ulang seluruh database dari linked list ke CSV
void sinkronisasiKeCSV()
{
    ofstream file(dbMobil.c_str());
    if (!file.is_open())
        return;

    file << "ID,Merk,Model,Tahun,Kondisi\n"; // Header
    for (int i = 0; i < 3; i++)
    {
        Mobil *temp = showroom[i].head;
        while (temp != nullptr)
        {
            file << temp->id << ","
                 << showroom[i].NamaMerk << ","
                 << temp->Model << ","
                 << temp->Tahun << ","
                 << temp->Kondisi << "\n";
            temp = temp->next;
        }
    }
    file.close();
}

void showTableData()
{
    cout << "\n"
         << setfill('=') << setw(70) << "=" << setfill(' ') << endl; // gunakan setfill menggunakan library iomanip
    cout << left
         << setw(5) << "ID"
         << setw(12) << "MERK"
         << setw(22) << "MODEL"
         << setw(8) << "TAHUN"
         << "KONDISI" << endl;
    cout << setfill('-') << setw(70) << "-" << setfill(' ') << endl;

    for (int i = 0; i < 3; i++)
    {
        Mobil *temp = showroom[i].head;
        while (temp != nullptr)
        {
            cout << left
                 << setw(5) << temp->id
                 << setw(12) << showroom[i].NamaMerk
                 << setw(22) << temp->Model
                 << setw(8) << temp->Tahun
                 << temp->Kondisi << endl;
            temp = temp->next;
        }
    }
    int jumlah = sizeof(showroom) / sizeof(showroom[0]);
    cout << jumlah << endl;
}

void updateMobilAdmin()
{
    int targetId;
    string kondisiBaru;
    string modelBaru;
    string merkBaru;
    optional<int> tahunBaru;
    int y;
    // int index;
    bool ditemukan = false;

    cout << "\n======================================" << endl;
    cout << "     UPDATE UNIT MOBIL (ADMIN)        " << endl;
    cout << "======================================" << endl
         << endl
         << endl
         << endl;

    showTableData();

    cout << "Masukkan ID Mobil yang ingin diupdate: ";
    if (!(cin >> targetId))
    {
        cin.clear();
        cin.ignore(10000, '\n');
        cout << "[Error] Input ID harus berupa angka!\n";
        return;
    }

    // Mencari mobil berdasarkan ID di dalam linked list showroom
    for (int i = 0; i < 3; i++)
    {
        Mobil *temp = showroom[i].head;
        while (temp != nullptr)
        {
            if (temp->id == targetId)
            {
                cout << "\nData Ditemukan:" << endl;
                cout << "Merk    : " << showroom[i].NamaMerk << endl;
                cout << "Model   : " << temp->Model << endl;
                cout << "Kondisi : " << temp->Kondisi << endl;

                cout << "\n"
                     << setfill('-') << setw(80) << "-" << setfill(' ') << endl;
                cout << left << setw(25) << "UBAH DATA UNIT (ID: " << targetId << ") (kOSONGKAN JIKA TIDAK INGIN DIUBAH)" << endl;
                cout << left << setw(5) << showroom[i].NamaMerk
                     << setw(22) << temp->Model
                     << setw(8) << temp->Tahun
                     << temp->Kondisi << endl;
                cout
                    << "\n"
                    << setfill('-') << setw(80) << "-" << setfill(' ') << endl;

                cout << "\nMasukan Merk Baru: ";
                cin.ignore();
                getline(cin, merkBaru);
                if (merkBaru == "")
                {
                    merkBaru = showroom[i].NamaMerk;
                }

                cout << "\nMasukan Model Baru: ";
                cin;
                getline(cin, modelBaru);
                if (modelBaru == "")
                {
                    modelBaru = temp->Model;
                }

                cout << "\nMasukkan Kondisi Baru: ";
                cin.ignore();
                getline(cin, kondisiBaru);

                if (kondisiBaru == "")
                {
                    kondisiBaru = temp->Kondisi;
                }

                cout << "\nMasukan Tahun pembuatan baru: ";

                if (cin >> y)
                {
                    tahunBaru = y;
                }
                else
                {
                    tahunBaru = nullopt;
                }

                if (!tahunBaru)
                {
                    tahunBaru = temp->Tahun; // rawan error
                }

                // Update data di memori
                temp->Kondisi = kondisiBaru;
                temp->Model = modelBaru;
                temp->Tahun = *tahunBaru;
                ditemukan = true;
                break;
            }
            temp = temp->next;
        }
        if (ditemukan)
            break;
    }

    if (ditemukan)
    {
        // Simpan perubahan permanen ke file CSV
        sinkronisasiKeCSV();
        cout << "[Sukses] Kondisi unit dengan ID " << targetId << " berhasil diperbarui!\n";
    }
    else
    {
        cout << "[Error] Unit dengan ID " << targetId << " tidak ditemukan!\n";
    }
}