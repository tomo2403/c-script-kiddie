#include <iostream>
using namespace std;

int inputRequest()
{
    cout << "Max. Byte: ";

    int decimalInput = 0;
    if(!(cin >> decimalInput)) //checks if input is numeric
    {
        cout << "Die Eingabe muss eine Ganzzahl sein, welche zur Reihe der 2er-Potenzen gehört und nicht größer als 256 ist." << endl;
        cin.clear();
        cin.ignore(123, '\n');
        return inputRequest();
    }

    int i = 1;
    while (decimalInput <= 256 and decimalInput > i) //finds valid number, closest to the number inputted
    {
        i *= 2;
    }

    if (decimalInput == i) //checks if inputted number is valid
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