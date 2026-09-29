# blockchain_technologies
## Pradine versija v0.1
### apie funkcija int gautiBaitus(string t)
Iš pradžių nusprendžiau kiekvieną įvesto teksto baitą paversti jo skaitine reikšme. Gautas reikšmes sudedu ir saugau kintamajame visiBaitai.
Tačiau pastebėjau, kad paprasčiausiai sudedant baitų reikšmes įvyksta kolizija tarp skirtingų įvesčių, pavyzdžiui, „ab“ ir „ba“. Siekdamas to išvengti, nusprendžiau kiekvieno baito reikšmę padauginti iš jo pozicijos tekste: pirmąjį iš 1, antrąjį iš 2 ir t. t.
Atlikęs pirmuosius bandymus pastebėjau, kad šis pakeitimas neišsprendžia visų kolizijų problemos. Pavyzdžiui, skirtingos įvestys „ac“ ir „cb“ vis tiek duoda vienodą rezultatą. Todėl algoritmą reikia toliau tobulinti.
### apie funkcija std::array<uint32_t, 8> gautiHash(string t)
Pradinis šios funkcijos veikimo principas panašus į ankstesnės funkcijos: kiekvieno įvesties baito skaitinė reikšmė dauginama iš jo pozicijos. Tačiau šį kartą gauti rezultatai paskirstomi į aštuonis 32 bitų masyvo elementus. Tai leidžia išvengti anksčiau pastebėtos kolizijos tarp „ac“ ir „cb“, tačiau negarantuoja, kad kolizijų nebus tarp kitų įvesčių.
Siekdamas toliau patobulinti algoritmą, nusprendžiau prie kiekvieno maišos elemento pridėti ankstesnio elemento reikšmę. Tokiu būdu kiekvienas naujas elementas priklauso ne tik nuo dabartinio įvesties baito, bet ir nuo ankstesnių skaičiavimų rezultatų. Šiuo pakeitimu siekiu geriau susieti maišos elementus ir sumažinti lengvai aptinkamų kolizijų skaičių.
## Versija v0.11
### Pradiniai pakeitimai
Patobulinau koda, kad galima butu nuskaityti tekstinius failus, o ne tik ivesti teksta ranka. 
### 1 eksperimentas
Sukuriau tuščią failą ir failus, turinčius tiksliai vieną baitą, a ir b, be naujos eilutės simbolio. Tris ASCII turinio failai 1000, 2000 ir 3000 baitų ilgio. Šių failų kopijas, kuriose pakeistas tiksliai vienas baitas pradžioje - padaryta su 1000 ilgio failu, viduryje - su 2000, pabaigoje - su 3000 ilgio failu. Keli struktūruoti atvejai: pasikartojančių simbolių failas pasikartojantys.txt, pakeista simbolių tvarka failuose ab.txt ir ba.txt, tarpai pradžioje tarpas_pradzioje.txt / pabaigoje tarpas_pabaigoje.txt ir tas
pats tekstas su naujos eilutės simboliu nauja_eilute.txt bei be jo be_eilutes.
Bent vienas UTF-8 pavyzdys su ne ASCII simboliais faile utf8.txt. 
Patikrinimai po šio eksperimento buvo šie:
Nuskaičius tuščią failą, ekrane matome išvesta - 0000000000000000000000000000000000000000000000000000000000000000. 
Nuskaičius failus po vieną baitą - 
a.txt - 0000006100000000000000000000000000000000000000000000000000000000,
b.txt - 0000006200000000000000000000000000000000000000000000000000000000, kadangi a ir b skiriasi vienetu ascii koduotėje, todėl ir hash jų skirtumas yra tik viename simbolyje.
Failo su 1000 ir pakeisto pradinio simbolio su 1000 hash formatai - 
004d99920c98cfe792ea6310c83d6e67846a7afefc544eb87107f8f9b327389d,
004d997b0c98c4ac92e79f8bc7c86ebe75ca85de8302341881bfb8191095e83d.
Failo su 2000 ir pakeisto viduje simbolio su 2000 hash formatai - 
013163b7663026f925af072bf64b9feb77e2781cecafa4b3c39eec1652aabe78, 
013163b76630779525d8e8370141860f651bec706e5117dba3803f5e6fe939f0.
Failo su 3000 ir pakeisto gale simbolio su 3000 hash formatai - 
02c0b2ac5296c4d0770a1773dc2ce08977a19c8b05f5226ed42aedf7c64aafcf, 
02c0b2ac5296c4d0770a1773dc2ce08977a19c8b05f5226ed42aedf7c64cbf27.
Failas su pasikartojančiais simboliais gauna reikšmę - 
000003ca000008b700000246000003ca000005af000007f500000a9c00000da4.
Failai, kuriuose simboliai sukeisti vietomis ab ir ba - 
ab - 0000006100000125000000000000000000000000000000000000000000000000, 
ba - 0000006200000124000000000000000000000000000000000000000000000000. 
Su tarpais pradzioje ir pabaigoje -
 pradzioje - 00000020000000b8000001db0000036300000548000007fa0000000000000000, 
pabaigoje - 0000004c0000010e00000234000003b8000005f7000006b70000000000000000.
Tas pats tekstas su nauja eilute po jo - 
0000004c0000010e00000234000003b8000005f7000006450000068b00000000,
be naujos eilutės - 0000004c0000010e00000234000003b8000005f7000000000000000000000000.
Tekstas su lietuviškomis raidemis - Ąžuolas - simbilių skaičius jame yra 7, o baitu išvedama 9, 
000004cf000001cc0000041b000007130000095c00000bf600000eea000011f2.
### Eksperimento išvados
Atlikus pirmąjį eksperimentą nustatyta, kad programa geba apskaičiuoti maišas tuščiam failui, vieno baito failams, skirtingo dydžio ASCII failams ir UTF-8 tekstui su lietuviškomis raidėmis. Tuščio failo maišą sudaro vien nuliai. Vieno baito failų a.txt ir b.txt maišos skiriasi tik vienu šešioliktainiu skaitmeniu, arba dviem bitais.
Pakeitus vieną baitą didesniuose failuose, gautos skirtingos maišos, tačiau pastebėta, kad pakeitimas failo pabaigoje paveikia tik dalį maišos. Tai rodo, kad dabartinėje algoritmo versijoje įvesties pakeitimai nepakankamai pasklinda po visą 256 bitų išvestį.
Struktūruotų įvesčių bandymai parodė, kad simbolių tvarkos pakeitimas, tarpo pozicija ir papildomi naujos eilutės baitai gali pakeisti gaunamą maišą. UTF-8 bandyme tekstą Ąžuolas sudarė 7 simboliai ir 9 baitai, todėl patvirtinta, kad baitų skaičius nebūtinai sutampa su simbolių skaičiumi.

## Versija v0.12
### 2 eksperimentas
Atlikus testus su praeitame eksperimente sukurtais failais gauname tokias jų hex ir maišos ilgių reikšmes:
| Įvestis                      | Maiša(HEX)                                                     | Maišos ilgis |
|------------------------------|------------------------------------------------------------------|--------------|
| Tuščia                       | 0000000000000000000000000000000000000000000000000000000000000000 | 64           |
| Vienas baitas a              | 0000006100000000000000000000000000000000000000000000000000000000 | 64           |
| Vienas baitas b              | 0000006200000000000000000000000000000000000000000000000000000000 | 64           |
| 1000 ilgis                   | 004d99920c98cfe792ea6310c83d6e67846a7afefc544eb87107f8f9b327389d | 64           |
| 1000 ilgis su pirmu pakeistu | 004d997b0c98c4ac92e79f8bc7c86ebe75ca85de8302341881bfb8191095e83d | 64           |
| 2000 ilgis                   | 013163b7663026f925af072bf64b9feb77e2781cecafa4b3c39eec1652aabe78 | 64           |
| pakeistas viduje             | 013163b76630779525d8e8370141860f651bec706e5117dba3803f5e6fe939f0 | 64           |
| 3000 ilgis                   | 02c0b2ac5296c4d0770a1773dc2ce08977a19c8b05f5226ed42aedf7c64aafcf | 64           |
| pakeistas paskutinis         | 02c0b2ac5296c4d0770a1773dc2ce08977a19c8b05f5226ed42aedf7c64cbf27 | 64           |
| pasikartojantys a            | 000003ca000008b700000246000003ca000005af000007f500000a9c00000da4 | 64           |
| ab                           | 0000006100000125000000000000000000000000000000000000000000000000 | 64           |
| ba                           | 0000006200000124000000000000000000000000000000000000000000000000 | 64           |
| tarpas pradžioje             | 00000020000000b8000001db0000036300000548000007fa0000000000000000 | 64           |
| tarpas pabaigoje             | 0000004c0000010e00000234000003b8000005f7000006b70000000000000000 | 64           |
| tekstas su eilute po juo     | 0000004c0000010e00000234000003b8000005f7000006450000068b00000000 | 64           |
| be naujos eilutės            | 0000004c0000010e00000234000003b8000005f7000000000000000000000000 | 64           |
| Ąžuolas                      | 000004cf000001cc0000041b000007130000095c00000bf600000eea000011f2 | 64           |
| Labas - ranka                | 0000004c0000010e00000234000003b8000005f7000000000000000000000000 | 64           |
| Labas - nuskaitant           | 0000004c0000010e00000234000003b8000005f7000000000000000000000000 | 64           |

#### Išvados
Atlikus testus matome, kad su bet kokio ilgio ir formato įvestimi gaunama fiksuoto 256 bitų ilgio maiša. Kadangi vienas HEX simbolis atitinka 4 bitus, 256 bitų maiša yra atvaizduojama 64 HEX simboliais. Visuose atliktuose testuose maišos ilgis buvo 64 simboliai, o pradiniai nuliai buvo išsaugomi.
Taip pat patikrinta, kad įvedus tą patį tekstą Labas rankiniu būdu ir nuskaičius tokį patį tekstą iš failo, kai sutampa įvesties baitai, gaunama identiška maišos reikšmė. Tai parodo, kad maišos rezultatas nepriklauso nuo įvesties būdo.