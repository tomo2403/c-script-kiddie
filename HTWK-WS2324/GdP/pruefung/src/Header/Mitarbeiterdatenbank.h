#ifndef PRUEFUNG_MITARBEITERDATENBANK_H
#define PRUEFUNG_MITARBEITERDATENBANK_H

#include <map>
#include "Mitarbeiter.h"

class MitarbeiterDatenbank
{
public:
    static void Init(std::string saveToFilename, char csvSeparator, int nextId);
    static int neuerMitarbeiter(std::string name, std::string vorname, std::string postleitzahl, double gehalt);
    static void erhoeheGehalt(int mitarbeiterNummer, double faktor);
    static void loescheMitarbeiter(int mitarbeiterNummer);
    static std::vector<int> findeMitarbeiter(const std::string &name, const std::string &vorname);
    static std::map<int, Mitarbeiter> alleMitarbeiter();
    static void serialisieren();
    static void deserialisieren();

protected:
    static int _nextId;
    static std::map<int, Mitarbeiter> _mitarbeiterListe;
    static std::string _saveToFilename;
    static char _csvSeparator;

    static int provideId();
};

#endif //PRUEFUNG_MITARBEITERDATENBANK_H
