#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <algorithm>
#include <iomanip>
#include "homeUser.h"

using namespace std;

const int MAX_MOBIL = 500;

// ======================
// STRUCT MOBIL
// ======================

struct Mobil
{
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

// ======================
// STRUCT TREE
// ======================

struct TreeNode
{
    string kategori;

    int daftarMobil[MAX_MOBIL];
    int jumlahMobil;

    TreeNode* left;
    TreeNode* right;
};

// ======================
// STRUCT SKOR
// ======================

struct SkorMobil
{
    int idMobil;
    int skor;
};

// ======================
// CREATE NODE
// ======================

TreeNode* createNode(string kategori)
{
    TreeNode* baru = new TreeNode;

    baru->kategori = kategori;
    baru->jumlahMobil = 0;

    baru->left = NULL;
    baru->right = NULL;

    return baru;
}

// ======================
// CARI KATEGORI
// ======================

TreeNode* cariKategori(TreeNode* root,
                       string kategori)
{
    if(root == NULL)
        return NULL;

    if(root->kategori == kategori)
        return root;

    TreeNode* kiri =
        cariKategori(root->left, kategori);

    if(kiri != NULL)
        return kiri;

    return cariKategori(root->right, kategori);
}

// ======================
// TAMBAH KE KATEGORI
// ======================

void tambahKeKategori(TreeNode* root,
                      string kategori,
                      int idMobil)
{
    TreeNode* node =
        cariKategori(root, kategori);

    if(node == NULL)
        return;

    node->daftarMobil[node->jumlahMobil]
        = idMobil;

    node->jumlahMobil++;
}

// ======================
// LOAD CSV
// ======================

void loadMobil(string namaFile)
{
    ifstream file(namaFile);

    string line;

    getline(file, line);

    while(getline(file, line))
    {
        stringstream ss(line);

        string temp;

        Mobil m;

        getline(ss, temp, ',');
        m.id = stoi(temp);

        getline(ss, m.merk, ',');

        getline(ss, m.model, ',');

        getline(ss, temp, ',');
        m.tahun = stoi(temp);

        getline(ss, m.kondisi, ',');

        getline(ss, m.benua, ',');

        getline(ss, m.transmisi, ',');

        getline(ss, m.tipe, ',');

        dataMobil[jumlahMobil++] = m;
    }


    file.close();
}

string loadPreference(int idUser)
{
    ifstream file("database_prefensi.csv");

    string line;

    // lewati header
    getline(file, line);


    if(!file.is_open()){
        cout << "File Gagal dibuka"
             << endl;
        return "";
    }

    while(getline(file, line))
    {
        stringstream ss(line);

        string temp;

        int id;
        int userId;
        string preference;

        getline(ss, temp, ',');
        id = stoi(temp);

        getline(ss, temp, ',');
        userId = stoi(temp);

        getline(ss, preference);


        if(userId == idUser)
        {
            file.close();
            return preference;
        }
    }

    file.close();
    return "";
}

// ======================
// BUILD TREE INDEX
// ======================

void buildTreeIndex(TreeNode* root)
{
    for(int i = 0; i < jumlahMobil; i++)
    {
        Mobil m = dataMobil[i];

        // Responsive
        if(m.transmisi == "Manual")
            tambahKeKategori(root,
                             "Responsive",
                             m.id);

        // Relaxed
        if(m.transmisi == "Auto")
            tambahKeKategori(root,
                             "Relaxed",
                             m.id);

        // Classic
        if(m.tahun < 2000)
            tambahKeKategori(root,
                             "Classic Car",
                             m.id);

        // Modern
        if(m.tahun >= 2000)
            tambahKeKategori(root,
                             "Modern Car",
                             m.id);

        // JDM
        if(m.benua == "Asia")
            tambahKeKategori(root,
                             "JDM",
                             m.id);

        // Muscle
        if(m.benua == "Amerika")
            tambahKeKategori(root,
                             "Muscle",
                             m.id);

        // Aero
        if(m.benua == "Eropa")
            tambahKeKategori(root,
                             "Aero",
                             m.id);

        // City
        if(m.tipe == "Hatchback")
            tambahKeKategori(root,
                             "City",
                             m.id);

        // Family
        if(m.tipe == "MPV")
            tambahKeKategori(root,
                             "Family",
                             m.id);

        // High Ground
        if(m.tipe == "SUV")
            tambahKeKategori(root,
                             "High Ground",
                             m.id);

        // Luxury
        if(m.tipe == "Sport")
            tambahKeKategori(root,
                             "Luxury",
                             m.id);

        // Performance
        if(m.tipe == "Sport")
            tambahKeKategori(root,
                             "Performance",
                             m.id);

        // Like New
        if(m.kondisi == "Mint" ||
           m.kondisi == "Brand New")
        {
            tambahKeKategori(root,
                             "Like New",
                             m.id);
        }

        // For Hobbyists
        if(m.kondisi == "Project Car")
        {
            tambahKeKategori(root,
                             "For Hobbyists",
                             m.id);
        }

        // Aerodinamis
        if(m.tipe == "Sedan" ||
           m.tipe == "Sport")
        {
            tambahKeKategori(root,
                             "Aerodinamis",
                             m.id);
        }

        // Elegant
        if(m.benua == "Eropa" &&
           m.tipe == "Sedan")
        {
            tambahKeKategori(root,
                             "Elegant",
                             m.id);
        }

        // National Car
        if(m.merk == "Esemka" ||
           m.merk == "Pindad")
        {
            tambahKeKategori(root,
                             "National Car",
                             m.id);
        }
    }
}

// ======================
// SPLIT PREFERENCE
// ======================

void splitPreference(
    string data,
    string hasil[],
    int& jumlah)
{
    string temp = "";

    for(char c : data)
    {
        if(c == '|')
        {
            hasil[jumlah++] = temp;
            temp = "";
        }
        else
        {
            temp += c;
        }
    }

    hasil[jumlah++] = temp;
}

// ======================
// MAIN
// ======================

void recomendation(int userId)
{
    // ------------------
    // LOAD DATA
    // ------------------

    loadMobil("database_mobil.csv");

    // ------------------
    // BUILD TREE
    // ------------------

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

    // kategori lain bisa ditambahkan
    // sesuai kebutuhan

    buildTreeIndex(root);

    // ------------------
    // USER PREFERENCE
    // ------------------

    string preferensi = loadPreference(userId);

    if(preferensi == ""){
        cout << "Preference not found" << endl;
        return;
    }
       

    string pref[20];
    int jumlahPref = 0;

    splitPreference(
        preferensi,
        pref,
        jumlahPref);

    // ------------------
    // INIT SCORE
    // ------------------

    SkorMobil skor[MAX_MOBIL];

    for(int i=0;i<jumlahMobil;i++)
    {
        skor[i].idMobil =
            dataMobil[i].id;

        skor[i].skor = 0;
    }

    // ------------------
    // HITUNG SKOR
    // ------------------

    for(int p=0;p<jumlahPref;p++)
    {
        TreeNode* node =
            cariKategori(root,
                         pref[p]);

        if(node == NULL)
            continue;

        for(int i=0;i<node->jumlahMobil;i++)
        {
            int id =
                node->daftarMobil[i];

            for(int j=0;j<jumlahMobil;j++)
            {
                if(skor[j].idMobil
                    == id)
                {
                    skor[j].skor++;
                    break;
                }
            }
        }
    }

    for(int i=0;i<jumlahMobil-1;i++)
    {
        for(int j=0;
            j<jumlahMobil-i-1;
            j++)
        {
            if(skor[j].skor <
               skor[j+1].skor)
            {
                SkorMobil temp =
                    skor[j];

                skor[j] =
                    skor[j+1];

                skor[j+1] =
                    temp;
            }
        }
    }

cout << "\n=========================================\n";
cout << "🔥 THE CAR THAT MEANT FOR YOU:\n";
cout << "=========================================\n";

for(int i = 0; i < 5 && i < jumlahMobil; i++)
{
    int id = skor[i].idMobil;

    for(int j = 0; j < jumlahMobil; j++)
    {
        if(dataMobil[j].id == id)
        {
            cout << "+---------------------------------------+\n";

            cout << "| 🚗 "
                 << left << setw(33)
                 << (dataMobil[j].merk + " " + dataMobil[j].model)
                 << "|\n";

            cout << "| 📅 "
                 << left << setw(33)
                 << dataMobil[j].tahun
                 << "|\n";

            cout << "| ⚙️  "
                 << left << setw(33)
                 << dataMobil[j].transmisi
                 << "|\n";

            cout << "| 🏁 "
                 << left << setw(33)
                 << dataMobil[j].tipe
                 << "|\n";

            cout << "| ⭐ "
                 << left << setw(33)
                 << dataMobil[j].kondisi
                 << "|\n";

            cout << "| ID: "
                 << left << setw(30)
                 << dataMobil[j].id
                 << "|\n";

            cout << "+---------------------------------------+\n";

            break;
        }
    }
}

}