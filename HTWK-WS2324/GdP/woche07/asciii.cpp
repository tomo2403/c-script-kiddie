#include "iostream"
#include "iomanip"

int main(){
    std::cout << "ASCII - Tabelle" << std::endl;

    std::cout << std::setw(8) << 'i';
    for (int i = 0; i <= 7; i++){
        std::cout << std::setw(7) << "i+" << i;
    }
    std::cout << std::endl;

    for (int i = 32; i <= 127; i += 8){
        std::cout << std::setw(8) <<i;
        for (int n = 0; n <= 7; n++){
            std::cout << std::setw(8) << char(i + n);
        }
        std::cout << std::endl;
    }
}