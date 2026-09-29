#include <iostream>
#include <iomanip>
#include <string>
#include <fstream>
#include <array>
#include <cstdint>
#include <random>
#include <windows.h>
using std::string;
using std::cin;
using std::getline;
using std::ifstream;
using std::cout;
using std::endl;
using std::ofstream;



int gautiBaitus(string t);
std::array<uint32_t, 8> gautiHash(string t);
bool nuskaitytiIsFailo(string failoPavadinimas, string& tekstas);
void isvedimas(std::array<uint32_t, 8> hash);
void failuKurimas();


int main() {
    SetConsoleOutputCP(CP_UTF8); // Nustatome konsolės išvesties koduotę į UTF-8
    SetConsoleCP(CP_UTF8); // Nustatome konsolės įvesties koduotę į UTF-8

    string tekstas;
    //cout<<" iveskite teksta:"<<endl;
   //getline(cin, tekstas);
   cout<<"Ka jus norite daryti?"<<endl;
   cout<<"1. Nuskaityti tekstą iš failo"<<endl;
   cout<<"2. Įvesti tekstą rankiniu būdu"<<endl;
   cout<<"3. Sukurti naują failą su atsitiktiniu tekstu"<<endl;
   int rinktis;
   cin>>rinktis;
    if(rinktis == 1)
    {
        system("powershell ls *.txt");
        cout << "Įveskite failo pavadinimą iš sąrašo (pvz., tekstas.txt): ";
        
        string failoPavadinimas;
        cin >> failoPavadinimas;
        if(nuskaitytiIsFailo(failoPavadinimas, tekstas))
        {
            cout << "Tekstas nuskaitytas iš failo. Baitų skaičius: " << tekstas.size() << endl;
        }
        else
        {
            cout << "Nepavyko nuskaityti teksto iš failo." << endl;
            return 1; // Grąžiname klaidos kodą
        }
    }
   if(rinktis == 2)
    {
        cout << "Įveskite tekstą:" << endl;
        getline(cin, tekstas);
    }
    if(rinktis == 3)
    {
        failuKurimas();
        cout << "Failas 'tekstas1000.txt', 'tekstas2000.txt' ir 'tekstas3000.txt' sukurti su atsitiktiniu tekstu." << endl;
    }
  
    //int baitai = gautiBaitus(tekstas);
    //cout << "Baitų skaičius: " << baitai << endl;
    //cout << std::hex << baitai << endl;
    auto hash = gautiHash(tekstas);
    isvedimas(hash);
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
std::array<uint32_t, 8> gautiHash(string t)
{ 
    std::array<uint32_t, 8> hash{};
    for(size_t i = 0; i < t.length(); i++)
    {

        unsigned char simbolis = t.at(i);
        size_t pozicija = i % 8; 
        hash[pozicija] += uint32_t(simbolis) * uint32_t(i + 1);
        if(pozicija > 0)
        {
            hash[pozicija] += hash[(pozicija +7) % 8];
        }
    }

    return hash;

}
bool nuskaitytiIsFailo(string failoPavadinimas, string& tekstas)
{
    ifstream failas(failoPavadinimas, std::ios::binary);
    if (!failas) {
        cout << "Nepavyko atidaryti failo: " << failoPavadinimas << endl;
        return false;
    }

    string eilute;
    char simbolis;
    while (failas.get(simbolis)) {
        tekstas += simbolis; // Pridedame simboli prie teksto
    }
    if (!failas.eof()) // Patikriname, ar pasiekėme failo pabaigą
    {
        cout << "Klaida skaitant failą: " << failoPavadinimas << endl;
        failas.close();
        return false;
    }
    failas.close();
    return true;
}
void isvedimas(std::array<uint32_t, 8> hash)
{
    cout << "Hash: ";
    for (const auto& h : hash) {
        cout << std::hex << std::setw(8) << std::setfill('0') << h;
    }
    cout << endl;
}
void failuKurimas()
{
    std::mt19937 generator(12345); // Naudojame fiksuotą seed, kad rezultatai būtų atkuriami
    ofstream failas("tekstas1000.txt");
    std::uniform_int_distribution<int> ascii(32, 126);
    for (int i = 0; i < 1000; i++) {
        char simbolis = static_cast<char>(ascii(generator));
        failas << simbolis;
    }
    failas.close();
    ofstream failas2("tekstas2000.txt");
    for (int i = 0; i < 2000; i++) {
        char simbolis = static_cast<char>(ascii(generator));
        failas2 << simbolis;
    }
    failas2.close();
    ofstream failas3("tekstas3000.txt");
    for (int i = 0; i < 3000; i++) {
        char simbolis = static_cast<char>(ascii(generator));
        failas3 << simbolis;
    }
    failas3.close();
}