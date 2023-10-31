#include <iostream>
using namespace std;

int inputRequest()
{
    int decimalInput = 0;
    cout << "Max. Byte: ";
    cin >> decimalInput;

    int i = 1;
    while (decimalInput <= 256 and decimalInput > i)
    {
        i *= 2;
    }

    if (decimalInput == i)
    {
        return decimalInput;
    }
    else
    {
        cout << "Eingabe ungültig. Bitte erneut versuchen." << endl;
        return inputRequest();
    }
}

int main()
{
    cout << inputRequest() << endl;
}