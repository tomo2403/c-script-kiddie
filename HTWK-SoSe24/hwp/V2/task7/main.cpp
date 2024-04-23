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

    std::array<uint16_t, 1024> bufferA, bufferB;
    drv.analogSequence(0, bufferA.data(), 0, 1, bufferB.data(), 0, 0, 1, 1024);
    for(uint16_t i = 0; i < 1024; i++)
    {
        uint16_t messwert = bufferB[i];

        float betriebsspannungVolt = bufferA[i]/204.8;
        float messwertVolt = messwert/204.8;
        float stromstaerkeMilliAmpere = messwert/204.8/1000;
        float spannungDiodeVolt = betriebsspannungVolt - messwertVolt;

        // betriebsspannung;spannugnÜberR2;Stromstärke;SpannugDiode
        std::cout << betriebsspannungVolt << ";" << messwertVolt << ";" << stromstaerkeMilliAmpere << ";" << spannungDiodeVolt << std::endl;
        file << betriebsspannungVolt << ";" << messwertVolt << ";" << stromstaerkeMilliAmpere << ";" << spannungDiodeVolt << std::endl;
    }
    drv.analogWrite0(0);
	file.close();
}