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

// rechnet einen Integer Wert [0-1023] in eine Spannung [0-5] in Volt um
double toVolt(const uint16_t &spannung_Integer)
{
    return spannung_Integer * (5.0/1023.0);
}

// rechnet eine Spannung [0-5] in Volt in einen Integer Wert [0-1023]
uint16_t toInt(const double &spannung_Volt)
{
    return round(spannung_Volt * (1023.0/5.0));
}

void druckeKennlinie(const std::vector<std::pair<double, double>> &kennlinie, const std::string &dateipfad)
{
    std::ofstream datei(dateipfad);

    if (!datei.is_open())
	{
		std::cerr << "Fehler: Datei konnte nicht geöffnet werden." << std::endl;
	}

    // for-Schleife schneidet letzten Wert ab
    for(uint16_t i = 0; i < kennlinie.size()-1; i++)
    {
        double wert1 = kennlinie.at(i).first;
        double wert2 = kennlinie.at(i).second;
        datei << std::fixed << std::setprecision(10) << wert1 << "," << wert2 << std::endl;
    }

    datei.close();
}

void aufgabe_8_4()
{
    // Setzen der abzuarbeitenden Gate-Spannungen
    std::vector<double> spannungenGateSource_Volt {0.0, 1.0, 2.0, 2.5, 3.0, 4.0, 5.0};
    
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

// ACHTUNG: Ausgänge AA0 und AA1 müssen vertauschst werden!
void aufgabe_8_6()
{
    // Setzen der abzuarbeitenden Betiebsspannungen
    std::vector<double> betriebsspannungen_Volt {2.0, 3.0, 4.0, 5.0};
    
    for(double const& betriebsspannung_Volt : betriebsspannungen_Volt)
    {
        // Setzten der Betriebsspannung
        drv.analogWrite1(toInt(betriebsspannung_Volt));

        // Ermitteln der Messerte
        std::array<uint16_t, 1024> buffer_AE1, buffer_AE2;
        drv.analogSequence(1, buffer_AE1.data(), 0, 2, buffer_AE2.data(), 0, 0, 1, 1023);

        // Berechnen der Stromstärke ID
        uint8_t R1_Ohm = 100;
        std::vector<std::pair<double, double>> verstaerkungsKennlinie;
        for(uint16_t i = 0; i < buffer_AE1.size(); i++)
        {
            double spannungGateSource_Volt = toVolt(buffer_AE2.at(i));
            double spannungR1_Volt = betriebsspannung_Volt - toVolt(buffer_AE1.at(i));
            double stromDrain_Ampere = spannungR1_Volt / R1_Ohm;
            
            verstaerkungsKennlinie.push_back({spannungGateSource_Volt, stromDrain_Ampere});
        }

        // Ausgeben der Messwerte
        std::string orderpfad = "./aufgabe_8_6/";
        std::string dateiname = "Verstaerkungskennlinie_ID_von_UGS_bei_UDS_von_" + std::to_string(betriebsspannung_Volt) + "V.csv";
        std::string dateipfad = orderpfad + dateiname;
        druckeKennlinie(verstaerkungsKennlinie, dateipfad);
    }
}

void aufgabe_8_8()
{
    while(true)
    {
        // std::cout << "High" << std::endl;
        drv.analogWrite1(1023);
        // drv.delay_ms(1000);
        // std::cout << "Low" << std::endl;
        drv.analogWrite1(0);
    }
}

void aufgabe_8_11()
{
    // Setzen der abzuarbeitenden Basisspannungen
    std::vector<double> spannungenBasis_Volt {0.0, 1.0, 2.0, 2.5, 3.0, 4.0, 5.0};
    
    for(double const& spannungBasis_Volt : spannungenBasis_Volt)
    {
        // Setzten der Betriebsspannung
        drv.analogWrite1(toInt(spannungBasis_Volt));

        // Ermitteln der Messerte
        std::array<uint16_t, 1024> buffer_AE1, buffer_AE2;
        drv.analogSequence(1, buffer_AE1.data(), 0, 2, buffer_AE2.data(), 0, 0, 1, 1023);

        // Berechnen der Stromstärken ID und IC
        uint8_t R1_Ohm = 100;
        uint16_t R2_Ohm = 1000;
        std::vector<std::pair<double, double>> kennlinie;
        for(uint16_t i = 0; i < buffer_AE1.size(); i++)
        {
            double betriebsspannung_Volt = toVolt(i);
            double stromstaerkeCollector_Ampere = static_cast<double>(betriebsspannung_Volt - toVolt(buffer_AE1.at(i))) / R1_Ohm;
            double spannungCollectorEmitter_Volt = toVolt(buffer_AE1.at(i));
            kennlinie.push_back({spannungCollectorEmitter_Volt, stromstaerkeCollector_Ampere});
        }

        // Ausgeben der Messwerte
        std::string orderpfad = "./aufgabe_8_11/";
        std::string dateiname = "Kennlinie_IC_von_IB_bei_UB_von_" + std::to_string(spannungBasis_Volt) + "V.csv";
        std::string dateipfad = orderpfad + dateiname;
        druckeKennlinie(kennlinie, dateipfad);
    }
}

// ACHTUNG: Ausgänge AA0 und AA1 müssen vertauschst werden!
void aufgabe_8_12()
{
    // Setzen der abzuarbeitenden Basisspannungen
    std::vector<double> betriebsspannung_Volt {2.0, 3.0, 4.0, 5.0};
    
    for(double const& betriebsspannung_Volt : betriebsspannung_Volt)
    {
        // Setzten der Betriebsspannung
        drv.analogWrite1(toInt(betriebsspannung_Volt));

        // Ermitteln der Messerte
        std::array<uint16_t, 1024> buffer_AE1, buffer_AE2;
        drv.analogSequence(1, buffer_AE1.data(), 0, 2, buffer_AE2.data(), 0, 0, 1, 1023);

        // Berechnen der Stromstärken ID und IC
        uint8_t R1_Ohm = 100;
        uint16_t R2_Ohm = 1000;
        std::vector<std::pair<double, double>> kennlinie;
        for(uint16_t i = 0; i < buffer_AE1.size(); i++)
        {
            double spannungBasis_Volt = toVolt(i);
            double stromstaerkeCollector_Ampere = static_cast<double>(betriebsspannung_Volt - toVolt(buffer_AE1.at(i))) / R1_Ohm;
            double stromstaerkeBasis_Ampere = static_cast<double>(spannungBasis_Volt - toVolt(buffer_AE2.at(i))) / R2_Ohm;
            
            double spannungCollectorEmitter_Volt = toVolt(buffer_AE1.at(i));
            kennlinie.push_back({stromstaerkeBasis_Ampere, stromstaerkeCollector_Ampere});
        }

        // Ausgeben der Messwerte
        std::string orderpfad = "./aufgabe_8_12/";
        std::string dateiname = "Kennlinie_IC_von_IB_bei_UB_von_" + std::to_string(betriebsspannung_Volt) + "V.csv";
        std::string dateipfad = orderpfad + dateiname;
        druckeKennlinie(kennlinie, dateipfad);
    }
}

int main()
{
    aufgabe_8_8();
}