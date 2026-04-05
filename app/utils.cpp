#include <iostream>
#include <string>
#include <windows.h> 

using namespace std;

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