#include <iostream>
#include <string>
#include "features.h"
#include <cctype>

using namespace std;

void hapusMobilAdmin()
{
    string target;
    cout << "\n=== HAPUS UNIT MOBIL ===" << endl;
    cout << "Masukkan Nama Model yang akan dihapus: ";
    cin.ignore();
    getline(cin, target);

    if (target.empty())
    {
        cout << "[Error] Input tidak boleh kosong!\n";
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
    Kategori* currKat = headKategori;
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
                    if (currKat->head != nullptr) currKat->head->prev = nullptr;
                }
                else
                {
                    temp->prev->next = temp->next;
                    if (temp->next != nullptr) temp->next->prev = temp->prev;
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