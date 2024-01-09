#ifndef WOCHE09_EINGANGRAD_H
#define WOCHE09_EINGANGRAD_H

#include <iostream>
#include <cmath>
#include <iomanip>

class EingangRad {
public:
    EingangRad(int zVorne, int zHinten, double d) : zahnkranz_hinten(zHinten), zahnkranz_vorne(zVorne),
                                                    raddurchmesser(d) {

    }

    double bestimmeRadumfang() {
        return M_PI * raddurchmesser;
    }

    virtual double bestimmeEntfaltung() {
        return (double) zahnkranz_vorne / zahnkranz_hinten * bestimmeRadumfang();
    }

    double bestimmeGeschwindigkeit(unsigned short trittFrequenz) {
        return trittFrequenz * bestimmeEntfaltung() * 60.0 / 1000.0;
    }

    void druckeGeschwindigkeit(int trittFrequenz){
        std::cout << "Geschwindigkeit bei "
                  << std::fixed << std::setprecision(1)
                  << trittFrequenz
                  << " Umdrehungen pro Minute: "
                  << bestimmeGeschwindigkeit(trittFrequenz)
                  << "km/h " << std::endl;
    }

private:
    int zahnkranz_hinten;
    int zahnkranz_vorne;
    double raddurchmesser;
};

#endif //WOCHE09_EINGANGRAD_H
