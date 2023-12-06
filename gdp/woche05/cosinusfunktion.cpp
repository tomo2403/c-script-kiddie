#include "iostream"

int fak(int n){
    int f = 1;
    if (n > 0){
        do {
            f *= n;
            n--;
        } while (n > 0);
    }
    return f;
}

int main(){
    std::cout << "Berechnung der Cosinusfunktion" << std::endl;
    std::cout << "x-Wert eingeben: ";
    double x = 0.0;
    std::cin >> x;
    x = M_PI / 180 * x;
    double cos = 0.0;

    for (int n = 0; n <= 6; n++){
        cos += (pow(-1, n) * pow(x, 2.0 * n)) / fak(2*n);
    }
    std::cout << "cos(" << x << ") = " << cos << std::endl;
}