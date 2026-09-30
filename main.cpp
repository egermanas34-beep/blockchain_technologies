#include <iostream>
#include <iomanip>
#include <string>
#include <fstream>
#include <array>
#include <cstdint>
#include <random>
#include <limits>
#include <chrono>
#include <sstream>
#include <unordered_map>
#include <windows.h>
using std::string;
using std::cin;
using std::getline;
using std::ifstream;
using std::cout;
using std::endl;
using std::ofstream;

const string abecele = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789";

int gautiBaitus(string t);
std::array<uint32_t, 8> gautiHash(string t);
bool nuskaitytiIsFailo(string failoPavadinimas, string& tekstas);
void isvedimas(std::array<uint32_t, 8> hash);
void failuKurimas();
int eiluciuSkaicius(string & tekstas);
string gautiIstrauka(string & tekstas, int kiekEiluciu);
string generuotiASCII(int ilgis, std::mt19937& generatorius);
string hashIString(std::array<uint32_t, 8>& hash);
string pakeistiSimboli(string &tekstas, std::mt19937& generatorius);

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
   cout<<"7. Tikrinti kolizija su atsitiktiniu tekstu poromis"<<endl;
   cout<<"8. Tikrinti kolizija su atsitiktiniu tekstu globaliai"<<endl;
   cout<<"9. Tikrinti kolizija strukturuotu tekstu"<<endl;
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
    if(rinktis == 7)
    {
        cout<< "Tikriname kolizijas su atsitiktiniu tekstu..." << endl;
        const int poruSkaicius = 100000;
        int kolizijuSkaicius = 0;
        const int ilgis = 1000;
        for(int i = 0; i < poruSkaicius; i++)
        { 
            std::mt19937 generatorius(12345);
            string A = generuotiASCII(ilgis, generatorius);
            string B = generuotiASCII(ilgis, generatorius);

            while(A == B) // Užtikriname, kad A ir B būtų skirtingi
            {
                B = generuotiASCII(ilgis, generatorius);
            }
            auto hashA = gautiHash(A);
            auto hashB = gautiHash(B);
            if(hashA == hashB)
            {
                kolizijuSkaicius++;
            }
        }
        cout << "Iš " << poruSkaicius << " porų, kolizijų skaičius: " << kolizijuSkaicius << endl;
    }
    if(rinktis == 8)
    {
        cout<< "Tikriname kolizijas su atsitiktiniu tekstu globaliai..." << endl;
        const int poruSkaicius = 100000;
        int kolizijuSkaicius = 0;
        const int ilgis = 1000;
        std::mt19937 generatorius(12345);
        std::unordered_map<string, string> matytiHash; // Naudojame unordered_map, kad saugotume hash reikšmes
        for(int i = 0; i < poruSkaicius; i++)
        { 
            string A = generuotiASCII(ilgis, generatorius);
            string B = generuotiASCII(ilgis, generatorius);
            while(A == B) // Užtikriname, kad A ir B būtų skirtingi
            {
                B = generuotiASCII(ilgis, generatorius);
            }
            string tekstai[2] = {A, B}; // Sukuriame masyvą su dviem tekstais

            for (const string& tekstas : tekstai) // Iteruojame per abu tekstus
            {
                auto hash = gautiHash(tekstas);
                string hashTekstas = hashIString(hash);// Konvertuojame hash į string

                // Ieškome hash reikšmės masyve
                auto rastas = matytiHash.find(hashTekstas);

                if (rastas != matytiHash.end()) // Jei rastas, tai reiškia, kad jau turime tą hash reikšmę
                {
                    if (rastas->second != tekstas) // Patikriname, ar tekstai skiriasi
                    {
                        kolizijuSkaicius++;

                        cout << "Rasta kolizija!" << endl;
                        cout << "1: " << rastas->second << endl;
                        cout << "2: " << tekstas << endl;
                        cout << "Hash: " << hashTekstas << endl;
                    }
                }
                else
                {
                    matytiHash[hashTekstas] = tekstas;
                }
            }
        }
        
        
        
        
        cout << "Iš " << poruSkaicius << " porų, kolizijų skaičius: " << kolizijuSkaicius << endl;
    }
    if(rinktis == 9)
    { 
        string A1 = "abcdefghij";
        string B1 = "jihgfedcba";

        string A2 = "ababababab";
        string B2 = "bababababa";

        string A3 = "aaaaaaaaaa";
        string B3 = "bbbbbbbbbb";
        string tekstai[6] = {A1, B1, A2, B2, A3, B3};
        for (int i = 0; i < 6; i++)
        {
            auto hash = gautiHash(tekstai[i]);
            cout << "Tekstas: " << tekstai[i] << endl;
            isvedimas(hash);
        }
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
string generuotiASCII(int ilgis, std::mt19937& generatorius)
{
    // Naudojame fiksuotą seed, kad rezultatai būtų atkuriami
    std::uniform_int_distribution<int> dist(0, abecele.length() - 1); // ASCII simbolių diapazonas
    string tekstas;
    for (int i = 0; i < ilgis; i++)
    {
        tekstas += abecele[dist(generatorius)];
    }
    return tekstas;
}
string hashIString(std::array<uint32_t, 8>& hash)
{
    std::ostringstream oss;
    for (const auto& h : hash) {
        oss << std::hex << std::setw(8) << std::setfill('0') << h;
    }
    return oss.str();
}
string pakeistiSimboli(string &tekstas, std::mt19937& generatorius)
{
    string pakeistas = tekstas; 
    std::uniform_int_distribution<int> dist(0, tekstas.length() - 1); // Atsitiktinė pozicija tekste    
    std::uniform_int_distribution<int> simboliuDist(0, abecele.length() - 1); // Atsitiktinis simbolis iš abėcėlės
    
    int pozicija = dist(generatorius);// Atsitiktinė pozicija tekste
    char naujasSimbolis = abecele[simboliuDist(generatorius)];// Atsitiktinis simbolis iš abėcėlės
    while(pakeistas[pozicija] == naujasSimbolis) // Užtikriname, kad simboliai nesutaptų
    {
        naujasSimbolis = abecele[simboliuDist(generatorius)];
    }
    pakeistas[pozicija] = naujasSimbolis;
    return pakeistas;
}
