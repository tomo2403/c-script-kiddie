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

int main(){
//    std::string zeile = "abcdefghijklmnopqrstuvwxyz";
//
//    std::cout << std::setw(15) << "Klartext: " << zeile << std::endl;
//
//    for (int i = 0; i < zeile.length(); i++){
//        char zeichen = zeile.at(i);
//        if (zeichen >= 'a' && zeichen <= 'z'){
//            zeile.at(i) = (zeile.at(i) - 'a' + 3) % 26 + 'a';
//        }
//        else{
//            if (zeichen >= 'A' &&  zeichen <= 'Z'){
//                zeile.at(i) = (zeile.at(i) - 'A' + 3) % 26 + 'A';
//            }
//        }
//    }
//
//    std::cout << std::setw(15) << "verschlüsselt: " << zeile << std::endl;

    std::cout << "Klartext eingeben: ";
    std::string zeile;
    std::getline(std::cin, zeile);

    std::cout << std::setw(15) << "Klartext: " << zeile << std::endl;
    std::cout << std::setw(15) << "verschlüsselt: " << cipherLine(zeile, 3) << std::endl;
    std::cout << std::setw(15) << "entschlüsselt: " << cipherLine(zeile, -3) << std::endl;
}

