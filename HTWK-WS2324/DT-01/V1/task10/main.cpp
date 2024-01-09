#include <b15f/b15f.h>

int main()
{
    // Verbindung zum B15-Board aufbauen
    B15F &drv = B15F::getInstance();

    int mode = 0;
    while (true)
    {
        // DIP Schalter auslesen um aktiven Zustand zu ermitteln
        mode = drv.readDipSwitch();

        if (mode == 0) // Zustand A
        {
            // Digitalen Eingang auf digitalen Ausgang invertieren
            drv.digitalWrite0(255 - (int)drv.digitalRead0());
        }
        else if (mode == 1) // Zustand B
        {
            // Lauflicht in Richtung 1
            for (int output = 64; output > 1; output /= 2)
            {
                drv.digitalWrite0(output);
                drv.delay_ms(150);
            }

            // Lauflicht in Richtig 2
            for (int output = 1; output <= 128; output *= 2)
            {
                drv.digitalWrite0(output);
                drv.delay_ms(150);
            }
        }
    }
}