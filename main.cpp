#include <iostream>
#include <string>
#include <fstream>
#include <windows.h>
using std::string;
using std::cin;
using std::getline;
using std::ifstream;
using std::cout;
using std::endl;
using std::ofstream;



int gautiBaitus(string t);

int main() {
    SetConsoleOutputCP(CP_UTF8); // Nustatome konsolės išvesties koduotę į UTF-8
    SetConsoleCP(CP_UTF8); // Nustatome konsolės įvesties koduotę į UTF-8

    string tekstas;
    cout<<" iveskite teksta:"<<endl;
    getline(cin, tekstas);

    
    int baitai = gautiBaitus(tekstas);
    cout << "Baitų skaičius: " << baitai << endl;
    cout << std::hex << baitai << endl;
    return 0;
}
int gautiBaitus(string t)
{
    int visiBaitai = 0;
     for(int i = 0; i < t.length(); i++)
    {
       unsigned char simbolis = t.at(i);
        //cout << int(simbolis) * i << " ";
        visiBaitai += int(simbolis) * (i + 1);
    }
    return visiBaitai;
}