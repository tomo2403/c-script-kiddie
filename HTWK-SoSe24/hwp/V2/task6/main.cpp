#include <b15f/b15f.h>

int main()
{
    // Verbindung zum B15-Board aufbauen
    B15F &drv = B15F::getInstance();

    std::ofstream file("result2.csv");

	if (!file.is_open())
	{
		std::cerr << "Konnte die Datei nicht öffnen";
		return 1;
	}

    for(uint16_t i = 0; i < 1024; i += 2)
    {
        drv.analogWrite0(i);
        uint16_t o = drv.analogRead(0);

        std::cout << (i/204.8) << ";" << (o/204.8) << std::endl;
        file << (i/204.8) << ";" << (o/204.8) << std::endl;
    }

	file.close();
}