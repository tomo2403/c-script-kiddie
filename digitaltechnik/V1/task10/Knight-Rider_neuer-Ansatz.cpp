#include <iostream>
#include <chrono>
#include <thread>
using namespace std;

void print(unsigned int output)
{
   cout << output << endl; //muss mit B15 output ersetzt werden
}

int main()
{
    bool richtung{true}; // true: nach links (größer werdend), false: nach rechts (kleiner werdend)
    unsigned int output{1};
    print(output);

    for (int i = 1; i <= 40; i++) // Anzahl der Durchläufe begrenzt, sonst while(true)
    {

        this_thread::sleep_for(chrono::milliseconds(150)); //muss mit B15 sleep ersetzt werden ersetzt werden

        if (richtung and output < 128)
        {
            output *= 2;
            print(output);
        }
        else if (!richtung and output > 1)
        {
            output /= 2;
            print(output);
        }
        else
        {
            richtung = !richtung;
        }

    }
}