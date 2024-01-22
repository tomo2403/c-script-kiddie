#ifndef PRUEFUNG_MITARBEITERDATENBANK_H
#define PRUEFUNG_MITARBEITERDATENBANK_H

#include <utility>

#include "Mitarbeiter.h"

class MitarbeiterDatenbank
{
public:
    int ProvideId()
    {
        nextId++;
        return nextId;
    }

    int neuerMitarbeiter(std::string name, std::string vorname, unsigned int postleitzahl, double gehalt)
    {
        Mitarbeiter mNeu(ProvideId(), std::move(name), std::move(vorname), postleitzahl, 0.0);
        //Add to vector
        return mNeu.getMitarbeiterNummer();
    }

    void erhoeheGehalt(unsigned int id, double faktor)
    {

    }

    void loescheMitarbeiter(unsigned int mitarbeiterNummer)
    {

    }

    std::vector<int> findeMitarbeiter(const std::string &name, const std::string &vorname)
    {

    }

    void speichern()
    {

    }

    void laden()
    {

    }

protected:
    int nextId = 0;
    std::vector<Mitarbeiter> mitarbeiterListe;
};

#endif //PRUEFUNG_MITARBEITERDATENBANK_H
