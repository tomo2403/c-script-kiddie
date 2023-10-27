#include <b15f/b15f.h>

int main()
{
    int mode = 0;
    B15F &drv = B15F::getInstance();

    while (true)
    {
        mode = drv.readDipSwitch();
        if (mode == 0)
        {
            drv.digitalWrite0(255 - (int)drv.digitalRead0());
        }
        else if (mode == 1)
        {
            for (int output = 64; output > 1; output /= 2)
            {
                drv.digitalWrite0(output);
                drv.delay_ms(150);
            }

            for (int output = 1; output <= 128; output *= 2)
            {
                drv.digitalWrite0(output);
                drv.delay_ms(150);
            }
        }
    }
}
