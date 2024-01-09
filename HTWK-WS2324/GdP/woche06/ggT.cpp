#include "iostream"

int ggT(int a, int b) {
    if (a < b) {
        return ggT(b, a);
    } else if (a % b == 0) {
        return b;
    } else {
        return ggT(b, a % b);
    }
}

int main() {
    std::cout << "Groester gemeinsamer Teiler" << std::endl;

    int a;
    int b;

    std::cout << "Eingabe a: ";
    std::cin >> a;
    std::cout << "Eingabe b: ";
    std::cin >> b;

    std::cout << "Ergebnis = " << ggT(a, b) << std::endl;
}