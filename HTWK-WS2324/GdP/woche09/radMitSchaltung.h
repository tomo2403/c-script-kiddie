#ifndef WOCHE09_RADMITSCHALTUNG_H
#define WOCHE09_RADMITSCHALTUNG_H

#include "eingangrad.h"

class RadMitSchaltung : public EingangRad
{
public:
    RadMitSchaltung(int zVorne, int zHinten, double d) : EingangRad(zVorne, zHinten, d)
    {

    }

    double bestimmeEntfaltung() override
    {
        return (double) kettenblaetter[gangHinten] / ritzel[gangVorne] * bestimmeRadumfang();
    }

    int anzahlRitzel()
    {
        return ritzel[gangHinten];
    }

    int anzahlKettenblaetter()
    {
        return kettenblaetter[gangVorne];
    }

    void setzeGang(int kettenblattNummer, int ritzelNummer)
    {
        gangVorne = kettenblattNummer;
        gangHinten = ritzelNummer;
    }

    std::vector<int> gaenge()
    {
        return {static_cast<int>(ritzel.size()), static_cast<int>(kettenblaetter.size())};
    }

private:
    unsigned char gangVorne = 0;
    unsigned char gangHinten = 0;

    std::vector<char> kettenblaetter = {
            34,
            50
    };
    std::vector<char> ritzel = {
            28,
            24,
            21,
            19,
            17,
            15,
            13,
            12,
            11
    };
};


#endif //WOCHE09_RADMITSCHALTUNG_H
