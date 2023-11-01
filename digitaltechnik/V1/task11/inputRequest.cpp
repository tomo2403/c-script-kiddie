#include <iostream>
using namespace std;

int inputRequest()
{
    cout << "Max. Byte: ";

    int decimalInput = 0;
    if (!(cin >> decimalInput)) // schaut, ob Eingabe eine Zahl ist
    {
        cout << "Die Eingabe muss eine Ganzzahl sein, welche zur Reihe der 2er-Potenzen gehört und nicht größer als 256 ist." << endl;
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
        cout << "Die Eingabe muss eine Ganzzahl sein, welche zur Reihe der 2er-Potenzen gehört und nicht größer als 256 ist." << endl;
        return inputRequest();
    }
}

int main()
{
    cout << inputRequest() << endl;
}