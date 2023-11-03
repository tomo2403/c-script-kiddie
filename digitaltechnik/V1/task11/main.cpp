#include <iostream>
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

int main()
{
    B15F &drv = B15F::getInstance();
    int max = 0;
    string letters = "abcdefgh";

    cout << "Anzahl der maximalen Zeilen: ";
    cin >> max;
    cout << "\n\n";

    string output = "";
    for (int i = 0; i < max; i++)
    {
        drv.digitalWrite0(i);
        int input = (int)drv.digitalRead0();

        string bin = toBinary(i);
        while (bin.length() < (log(max) / log(2)))
        {
            bin = bin.insert(0, "0");
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