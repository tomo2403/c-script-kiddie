#include <b15f/b15f.h>
#include <string>
#include <array>
#include <iostream>

B15F &drv = B15F::getInstance();

std::array<double, 4> messen()
{
    double umrechnungsfaktorIntegerZuVolt = 5.0/1024.0;
    std::array<double, 4> messwerte_Volt;
    for(int i = 0; i < 4; i++)
    {
        messwerte_Volt.at(i) = drv.analogRead(i) * umrechnungsfaktorIntegerZuVolt;
    }
    return messwerte_Volt;
}

int main()
{
    std::cout << "Gate-Spannung: ";
    double gateSpannung_Volt = 0;
    std::cin >> gateSpannung_Volt;
    
    double umrechnungsfaktorVoltZuInteger = 1024.0/5.0;
    double gateSpannung_Integer = umrechnungsfaktorVoltZuInteger * gateSpannung_Volt;

    drv.analogWrite1(gateSpannung_Integer);

    for(uint16_t i = 0; i < 1024; i += 2)
    {
        drv.analogWrite0(i);
        std::array<double, 4> messwerte_Volt = messen();

        double widerstandEins_ohm = 56.0;
        double stromstaerke = messwerte_Volt.at(0) / widerstandEins_ohm;

        std::cout << stromstaerke << std::endl;
    }
}