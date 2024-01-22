#include <utility>

#ifndef PRUEFUNG_MITARBEITER_H
#define PRUEFUNG_MITARBEITER_H

class Mitarbeiter
{
public:
    Mitarbeiter(int mitarbeiterNummer, std::string name, std::string vorname, unsigned int postleitzahl, double gehalt)
            : mitarbeiterNummer(mitarbeiterNummer), name(std::move(name)), vorname(std::move(vorname)), postleitzahl(postleitzahl), gehalt(gehalt)
    { }

    int getMitarbeiterNummer()
    {
        return mitarbeiterNummer;
    }
    std::string name;
    std::string vorname;
    unsigned int postleitzahl;
    double gehalt;

private:
    int mitarbeiterNummer;
};

#endif //PRUEFUNG_MITARBEITER_H
