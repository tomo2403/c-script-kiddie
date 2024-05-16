#include <b15f/b15f.h>

using namespace std;
B15F &drv = B15F::getInstance();

double toVolt(const uint16_t &spannung_Integer)
{
    return spannung_Integer * (5.0 / 1023.0);
}

// rechnet eine Spannung [0-5] in Volt in einen Integer Wert [0-1023]
uint16_t toInt(const double &spannung_Volt)
{
    return round(spannung_Volt * (1023.0 / 5.0));
}

void aufgabe_6_1()
{
    int last = 0;
    int i = 0;
    while (true)
    {
        i = drv.analogRead(7);
        if (last != i)
        {
            drv.analogWrite0(i);
            std::cout << i << endl;
            last = i;
        }
    }
}

int main()
{
    aufgabe_6_1();
}