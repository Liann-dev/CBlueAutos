#include <iostream>
#include "auth.h"
#include "homeAdmin.h"
#include "homeUser.h"
#include "windows.h"
#include "features.h"

using namespace std;

void efekNgetik(string teks, int jedaMs = 30);

int main() {
    #ifdef _WIN32
        SetConsoleOutputCP(CP_UTF8);
    #endif
    // 1. Load data dari CSV ke dalam Tree & Linked List
    inisialisasiData(); 

    User userTerdaftar;
    int mulai = 1;

    // 2. Tampilkan Splash Screen dan Onboarding HANYA saat aplikasi pertama kali dibuka
    show_splash();
    show_onboarding();

    // 3. Masuk ke Looping Menu Utama (Login/Register)
    for (; mulai == 1; ) {
        int pilihan;
        
        #ifdef _WIN32
            system("cls");
        #else
            system("clear");
        #endif

        efekNgetik("\n=== C-BLUEAUTOS ===", 10);
        cout << "1. Login\n";
        cout << "2. Register\n";
        cout << "3. Keluar\n";
        cout << "-------------------\n";
        cout << "Pilih menu: ";

        if (!(cin >> pilihan)) {
            cin.clear();
            cin.ignore(10000, '\n');
            continue;
        }
        
        if (cin.peek() == '\n' || cin.peek() == '\r') {
            cin.ignore();
        }

        if (pilihan == 1) {
            bool loginBerhasil = loginUser(userTerdaftar);

            if (loginBerhasil) {
                if (userTerdaftar.role == "admin") {
                    loading_admin_transition(); 
                    menuUtamaAdmin(userTerdaftar.role);
                    loading_exit_admin(); 

                } else if (userTerdaftar.role == "user") {
                    cout << "\nMemasuki Garasi Utama...\n";
                    
                    menuUtama(userTerdaftar.role, userTerdaftar.login_count); 
                } else {
                    cout << "Role tidak dikenali. Kembali ke menu utama.\n";
                    cin.get();
                }
            } 
        } 
        else if (pilihan == 2) {
            registerUser();
        } 
        else if (pilihan == 3) {
            #ifdef _WIN32
                system("cls");
            #else
                system("clear");
            #endif
            cout << "\n\n\n";
            efekNgetik("    Menyimpan semua pengaturan...", 30);
            efekNgetik("    Mematikan mesin C-BlueAutos...", 40);
            efekNgetik("    Sampai jumpa di jalan raya!\n\n", 50);
            mulai = 0;
        } 
        else {
            cout << "Pilihan tidak valid. Tekan Enter untuk mengulang.\n";
            cin.get();
        }
    }
    
    return 0;
}