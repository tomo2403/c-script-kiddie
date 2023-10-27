#include <iostream>

std::string numberToBinary(int number) {
    std::string binary = "";
    while(number != 0) {
        int mod = number % 2;
        number = number / 2;

        
        if (mod == 1) {
            binary = binary.insert(0, "1");
        } else {
            binary = binary.insert(0, "0");
        }
    }
    return binary;
}