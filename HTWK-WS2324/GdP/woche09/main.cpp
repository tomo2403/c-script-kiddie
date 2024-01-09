#include "radMitSchaltung.h"
#include "eingangrad.h"

void rad0() {
    std::cout << "Eingang Rad" << std::endl;

    EingangRad meinFahrrad(44, 13, 0.65);

    std::cout << "Radumfang: " << meinFahrrad.bestimmeRadumfang() << std::endl;
    std::cout << "Entfaltung: " << meinFahrrad.bestimmeEntfaltung() << std::endl;
    meinFahrrad.druckeGeschwindigkeit(40);
    meinFahrrad.druckeGeschwindigkeit(60);
    meinFahrrad.druckeGeschwindigkeit(90);
    meinFahrrad.druckeGeschwindigkeit(140);
}

void rad1() {
    std::cout << "Rad mit Schaltung" << std::endl;

    RadMitSchaltung meinFahrrad(44, 13, 0.65);
    meinFahrrad.setzeGang(1, 3);

    std::cout << "Radumfang: " << meinFahrrad.bestimmeRadumfang() << std::endl;

    for(int i = 0; i < meinFahrrad.gaenge()[0]; i++){
        for (int j = 0; j < meinFahrrad.gaenge()[1]; j++){
            std::cout << "Entfaltung: " << meinFahrrad.bestimmeEntfaltung() << std::endl;
            meinFahrrad.druckeGeschwindigkeit(40);
            meinFahrrad.druckeGeschwindigkeit(60);
            meinFahrrad.druckeGeschwindigkeit(90);
            meinFahrrad.druckeGeschwindigkeit(140);
            meinFahrrad.setzeGang(i, j);
            std::cout << std::endl;
        }
    }
}

int main(){
    int mode;
    std::cin >> mode;

    switch (mode) {
        case 0:
            rad0();
            break;
        case 1:
            rad1();
            break;
        default:
            break;
    }
}