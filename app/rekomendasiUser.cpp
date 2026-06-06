#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <algorithm>
#include <iomanip>
#include <ctime>
#include <cstdlib>
#include "homeUser.h"

using namespace std;

const int MAX_MOBIL = 500;

struct Mobil {
    int id;
    string merk;
    string model;
    int tahun;
    string kondisi;
    string benua;
    string transmisi;
    string tipe;
};

Mobil dataMobil[MAX_MOBIL];
int jumlahMobil = 0;

struct TreeNode {
    string kategori;
    int daftarMobil[MAX_MOBIL];
    int jumlahMobil;
    TreeNode* left;
    TreeNode* right;
};

struct SkorMobil {
    int idMobil;
    int skor;
};

TreeNode* createNode(string kategori) {
    TreeNode* baru = new TreeNode;
    baru->kategori = kategori;
    baru->jumlahMobil = 0;
    baru->left = NULL;
    baru->right = NULL;
    return baru;
}

TreeNode* cariKategori(TreeNode* root, string kategori) {
    if(root == NULL) return NULL;
    if(root->kategori == kategori) return root;

    TreeNode* kiri = cariKategori(root->left, kategori);
    if(kiri != NULL) return kiri;

    return cariKategori(root->right, kategori);
}

void tambahKeKategori(TreeNode* root, string kategori, int idMobil) {
    TreeNode* node = cariKategori(root, kategori);
    if(node == NULL) return;

    if (node->jumlahMobil < MAX_MOBIL) {
        node->daftarMobil[node->jumlahMobil] = idMobil;
        node->jumlahMobil++;
    }
}

void loadMobil(string namaFile) {
    jumlahMobil = 0; 
    ifstream file(namaFile);
    string line;
    
    if (!file.is_open()) return;

    getline(file, line); 

    while(getline(file, line)) {
        if (line.empty() || line.find_first_not_of("\r\n \t") == string::npos) continue;

        stringstream ss(line);
        string temp;
        Mobil m;

        getline(ss, temp, ',');
        try { m.id = stoi(temp); } catch(...) { continue; }

        getline(ss, m.merk, ',');
        getline(ss, m.model, ',');

        getline(ss, temp, ',');
        try { m.tahun = stoi(temp); } catch(...) { continue; }

        getline(ss, m.kondisi, ',');
        getline(ss, m.benua, ',');
        getline(ss, m.transmisi, ',');
        getline(ss, m.tipe, ',');

        if (!m.tipe.empty() && m.tipe.back() == '\r') m.tipe.pop_back();

        if (jumlahMobil < MAX_MOBIL) {
            dataMobil[jumlahMobil++] = m;
        }
    }
    file.close();
}

string loadPreference(int idUser) {
    ifstream file("database_prefensi.csv");
    string line;
    
    if(!file.is_open()) return "";

    getline(file, line); 

    while(getline(file, line)) {
        if (line.empty() || line.find_first_not_of("\r\n \t") == string::npos) continue;

        stringstream ss(line);
        string temp;
        int id;
        int userId;
        string preference;

        getline(ss, temp, ',');
        try { id = stoi(temp); } catch(...) { continue; } 

        getline(ss, temp, ',');
        try { userId = stoi(temp); } catch(...) { continue; } 

        getline(ss, preference);
        
        if (!preference.empty() && preference.back() == '\r') preference.pop_back();

        if(userId == idUser) {
            file.close();
            return preference;
        }
    }
    file.close();
    return "";
}

void buildTreeIndex(TreeNode* root) {
    for(int i = 0; i < jumlahMobil; i++) {
        Mobil m = dataMobil[i];
        if(m.transmisi == "Manual") tambahKeKategori(root, "Responsive", m.id);
        if(m.transmisi == "Auto") tambahKeKategori(root, "Relaxed", m.id);
        if(m.tahun < 2000) tambahKeKategori(root, "Classic Car", m.id);
        if(m.tahun >= 2000) tambahKeKategori(root, "Modern Car", m.id);
        if(m.benua == "Asia") tambahKeKategori(root, "JDM", m.id);
        if(m.benua == "Amerika") tambahKeKategori(root, "Muscle", m.id);
        if(m.benua == "Eropa") tambahKeKategori(root, "Aero", m.id);
        if(m.tipe == "Hatchback") tambahKeKategori(root, "City", m.id);
        if(m.tipe == "MPV") tambahKeKategori(root, "Family", m.id);
        if(m.tipe == "SUV") tambahKeKategori(root, "High Ground", m.id);
        if(m.tipe == "Sport") tambahKeKategori(root, "Luxury", m.id);
        if(m.tipe == "Sport") tambahKeKategori(root, "Performance", m.id);
        if(m.kondisi == "Mint" || m.kondisi == "Brand New") tambahKeKategori(root, "Like New", m.id);
        if(m.kondisi == "Project Car") tambahKeKategori(root, "For Hobbyists", m.id);
        if(m.tipe == "Sedan" || m.tipe == "Sport") tambahKeKategori(root, "Aerodinamis", m.id);
        if(m.benua == "Eropa" && m.tipe == "Sedan") tambahKeKategori(root, "Elegant", m.id);
        if(m.merk == "Esemka" || m.merk == "Pindad") tambahKeKategori(root, "National Car", m.id);
    }
}

void splitPreference(string data, string hasil[], int& jumlah) {
    string temp = "";
    for(char c : data) {
        if(c == '|') {
            hasil[jumlah++] = temp;
            temp = "";
        } else {
            temp += c;
        }
    }
    hasil[jumlah++] = temp;
}

void tampilkanDetailMobil(int idTarget) {
    bool ketemu = false;

    for(int i = 0; i < jumlahMobil; i++) {
        if(dataMobil[i].id == idTarget) {
            #ifdef _WIN32
                system("cls");
            #else
                system("clear");
            #endif

            cout << "\n=======================================================\n";
            cout << "             D E T A I L   K E N D A R A A N           \n";
            cout << "=======================================================\n";
            cout << "  ID Mobil     : [ " << dataMobil[i].id << " ]\n";
            cout << "  Merk & Model : " << dataMobil[i].merk << " " << dataMobil[i].model << "\n";
            cout << "  Tahun Rilis  : " << dataMobil[i].tahun << "\n";
            cout << "-------------------------------------------------------\n";
            cout << "  Spesifikasi Teknis:\n";
            cout << "  - Tipe Bodi  : " << dataMobil[i].tipe << " 🏁\n";
            cout << "  - Transmisi  : " << dataMobil[i].transmisi << " ⚙️\n";
            cout << "  - Asal Benua : " << dataMobil[i].benua << " 🌍\n";
            cout << "  - Kondisi    : " << dataMobil[i].kondisi << " ⭐\n";
            cout << "=======================================================\n";
            ketemu = true;
            break;
        }
    }

    if(!ketemu) {
        cout << "\n[!] Mobil dengan ID " << idTarget << " tidak ditemukan dalam daftar.\n";
    }

    cout << "\n>> Tekan Enter untuk kembali ke Menu Utama...";
    string pauseBuffer;
    getline(cin, pauseBuffer);
}

void recomendation(int userId) {
    loadMobil("database_mobil.csv");
    if (jumlahMobil == 0) return; 

    TreeNode* root = createNode("ROOT");

    root->left = createNode("Responsive");
    root->right = createNode("Relaxed");
    root->left->left = createNode("Classic Car");
    root->left->right = createNode("Modern Car");
    root->right->left = createNode("City");
    root->right->right = createNode("High Ground");
    root->right->left->left = createNode("Performance");
    root->right->left->right = createNode("Family");
    root->right->right->left = createNode("Luxury");
    root->right->right->right = createNode("Elegant");
    root->right->left->left->left = createNode("Aerodinamis");
    root->right->left->left->right = createNode("Like New");
    root->right->right->left->left = createNode("JDM");
    root->right->right->left->right = createNode("Muscle");
    root->right->right->right->left = createNode("Aero");
    root->right->right->right->right = createNode("National Car");
    root->right->right->right->right->left = createNode("For Hobbyists");

    buildTreeIndex(root);

    string preferensi = loadPreference(userId);
    if(preferensi == "") return;

    string pref[20];
    int jumlahPref = 0;
    splitPreference(preferensi, pref, jumlahPref);

    SkorMobil skor[MAX_MOBIL];
    for(int i=0; i<jumlahMobil; i++) {
        skor[i].idMobil = dataMobil[i].id;
        skor[i].skor = 0;
    }

    for(int p=0; p<jumlahPref; p++) {
        TreeNode* node = cariKategori(root, pref[p]);
        if(node == NULL) continue;
        for(int i=0; i<node->jumlahMobil; i++) {
            int id = node->daftarMobil[i];
            for(int j=0; j<jumlahMobil; j++) {
                if(skor[j].idMobil == id) {
                    skor[j].skor++;
                    break;
                }
            }
        }
    }

    // PENGACAKAN DATA UNTUK MIX KATEGORI
    srand(time(0));
    for(int i = jumlahMobil - 1; i > 0; i--) {
        int j = rand() % (i + 1);
        SkorMobil temp = skor[i];
        skor[i] = skor[j];
        skor[j] = temp;
    }

    // BUBBLE SORT
    for(int i=0; i<jumlahMobil-1; i++) {
        for(int j=0; j<jumlahMobil-i-1; j++) {
            if(skor[j].skor < skor[j+1].skor) {
                SkorMobil temp = skor[j];
                skor[j] = skor[j+1];
                skor[j+1] = temp;
            }
        }
    }

    if (skor[0].skor == 0) return;

    cout << "\n========================================================================\n";
    cout << "                   🔥 THE CARS THAT ARE MEANT FOR YOU:\n";
    cout << "========================================================================\n";
    cout << left << " " << setw(5) << "ID" << setw(35) << "MERK & MODEL" << setw(10) << "TAHUN" << "KONDISI\n";
    cout << "------------------------------------------------------------------------\n";

    for(int i = 0; i < 5 && i < jumlahMobil; i++) {
        int id = skor[i].idMobil;

        for(int j = 0; j < jumlahMobil; j++) {
            if(dataMobil[j].id == id) {
                string namaMobil = dataMobil[j].merk + " " + dataMobil[j].model;
                if(namaMobil.length() > 32) namaMobil = namaMobil.substr(0, 29) + "...";

                cout << left << " " << setw(5) << dataMobil[j].id 
                     << setw(35) << namaMobil 
                     << setw(10) << dataMobil[j].tahun 
                     << dataMobil[j].kondisi << "\n";
                break;
            }
        }
    }
}