#include <b15f/b15f.h>

// Verbindung zum B15-Board aufbauen
B15F &drv = B15F::getInstance();

void messen(std::string name)
{
    std::ofstream file(name + "_result_diode.csv");

    if (!file.is_open())
    {
        std::cerr << "Konnte die Datei nicht öffnen";
        return;
    }

    std::array<uint16_t, 1024> bufferA, bufferB;
    drv.analogSequence(0, bufferA.data(), 0, 1, bufferB.data(), 0, 0, 1, 1023);
    for (uint16_t i = 0; i < bufferA.size(); i += 2)
    {
        uint16_t messwert = bufferA.at(i);

        float betriebsspannungVolt = i / 204.8;
        float messwertVolt = messwert / 204.8;
        float stromstaerkeMilliAmpere = betriebsspannungVolt;
        float spannungDiodeVolt = betriebsspannungVolt - messwertVolt;

        // betriebsspannung;spannugnÜberR2;Stromstärke;SpannugDiode
        file << betriebsspannungVolt << "," << messwertVolt << "," << stromstaerkeMilliAmpere << ","
             << spannungDiodeVolt << std::endl;
    }
    drv.analogWrite0(0);
    file.close();
}

int main()
{
    std::string name;
    std::getline(std::cin, name);
    messen(name);
    std::cout << "Flussrichtung gemessen" << std::endl;
    std::string temp;
    std::getline(std::cin, temp);
    messen(name + "_sperr");
    std::cout << "Sperrrichtung gemessen" << std::endl;
    return 0;
}