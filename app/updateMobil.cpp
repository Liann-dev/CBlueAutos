#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <vector>
#include <optional>
#include <iomanip>
#include "features.h"

using namespace std;


const string dbMobil = "database_mobil.csv";

void sinkronisasiKeCSV()
{
    ofstream file(dbMobil.c_str());
    if (!file.is_open())
        return;

    file << "ID,Merk,Model,Tahun,Kondisi\n"; 
    
    for (Kategori* currKat = headKategori; currKat != nullptr; currKat = currKat->next)
    {
        for (Mobil* temp = currKat->head; temp != nullptr; temp = temp->next)
        {
            file << temp->id << ","
                 << currKat->NamaMerk << ","
                 << temp->Model << ","
                 << temp->Tahun << ","
                 << temp->Kondisi << "\n";
        }
    }
    file.close();
}

void showTableData()
{
    cout << "\n"
         << setfill('=') << setw(70) << "=" << setfill(' ') << endl; 
    cout << left
         << setw(5) << "ID"
         << setw(12) << "MERK"
         << setw(22) << "MODEL"
         << setw(8) << "TAHUN"
         << "KONDISI" << endl;
    cout << setfill('-') << setw(70) << "-" << setfill(' ') << endl;

    for (Kategori* currKat = headKategori; currKat != nullptr; currKat = currKat->next)
    {
        for (Mobil* temp = currKat->head; temp != nullptr; temp = temp->next)
        {
            cout << left
                 << setw(5) << temp->id
                 << setw(12) << currKat->NamaMerk
                 << setw(22) << temp->Model
                 << setw(8) << temp->Tahun
                 << temp->Kondisi << endl;
        }
    }
}

void updateMobilAdmin()
{
    int targetId;
    string kondisiBaru;
    string modelBaru;
    string inputTahun;
    int tahunBaru;
    bool ditemukan = false;

    cout << "\n======================================" << endl;
    cout << "     UPDATE UNIT MOBIL (ADMIN)        " << endl;
    cout << "======================================" << endl << endl;

    showTableData();

    cout << "\nMasukkan ID Mobil yang ingin diupdate: ";
    if (!(cin >> targetId))
    {
        cin.clear();
        cin.ignore(10000, '\n');
        cout << "[Error] Input ID harus berupa angka!\n";
        return;
    }

    for (Kategori* currKat = headKategori; currKat != nullptr; currKat = currKat->next)
    {
        for (Mobil* temp = currKat->head; temp != nullptr; temp = temp->next)
        {
            if (temp->id == targetId)
            {
                cout << "\nData Ditemukan:" << endl;
                cout << "Merk    : " << currKat->NamaMerk << endl;
                cout << "Model   : " << temp->Model << endl;
                cout << "Tahun   : " << temp->Tahun << endl;
                cout << "Kondisi : " << temp->Kondisi << endl;

                cout << "\n" << setfill('-') << setw(80) << "-" << setfill(' ') << endl;
                cout << left << "UBAH DATA UNIT (ID: " << targetId << ") (KOSONGKAN JIKA TIDAK INGIN DIUBAH)" << endl;
                cout << setfill('-') << setw(80) << "-" << setfill(' ') << endl;

                // --- UPDATE KONDISI ---
                cout << "Masukkan Kondisi Baru (Baru/Bekas): ";
                cin.ignore();
                getline(cin, kondisiBaru);

                if (kondisiBaru == "") {
                    kondisiBaru = temp->Kondisi;
                } else if (kondisiBaru != "Baru" && kondisiBaru != "Bekas") {
                    cout << "[Error] Kondisi harus 'Baru' atau 'Bekas'!\n";
                    return;
                }

                // --- UPDATE MODEL ---
                cout << "Masukan Model Baru: ";
                getline(cin, modelBaru);
                if (modelBaru == "") {
                    modelBaru = temp->Model;
                }

                // --- UPDATE TAHUN ---
                cout << "Masukan Tahun Pembuatan Baru: ";
                getline(cin, inputTahun);
                if (inputTahun == "") {
                    tahunBaru = temp->Tahun;
                } else {
                    try {
                        tahunBaru = stoi(inputTahun);
                    } catch (...) {
                        cout << "[Error] Tahun harus berupa angka valid!\n";
                        return;
                    }
                }

                temp->Kondisi = kondisiBaru;
                temp->Model = modelBaru;
                temp->Tahun = tahunBaru;
                
                ditemukan = true;
                break;
            }
        }
        if (ditemukan) break;
    }

    if (ditemukan)
    {
        sinkronisasiKeCSV();
        cout << "\n[Sukses] Kondisi unit dengan ID " << targetId << " berhasil diperbarui!\n";
    }
    else
    {
        cout << "\n[Error] Unit dengan ID " << targetId << " tidak ditemukan!\n";
    }
}