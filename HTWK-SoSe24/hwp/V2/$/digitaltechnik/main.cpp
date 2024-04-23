#include <b15f/b15f.h>
#include <string>
#include <array>
#include <iostream>
#include <fstream>
#include <cstdint>
#include <cmath>
#include <vector>
#include <iomanip>
#include <vector>

B15F &drv = B15F::getInstance();

enum analogeEingaenge {AE0, AE1, AE2, AE3};

// rechnet einen Integer Wert [0-1023] in eine Spannung in Volt um
double toVolt(const uint16_t &spannung_Integer)
{
    return spannung_Integer * (5.0/1023.0);
}

// rechnet eine Spannung in Volt in einen Integer Wert [0-1023]
uint16_t toInt(const double &spannung_Volt)
{
    return round(spannung_Volt * (1023.0/5.0));
}

void druckeKennlinie(const std::vector<std::pair<double, double>> &kennlinie, const std::string &dateipfad)
{
    std::ofstream datei(dateipfad);

    if (!datei.is_open())
	{
		std::cerr << "Ich konnte die Datei nicht öffnen, entschuldigung :(." << std::endl;
	}

    for(auto &[wert1, wert2] : kennlinie)
    {
        datei << std::fixed << std::setprecision(10) << wert1 << "," << wert2 << std::endl;
    }

    datei.close();
}

void aufgabe_8_4()
{
    // setzen der abzuarbeitenden Gate-Spannungen
    std::vector<double> spannungenGateSource_Volt {0, 1, 2, 2.5, 3, 4, 5};
    
    for(double const& spannungGateSource_Volt : spannungenGateSource_Volt)
    {
        // Setzten der Gatespannung
        drv.analogWrite1(toInt(spannungGateSource_Volt));

        // Ermitteln der Messerte
        std::array<uint16_t, 1024> buffer_AE0, buffer_AE1;
        drv.analogSequence(0, buffer_AE0.data(), 0, 1, buffer_AE1.data(), 0, 0, 1, 1023);

        // Berechnen der Stromstärke ID
        uint8_t R1_Ohm = 100;
        std::vector<std::pair<double, double>> kennlinie;
        for(uint16_t i = 0; i < buffer_AE0.size(); i++)
        {
            double spannungSourceDrain_Volt = toVolt(buffer_AE1.at(i));
            double spannungR1_Volt = toVolt(buffer_AE0.at(i) - buffer_AE1.at(i));
            double stromDrain_Ampere = spannungR1_Volt / R1_Ohm;
            
            kennlinie.push_back({spannungSourceDrain_Volt, stromDrain_Ampere});
        }

        // Ausgeben der Messwerte
        std::string orderpfad = "./aufgabe_8_4/";
        std::string dateiname = "Kennlinie_ID_von_USD_bei_UGS_von_" + std::to_string(spannungGateSource_Volt) + "V.csv";
        std::string dateipfad = orderpfad + dateiname;
        druckeKennlinie(kennlinie, dateipfad);
    }
}

int main()
{
    aufgabe_8_4();
}