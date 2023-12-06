#include "iostream"
#include "iomanip"

int pascal(int n, int k) {
    return (k == 1 || k == n) ? 1 : pascal(n - 1, k - 1) + pascal(n - 1, k);
}

void druckeDreieck(int max) {
    //Zeilen
    for (int i = 1; i <= max; i++) {
        //Leerzeichen vor jeder Zeile
        for (int z = 1; z <= max - i; z++) {
            std::cout << "   ";
        }

        for (int j = 1; j <= i; j++) {
            std::cout << std::setw(6) << pascal(i, j);
        }
        std::cout << std::endl;
    }
}

int main() {
    std::cout << "Pascalsches Dreieck" << std::endl;
    std::cout << "Wieviele Zeilen?: ";
    int zeilen = 0;
    std::cin >> zeilen;
    druckeDreieck(zeilen);
}