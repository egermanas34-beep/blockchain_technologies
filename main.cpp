#include <iostream>
#include <string>
#include <windows.h>
using std::string;
using std::cin;
using std::getline;
using std::isalpha;
using std::tolower;
using std::ifstream;
using std::cout;
using std::endl;
using std::ofstream;
using std::ispunct;


int gautiBaitus(string t);

int main() {
SetConsoleOutputCP(CP_UTF8); // Nustatome konsolės išvesties koduotę į UTF-8
    SetConsoleCP(CP_UTF8); // Nustatome konsolės įvesties koduotę į UTF-8

    string tekstas;
    cout<<" iveskite teksta:"<<endl;
    getline(cin, tekstas);

    cout << "Baitų skaičius: " << gautiBaitus(tekstas) << endl;
    return 0;
}
int gautiBaitus(string t)
{
    int visiBaitai = 0;
     for(int i = 0; i < t.length(); i++)
    {
       unsigned char simbolis = t.at(i);
        //cout << int(simbolis) * i << " ";
        visiBaitai += int(simbolis) * i;
    }
    return visiBaitai;
}