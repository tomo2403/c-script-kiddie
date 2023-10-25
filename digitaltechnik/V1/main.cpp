#include <iostream>
#include <cmath>
#include <b15f/b15f.h>

using namespace std;

/*
 * Erzeugt ein PWM Signal an PB4 mit 100KHz.
 * Beste Frequenz: 31300
 */
int main()
{
	bool isRunningA = true;

	B15F& drv = B15F::getInstance();
		
	while(true) 
    {
        drv.digitalWrite0(255 - (int)drv.digitalRead0()); //digitalWrite1 oder digitalWrite0?
    }
}
