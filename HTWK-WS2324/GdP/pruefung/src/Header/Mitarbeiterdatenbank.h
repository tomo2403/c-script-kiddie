#ifndef PRUEFUNG_MITARBEITERDATENBANK_H
#define PRUEFUNG_MITARBEITERDATENBANK_H

#include <map>
#include "Mitarbeiter.h"

class MitarbeiterDatenbank
{
public:
    int ProvideId();
    int neuerMitarbeiter(std::string name, std::string vorname, std::string postleitzahl, double gehalt);
    void erhoeheGehalt(int mitarbeiterNummer, double faktor);
    void loescheMitarbeiter(int mitarbeiterNummer);
    std::vector<int> findeMitarbeiter(const std::string &name, const std::string &vorname);
    void serialisieren();
    void deserialisieren();

protected:
    int nextId = 0;
    std::map<int, Mitarbeiter> mitarbeiterListe;
    std::string saveToFilename = "mitarbeiter.csv";
    char csvSeparator = ';';
};

#endif //PRUEFUNG_MITARBEITERDATENBANK_H
