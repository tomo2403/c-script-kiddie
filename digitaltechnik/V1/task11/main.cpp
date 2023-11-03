#include <iostream>
#include <string>
#include <b15f/b15f.h>

using namespace std;

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

int inputRequest()
{
    cout << "Anzahl der maximalen Zeilen: ";

    int decimalInput = 0;
    if (!(cin >> decimalInput)) // schaut, ob Eingabe eine Zahl ist
    {
        cout << "\nDie Eingabe muss eine Ganzzahl sein, welche zur Reihe der 2er-Potenzen gehört und nicht größer als 256 ist." << endl;
        cin.clear();
        cin.ignore(123, '\n');
        return inputRequest();
    }

    int i = 1;
    while (decimalInput <= 256 and decimalInput > i) // findet nächstgrößere korrekte Nummer zur Eingabe
    {
        i *= 2;
    }

    if (decimalInput == i) // Schaut ob die Eingabe gültig ist
    {
        return decimalInput;
    }
    else
    {
        cout << "\nDie Eingabe muss eine Ganzzahl sein, welche zur Reihe der 2er-Potenzen gehört und nicht größer als 256 ist." << endl;
        return inputRequest();
    }
}

int main()
{
    B15F &drv = B15F::getInstance();
    int max = 0;

    max = inputRequest();
    cout << "\n\n";

    bool headerOut = true;
    for (int i = 0; i < max; i++)
    {
        drv.digitalWrite0(i);
        int input = (int)drv.digitalRead0();

        string bin = toBinary(i);

        while (bin.length() < (log(max) / log(2)))
        {
            bin = bin.insert(0, "0");
        }

        if (headerOut)
        {
            string letters = " | a | b | c | d | e | f | g | h |";
            string header = letters.substr(0, bin.length() * 4 + 2);
            cout << header << "| A |\n" << endl;

            headerOut = false;
        }

        int length = bin.length() * 4 - 3;
        for (int j = 0; j < length; j += 4)
        {
            bin.insert(j, " | ");
        }

        cout << bin << " || " << input << " |" << endl;
    }

    return 0;
}