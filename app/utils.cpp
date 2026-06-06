#include <iostream>
#include <string>
#include <algorithm>
#include <cctype>
#include <windows.h> 
#include <thread>
#include <chrono>


using namespace std;
const int LEBAR_LAYAR = 80;
string keHurufKecil(string teks) {
    transform(teks.begin(), teks.end(), teks.begin(),
              [](unsigned char c) -> char { return static_cast<char>(std::tolower(c)); });
    return teks;
}

void efekNgetik(string teks, int jedaMs) {
    for (char c : teks) {
        cout << c << flush;
        Sleep(jedaMs); 
    }
    cout << endl;
}

void tampilkanLoading(string pesan, int iterasi) {
    const char spinner[] = {'|', '/', '-', '\\'};
    cout << pesan << " ";
    
    for (int i = 0; i < iterasi * 4; ++i) {
        cout << spinner[i % 4] << flush;
        Sleep(100);
        cout << "\b" << flush;
    }
    cout << " \n";
}

void cetakTengah(string teks) {
    int padding = (LEBAR_LAYAR - teks.length()) / 2;
    if (padding > 0) {
        cout << string(padding, ' ') << teks << endl;
    } else {
        cout << teks << endl;
    }
}

void tungguEnter() {
    string buffer;
    getline(cin, buffer);
}

void show_splash() {
    #ifdef _WIN32
        system("cls");
    #else
        system("clear");
    #endif

    cout << "\n\n\n";
    cetakTengah("C - B L U E A U T O S");
    cetakTengah("Build Your Dream Garage");
    cout << "\n";
    cetakTengah("Memuat Sistem...");

    int total_loading = 30; 
    int padding_kiri_angka = (LEBAR_LAYAR - 34) / 2;
    string padding_kiri = string(padding_kiri_angka, ' ');

    cout << "\033[?25l"; // Sembunyikan kursor
    
    for (int i = 0; i <= total_loading; ++i) {
        Sleep(50);
        int percent = (i * 100) / total_loading;
        
        string bar_isi = "";
        if (i > 0) {
            bar_isi = string(i - 1, '='); 
            if (i < total_loading) bar_isi += ">"; 
            else bar_isi += "="; 
        }
        string bar_kosong(total_loading - i, ' ');
        
        cout << "\r" << padding_kiri << "[" << bar_isi << bar_kosong << "] " << percent << "%";
        cout.flush();
    }

    cout << "\033[?25h"; 
    cout << "\n\n";
}

void show_onboarding() {
    #ifdef _WIN32
        system("cls");
    #else
        system("clear");
    #endif
    cout << "\n\n\n\n\n\n";
    cetakTengah("[Halaman 1 dari 3]");
    cetakTengah("=========================================");
    cetakTengah("📍  TEMUKAN MOBIL IMPIAN ANDA");
    cetakTengah("=========================================");
    cetakTengah("Akses katalog kendaraan terlengkap dengan");
    cetakTengah("pencarian pintar dan filter presisi.");
    cout << "\n\n\n";
    cetakTengah(">> Tekan ENTER untuk lanjut...");
    tungguEnter();

    #ifdef _WIN32
        system("cls");
    #else
        system("clear");
    #endif
    cout << "\n\n\n\n\n\n";
    cetakTengah("[Halaman 2 dari 3]");
    cetakTengah("=========================================");
    cetakTengah("⚙️  SESUAIKAN DENGAN GAYA ANDA");
    cetakTengah("=========================================");
    cetakTengah("Sistem rekomendasi otomatis berdasarkan");
    cetakTengah("tipe bodi, transmisi, dan benua asal pabrikan.");
    cout << "\n\n\n";
    cetakTengah(">> Tekan ENTER untuk lanjut...");
    tungguEnter();

    #ifdef _WIN32
        system("cls");
    #else
        system("clear");
    #endif
    cout << "\n\n\n\n\n\n";
    cetakTengah("[Halaman 3 dari 3]");
    cetakTengah("=========================================");
    cetakTengah("🛡️  GARASI AMAN DAN TERPERCAYA");
    cetakTengah("=========================================");
    cetakTengah("Semua kondisi kendaraan telah diverifikasi");
    cetakTengah("secara ketat oleh tim C-BlueAutos.");
    cout << "\n\n\n";
    cetakTengah(">> Tekan ENTER untuk Masuk ke Aplikasi...");
    tungguEnter();
}

void loading_admin_transition() {
    #ifdef _WIN32
        system("cls");
    #else
        system("clear");
    #endif

    cout << "\n\n\n";
    cetakTengah("C - B L U E A U T O S   |   A D M I N");
    cetakTengah("Menyiapkan Otoritas Akses Anda...");
    cout << "\n";
    cetakTengah("Membuka Dashboard Administrator...");

    int total_loading = 30;
    int padding_kiri_angka = (LEBAR_LAYAR - 34) / 2;
    string padding_kiri = string(padding_kiri_angka, ' ');

    cout << "\033[?25l"; 
    
    for (int i = 0; i <= total_loading; ++i) {
        Sleep(40);
        int percent = (i * 100) / total_loading;
        
        string bar_isi = "";
        if (i > 0) {
            bar_isi = string(i - 1, '=');
            if (i < total_loading) bar_isi += ">";
            else bar_isi += "=";
        }
        string bar_kosong(total_loading - i, ' ');
        
        cout << "\r" << padding_kiri << "[" << bar_isi << bar_kosong << "] " << percent << "%";
        cout.flush();
    }

    cout << "\033[?25h"; 
    cout << "\n\n";
    Sleep(400);
}


void loading_exit_admin() {
    #ifdef _WIN32
        system("cls");
    #else
        system("clear");
    #endif

    cout << "\n\n\n";
    cetakTengah("C - B L U E A U T O S   |   A D M I N");
    cetakTengah("Menyimpan Perubahan Database...");
    cout << "\n";
    cetakTengah("Menutup Dashboard...");

    int total_loading = 30;
    int padding_kiri_angka = (LEBAR_LAYAR - 34) / 2;
    string padding_kiri = string(padding_kiri_angka, ' ');

    cout << "\033[?25l"; 
    
    for (int i = 0; i <= total_loading; ++i) {
        Sleep(25);
        int percent = (i * 100) / total_loading;
        
        string bar_isi = "";
        if (i > 0) {
            bar_isi = string(i - 1, '=');
            if (i < total_loading) bar_isi += ">";
            else bar_isi += "=";
        }
        string bar_kosong(total_loading - i, ' ');
        
        cout << "\r" << padding_kiri << "[" << bar_isi << bar_kosong << "] " << percent << "%";
        cout.flush();
    }

    cout << "\033[?25h"; 
    cout << "\n\n";
    Sleep(300);
}