#include "iostream"

int summe (int a, int b){
    return a >= b ? a : a + summe(a + 2, b);
}

int main(){
    std::cout << "Summe des Invervalls [a,b]" << std::endl;

    int a;
    int b;

    std::cout << "Eingabe a: ";
    std::cin >> a;
    std::cout << "Eingabe b: ";
    std::cin >> b;

    if ((a & 1) == 1){
        std::cout << "ungerade" << std::endl;
    }

    std::cout << "Summe = " << summe(a,b) << std::endl;
}