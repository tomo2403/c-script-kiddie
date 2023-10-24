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
	
	B15F& drv = B15F::getInstance();
	
	string bin = drv.digitalRead0().tostring();
	
	
	while(true) {
	std::cout << "TOP: " << (int) drv.digitalRead0() << std::endl;
}
}

std::string toBinary(int n)
{
    std::string r;
    while(n!=0){
    	r=(n%2==0 ?"0":"1")+r; 
    	n/=2;
    }
    return r;
}

string invert(string toInvert)
{
	string temp = "";
	while (toInvert.length() != 0){
		temp += toInvert[toInvert.length()-1];
		toInvert.resize(toInvert.length()-1);
	}
	return temp;
}

long fromBin(long n)
{
    long factor = 1;
    long total = 0;

    while (n != 0)
    {
        total += (n%10) * factor;
        n /= 10;
        factor *= 2;
    }

    return total;
}