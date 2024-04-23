#include <b15f/b15f.h>
#include <string>

int main()
{
    // Verbindung zum B15-Board aufbauen
    B15F &drv = B15F::getInstance();

    std::ofstream file("result_diode_blue_sperr.csv");

	if (!file.is_open())
	{
		std::cerr << "Konnte die Datei nicht öffnen";
		return 1;
	}

    for(uint16_t i = 0; i < 1024; i += 2)
    {
        drv.analogWrite0(i);
        uint16_t messwert = drv.analogRead(0);

        float betriebsspannungVolt = i/204.8;
        float messwertVolt = messwert/204.8;
        float stromstaerkeMilliAmpere = messwert/204.8/1000;
        float spannungDiodeVolt = betriebsspannungVolt - messwertVolt;

        // betriebsspannung;spannugnÜberR2;Stromstärke;SpannugDiode
        std::cout << betriebsspannungVolt << ";" << messwertVolt << ";" << stromstaerkeMilliAmpere << ";" << spannungDiodeVolt << std::endl;
        file << betriebsspannungVolt << ";" << messwertVolt << ";" << stromstaerkeMilliAmpere << ";" << spannungDiodeVolt << std::endl;
    }

	file.close();
}