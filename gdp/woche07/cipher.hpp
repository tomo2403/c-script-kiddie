#include <iomanip>
#include <iostream>
#include <string>

bool isUpperCase(char c){
    return (c >= 'A') && (c <= 'Z');
}

bool isLowerCase(char c){
    return (c >= 'a') && (c <= 'z');
}

char cipherChar(char z, int key){
    char cipher = z;
    key = (key + 26) % 26;
    if (isUpperCase(z)){
        cipher = (z - 'A' + key) % 26 + 'A';
    }
    else if (isLowerCase(z)){
        cipher = (z - 'a' + key) % 26 + 'a';
    }

    return cipher;
}

std::string cipherLine(std::string z, int key){
    for (unsigned int i = 0; i < z.length(); i++){
        z.at(i) = cipherChar(z.at(i), key);
    }
    return z;
}