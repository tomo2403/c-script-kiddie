#include <iostream>

int main(){
    std::cout << "Wurzelberechnung nach Heron" << std::endl;

    double c = 0.0;
    std::cout << "Bitte c eingeben: ";
    std::cin >> c;

    double x_n = 1.0;
    for (int i = 0; i < fabs(pow(x_n, 2) - c); i++){
        x_n = x_n / 2.0 + c / (2.0 * x_n);
        std::cout << i << ". Iteration: x_n = " << x_n << "\t\t\tFehler: " << fabs(pow(x_n, 2) - c) << std::endl;
    }

    std::cout << "Wurzel aus " << c << " ist " << x_n << std::endl;
}