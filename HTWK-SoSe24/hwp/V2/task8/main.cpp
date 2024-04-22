#include <b15f/b15f.h>
#include <string>
#include <array>
#include <iostream>
#include <fstream>
#include <cstdint>
#include <cmath>
#include <vector>
#include <iomanip>

B15F &drv = B15F::getInstance();

enum analogeEingaenge {AE0, AE1, AE2, AE3};

double intZuVolt(const uint16_t &spannung_Integer)
{
    return spannung_Integer * (5.0/1023.0);
}

uint16_t voltZuInt(const double &spannung_Volt)
{
    return round(spannung_Volt * (1023.0/5.0));
}

std::array<uint16_t, 4> messen()
{
    std::array<uint16_t, 4> messwerte_Integer;
    for (uint8_t i = 0; i < 4; i++)
    {
        messwerte_Integer.at(i) = drv.analogRead(i);
    }
    return messwerte_Integer;
}

// zu Aufgabe 8.4
std::vector<std::pair<double, double>> plotte_stromDrain_von_spannungSourceDrain(const double &spannungGateSource_Volt)
{
    // Vektor mit Paaren aus spannungSourceDrain und stromDrain mit stromDrain(spannungSourceDrain) => Kennlinie
    std::vector<std::pair<double, double>> kennlinie;

    drv.analogWrite1(spannungGateSource_Volt);

    for(uint16_t i = 0; i < 1024; i += 2)
    {
        drv.analogWrite0(i);
        std::array<uint16_t, 4> messewerte_Integer = messen();

        // Berechnung der Stromstärke ID
        uint8_t R1_Ohm = 56;
        double spannungR1_Volt = intZuVolt(messewerte_Integer.at(AE0) - messewerte_Integer.at(AE1));
        double stromDrain_Ampere =  spannungR1_Volt / R1_Ohm;

        // Berechnung der Spannung USD
        double spannungSourceDrain_Volt = intZuVolt(messewerte_Integer.at(AE1));

        kennlinie.push_back({spannungSourceDrain_Volt, stromDrain_Ampere});
    }

    return kennlinie;
}

void druckeKennlinie(const std::vector<std::pair<double, double>> &kennlinie, const std::string &dateipfad)
{
    std::ofstream datei(dateipfad);

    if (!datei.is_open())
	{
		std::cerr << "Konnte die Datei nicht öffnen" << std::endl;
	}

    for(auto &[wert1, wert2] : kennlinie)
    {
        datei << std::fixed << std::setprecision(20) << wert1 << ";" << wert2 << std::endl;
    }

    datei.close();
}

void aufgabe_8_4()
{
    std::array<double, 7> spannungenGateSource_Volt {0, 1, 5};
    
    for(double spannung_Volt : spannungenGateSource_Volt)
    {
        std::vector<std::pair<double, double>> kennlinie = plotte_stromDrain_von_spannungSourceDrain(spannung_Volt);

        std::string dateipfad = "./aufgabe_8_4/Kennlinie_ID_von_USD_bei_UGS_von_" + std::to_string(spannung_Volt) + "V.csv";
        druckeKennlinie(kennlinie, dateipfad);
    }

    std::cout << "Aufgabe 8.4 abgeschlossen" << std::endl;
}

int main()
{
    aufgabe_8_4();
}