#include <iostream>
#include <iomanip>
#include <string>
#include <fstream>
#include <array>
#include <cstdint>
#include <random>
#include <limits>
#include <chrono>
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
int eiluciuSkaicius(string & tekstas);
string gautiIstrauka(string & tekstas, int kiekEiluciu);

int main() {
    SetConsoleOutputCP(CP_UTF8); // Nustatome konsolės išvesties koduotę į UTF-8
    SetConsoleCP(CP_UTF8); // Nustatome konsolės įvesties koduotę į UTF-8

    string tekstas;
    int eilute = 1; //cia eilutes reikalingos darbui su konstitucija.txt
    
   cout<<"Ka jus norite daryti?"<<endl;
   cout<<"1. Nuskaityti tekstą iš failo"<<endl;
   cout<<"2. Įvesti tekstą rankiniu būdu"<<endl;
   cout<<"3. Sukurti naują failą su atsitiktiniu tekstu"<<endl;
   cout<<"4. Patikrtinti determinizmą sekoje"<<endl;
   cout<<"5. Patikrinti determinizmą su vienodu tekstu"<<endl;
   cout<<"6. Dirbti su konstitucija.txt"<<endl;
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
        auto hash = gautiHash(tekstas);
    isvedimas(hash);
    }
   if(rinktis == 2)
    {
        cin.ignore((std::numeric_limits<std::streamsize>::max)(), '\n'); // Išvalome įvesties srautą
        cout << "Įveskite tekstą:" << endl;
        getline(cin, tekstas);
        auto hash = gautiHash(tekstas);
        isvedimas(hash);
    }
    if(rinktis == 3)
    {
        failuKurimas();
        cout << "Failas 'tekstas1000.txt', 'tekstas2000.txt' ir 'tekstas3000.txt' sukurti su atsitiktiniu tekstu." << endl;
    }
    if(rinktis == 4)
    {
        string A = "Labas";
        string B = "Kebabas";
        auto hashA = gautiHash(A);
        auto hashB = gautiHash(B);
        cout << "A =  " <<A<< endl;
        isvedimas(hashA);
        cout << "B =  " <<B<< endl;
        isvedimas(hashB);
        auto hashA2 = gautiHash(A);
        cout << "A = " <<A<< endl;
        isvedimas(hashA2);
    }
    if(rinktis == 5)
    {
        string A = "Labas";
        string B = "Labas";
        auto hashA = gautiHash(A);
        auto hashB = gautiHash(B);
        cout << "A =  " <<A<< endl;
        isvedimas(hashA);
        cout << "B =  " <<B<< endl;
        isvedimas(hashB);
    }
    if(rinktis == 6)
    {
        string failoPavadinimas = "konstitucija.txt";
        if(nuskaitytiIsFailo(failoPavadinimas, tekstas))
        {
            cout << "Tekstas nuskaitytas iš failo. Baitų skaičius: " << tekstas.size() << endl;
        }
        else
        {
            cout << "Nepavyko nuskaityti teksto iš failo." << endl;
            return 1; // Grąžiname klaidos kodą
        }
        int eilutes = eiluciuSkaicius(tekstas);
        cout << "Eilučių skaičius: " << eilutes << endl;
        for(int i = 1; i <= eilutes; i=i*2)
        {
        string istrauka = gautiIstrauka(tekstas, i);
        cout<< "Ištrauka iki " << i << " eilutės: " << endl;
        cout << istrauka.size() << " baitų" << endl;
        
        auto hash = gautiHash(istrauka);
        for(int j = 0; j < 5; j++)
        {
            auto start = std::chrono::high_resolution_clock::now();
            for(int k = 0; k < 1000; k++)
            {
                hash = gautiHash(istrauka);
            }
            auto end = std::chrono::high_resolution_clock::now();
            std::chrono::duration<double, std::milli> elapsed = end - start;
            cout << "Laikas: " << elapsed.count() << " ms" << endl;
        }
        
            isvedimas(hash);
        }
        cout<< " Ištrauka iki " << eilutes << " eilutės: " << endl;
        cout << tekstas.size() << " baitų" << endl;
        auto hash = gautiHash(tekstas);
        for(int j = 0; j < 5; j++)
        {
        auto start = std::chrono::high_resolution_clock::now();
        for(int k = 0; k < 1000; k++)
        {
        hash = gautiHash(tekstas);
        }
        auto end = std::chrono::high_resolution_clock::now();
        std::chrono::duration<double, std::milli> elapsed = end - start;
        cout << "Laikas: " << elapsed.count() << " ms" << endl;
        }
        isvedimas(hash);
    }
    //int baitai = gautiBaitus(tekstas);
    //cout << "Baitų skaičius: " << baitai << endl;
    //cout << std::hex << baitai << endl;
    
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
    cout <<std::dec<< endl;
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
int eiluciuSkaicius(string & tekstas)
{
    int eiluciuSkaicius = 0;

    for (char simbolis : tekstas)
    {
        if (simbolis == '\n')
        {
            eiluciuSkaicius++;
        }
    }

    if (!tekstas.empty() && tekstas.back() != '\n')
    {
        eiluciuSkaicius++;
    }

    
    return eiluciuSkaicius;
}
string gautiIstrauka(string & tekstas, int kiekEiluciu)
{
    int eilutes = 0;

    for (size_t i = 0; i < tekstas.size(); i++)
    {
        if (tekstas[i] == '\n')
        {
            eilutes++;

            if (eilutes == kiekEiluciu)
                return tekstas.substr(0, i + 1);
        }
    }

    return tekstas;
}