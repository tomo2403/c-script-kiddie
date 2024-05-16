#include <b15f/b15f.h>

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
  while (false)
  {
    drv.analogWrite0(drv.analogRead(0));
  }
}

int main()
{
  aufgabe_6_1();
}