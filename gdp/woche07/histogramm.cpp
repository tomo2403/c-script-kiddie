#include <iomanip>
#include <iostream>
#include <array>
#include <iomanip>
#include <streambuf>
#include <fstream>
#include "cipher.hpp"

std::string leseGanzeDatei(const std::string &dateiname){
    std::ifstream ifs (dateiname);
    return std::string((std::istreambuf_iterator<char>(ifs)),( std::istreambuf_iterator<char>()));
}

int transformChar(char c){
    if (isLowerCase(c)){
        return c - 'a';
    }
    else if (isUpperCase(c)){
        return c - 'A';
    }
    else{
        return -1;
    }
}

void printHistogramm(std::array<int,26> hist){
    for (unsigned int i = 0; i < hist.size(); i++){
        std::cout << "[" << std::setw(2) << i << "]: " << hist[i] << std::endl;
    }
}

std::array<int,26> berechneHistogramm(std::string text){
    std::array<int,26> hist;
    for (unsigned int i = 0; i < hist.size(); i++){
        hist[i] = 0;
    }

    for (unsigned int n = 0; n < text.size(); n++){
        int buchstabenwert = transformChar(text[n]);
        if (buchstabenwert != -1){
            hist[buchstabenwert]++;
        }
    }

    return hist;
}

void printHistogrammGrafisch(std::array<int,26> hist){
    int max = 0;
    for (unsigned int i = 0; i < hist.size(); i++){
        if (hist[i] > max){
            max = hist[i];
        }
    }
    const int maxBreit = 72;
    for (unsigned int i = 0; i < hist.size(); i++){
        int balkenBreite = hist[i] * maxBreit / max;
        std::cout << char(i + 'a') << ": " << std::string(balkenBreite, '#') << std::endl;
    }
}

int rateSchluessel(std::array<int,26> hist){
    int max = 0;
    int maxIndex = -1;

    for (unsigned int i = 0; i < hist.size(); i++){
        if (hist[i] > max){
            max = hist[i];
            maxIndex = i;
        }
    }

    return maxIndex - transformChar('e');
}

int main(){
    std::string dateiinhalt = leseGanzeDatei("rot.txt");
    std::array<int,26> hist = berechneHistogramm(dateiinhalt);

    printHistogramm(hist);
    printHistogrammGrafisch(hist);

    int key = rateSchluessel(hist);
    std::cout << cipherLine(dateiinhalt, key);
}