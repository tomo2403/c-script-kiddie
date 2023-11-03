#include <iostream>
#include <string>
#include <b15f/b15f.h>

using namespace std;

/// @brief Konvertiert eine Zahl von Dezimal in Binär
/// @param n Die natürliche Zahl, die konvertiert werden soll.
/// @return den Binären Wert von `n`
string toBinary(int n)
{
    string r;
    while (n != 0)
    {
        r = (n % 2 == 0 ? "0" : "1") + r;
        n /= 2;
    }
    return r;
}

/// @brief Fordert die Eingabe einer Zahl an und prüft diese auf Kompatiblität
/// @param errorOnLastRun `true`, wenn der letzte Aufruf nicht erfolgreich war.
/// @return Die korrekte Eingabe als Zahl
int inputRequest(bool errorOnLastRun = false)
{
    // Erzeugt eine Fehlermeldung bei unpassender Eingabe
    if (errorOnLastRun)
    {
        cout << "\nDie Eingabe muss eine Ganzzahl sein, welche zur Reihe der 2er-Potenzen gehört und nicht größer als 256 ist." << endl;
        cin.clear();
        cin.ignore(10000, '\n');
    }

    cout << "Anzahl der maximalen Zeilen: ";
    int decimalInput = 0;

    // Eingabe auf Zahl prüfen
    if (!(cin >> decimalInput))
    {
        // Eingabe erneut abfragen
        return inputRequest(true);
    }

    int i = 1;
    // Fehlerhafte Eingabe mit nächst-größerer Zahl korrigieren
    while (decimalInput <= 256 and decimalInput > i)
    {
        i *= 2;
    }

    // Prüft die eingegebene Zahl auf Gültigkeit
    return decimalInput == i ? decimalInput : inputRequest(true);
}

int main()
{
    // Verbindung zum B15-Board aufbauen
    B15F &drv = B15F::getInstance();

    // Die Anzahl der zu testenden Ausgänge abfragen
    int max = inputRequest();
    cout << "\n\n";

    for (int i = 0; i < max; i++)
    {
        // Aktuellen Testausgang konvertieren
        string bin = toBinary(i);

        // Führende Nullen ergänzen
        while (bin.length() < (log(max) / log(2)))
        {
            bin = bin.insert(0, "0");
        }

        // Seperator für die Darstellung einfügen
        int length = bin.length() * 4 - 3;
        for (int j = 0; j < length; j += 4)
        {
            bin.insert(j, " | ");
        }

        // Tabellenkopf erzeugen
        if (i == 0)
        {
            string letters = " | a | b | c | d | e | f | g | h |";
            string header = letters.substr(0, bin.length() * 4 + 2);
            cout << header << "| A |\n"
                 << endl;
        }

        // Ausgang auf Eingang testen
        drv.digitalWrite0(i);
        int input = (int)drv.digitalRead0();

        // Ergebnis ausgeben
        cout << bin << " || " << input << " |" << endl;
    }

    return 0;
}