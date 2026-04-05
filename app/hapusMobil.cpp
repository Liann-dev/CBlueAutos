#include <iostream>
#include <string>
#include "features.h"
#include <cctype>
#include <iomanip>

using namespace std;

void hapusMobilAdmin()
{
    string target;
    int targetId;
    int choice;
    cout << "\n======================================" << endl;
    cout << "     HAPUS UNIT MOBIL (ADMIN)        " << endl;
    cout << "======================================" << endl
         << endl
         << endl;

    cout << "Ingin hapus berdasarkan apa? (1. Nama Model / 2. ID Model): ";
    cin >> choice;
    showTableData();
    cout << endl
         << endl;

    // cout << "Masukkan Nama Model atau ID Model yang akan dihapus: ";
    // cin.ignore();
    // getline(cin, target);
    if (choice == 1)
    {
        cout << "Masukkan Nama Model yang akan dihapus: ";
        cin.ignore();
        getline(cin, target);

        if (target.empty())
        {
            cout << "[Error] Input tidak boleh kosong!\n";
            return;
        }
    }
    else if (choice == 2)
    {
        cout << "Masukkan ID Model yang akan dihapus: ";
        if (!(cin >> targetId))
        {
            cin.clear();
            cin.ignore(10000, '\n');
            cout << "[Error] Input ID harus berupa angka!\n";
            return;
        }
    }
    else
    {
        cout << "Pilihan tidak valid!\n";
        return;
    }

    for (Kategori *currKat = headKategori; currKat != nullptr; currKat = currKat->next)
    {
        for (Mobil *temp = currKat->head; temp != nullptr; temp = temp->next)
        {
            if (choice == 1 && temp->Model == target)
            {
                cout << "\n"
                     << setfill('-') << setw(80) << "-" << setfill(' ') << endl;
                cout << left << "KONFIRMASI DATA:  " << endl
                     << endl;
                cout << "Id      : " << temp->id << endl;
                cout << "Merk    : " << currKat->NamaMerk << endl;
                cout << "Model   : " << temp->Model << endl;
                cout << "Tahun   : " << temp->Tahun << endl;
                cout << "Kondisi : " << temp->Kondisi << endl;
                cout << setfill('-') << setw(80) << "-" << setfill(' ') << endl;

                cout << endl
                     << endl;
            }
            else if (choice == 2 && temp->id == targetId)
            {
                cout << "\n"
                     << setfill('-') << setw(80) << "-" << setfill(' ') << endl;
                cout << left << "KONFIRMASI DATA:  " << endl
                     << endl;

                cout << "Merk    : " << currKat->NamaMerk << endl;
                cout << "Model   : " << temp->Model << endl;
                cout << "Tahun   : " << temp->Tahun << endl;
                cout << "Kondisi : " << temp->Kondisi << endl;
                cout << setfill('-') << setw(80) << "-" << setfill(' ') << endl;

                cout << endl
                     << endl;
            }
        }
    }

    cout << "\n[Konfirmasi] Apakah Anda yakin ingin menghapus unit '" << target << "'? (y/n): ";
    char konfirmasi;
    cin >> konfirmasi;
    if (konfirmasi != 'y' && konfirmasi != 'Y')
    {
        cout << "\n[Hapus dibatalkan!]\n";
        return;
    }

    for (int i = 0; i < target.length(); i++)
    {
        if (i == 0 || target[i - 1] == ' ')
        {
            target[i] = toupper(static_cast<unsigned char>(target[i]));
        }
    }

    bool ditemukan = false;
    Kategori *currKat = headKategori;
    while (currKat != nullptr)
    {
        Mobil *temp = currKat->head;
        while (temp != nullptr)
        {
            if (temp->Model == target)
            {
                if (temp->prev == nullptr)
                {
                    currKat->head = temp->next;
                    if (currKat->head != nullptr)
                        currKat->head->prev = nullptr;
                }
                else
                {
                    temp->prev->next = temp->next;
                    if (temp->next != nullptr)
                        temp->next->prev = temp->prev;
                }

                delete temp;
                ditemukan = true;
                break;
            }
            else if (temp->id == targetId)
            {
                if (temp->prev == nullptr)
                {
                    currKat->head = temp->next;
                    if (currKat->head != nullptr)
                        currKat->head->prev = nullptr;
                }
                else
                {
                    temp->prev->next = temp->next;
                    if (temp->next != nullptr)
                        temp->next->prev = temp->prev;
                }

                delete temp;
                ditemukan = true;
                break;
            }
            temp = temp->next;
        }

        if (ditemukan)
        {
            sinkronisasiKeCSV();
            break;
        }
        currKat = currKat->next;
    }

    if (ditemukan)
        cout << "[Sukses] Unit '" << target << "' berhasil dihapus.\n";
    else
        cout << "[Error] Unit tidak ditemukan!\n";
}