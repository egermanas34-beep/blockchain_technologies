# blockchain_technologies
## Pradine versija v0.1
### apie funkcija int gautiBaitus(string t)
is pradziu nusprendziau kiekviena ivesto teksto baita paversti jo skaitine reiksme. Gautas reiksmes sudedu ir saugau kintamajame visiBaitai.
Taciau pastebejau, kad paprasciausiai sudedant baitu reiksmes ivyksta kolizija tarp skirtingu ivescių, pavyzdziui, „ab“ ir „ba“. Siekdamas to isvengti, nusprendziau kiekvieno baito reiksme padauginti is jo pozicijos tekste: pirmaji is 1, antraji is 2 ir t. t.
Atlikes pirmuosius bandymus pastebejau, kad sis pakeitimas neissprendzia visu koliziju problemos. Pavyzdziui, skirtingos ivestys „ac“ ir „cb“ vis tiek duoda vienoda rezultata. Todal algoritma reikia toliau tobulinti.