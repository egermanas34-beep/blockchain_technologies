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

int main() {
SetConsoleOutputCP(CP_UTF8); // Nustatome konsolės išvesties koduotę į UTF-8
    SetConsoleCP(CP_UTF8); // Nustatome konsolės įvesties koduotę į UTF-8

    string tekstas;
    cout<<" iveskite teksta:"<<endl;
    getline(cin, tekstas);

    for(int i = 0; i < tekstas.length(); i++)
    {
        char simbolis = tekstas.at(i);
        cout << int(simbolis) << " ";
    }
    cout << endl;

    return 0;
}