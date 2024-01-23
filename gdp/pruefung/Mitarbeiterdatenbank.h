#ifndef PRUEFUNG_MITARBEITERDATENBANK_H
#define PRUEFUNG_MITARBEITERDATENBANK_H

#include <utility>
#include <map>
#include <fstream>
#include <iosfwd>
#include <sstream>

#include "Mitarbeiter.h"

class MitarbeiterDatenbank
{
public:
    int ProvideId()
    {
        nextId++;
        return nextId;
    }

    int neuerMitarbeiter(std::string name, std::string vorname, std::string postleitzahl, double gehalt)
    {
        int id = ProvideId();
        Mitarbeiter mNeu(std::move(name), std::move(vorname), std::move(postleitzahl), gehalt);
        mitarbeiterListe.insert({id, mNeu});
        return id;
    }

    void erhoeheGehalt(int mitarbeiterNummer, double faktor)
    {
        if (mitarbeiterListe.contains(mitarbeiterNummer))
        {
            Mitarbeiter m = mitarbeiterListe.at(mitarbeiterNummer);
            m.gehalt(m.gehalt() * faktor);
            mitarbeiterListe.at(mitarbeiterNummer) = m;
        }
    }

    void loescheMitarbeiter(int mitarbeiterNummer)
    {
        if (mitarbeiterListe.contains(mitarbeiterNummer))
        {
            mitarbeiterListe.erase(mitarbeiterNummer);
        }
    }

    std::vector<int> findeMitarbeiter(const std::string &name, const std::string &vorname)
    {
        std::vector<int> result(0);
        for (auto &mitarbeiter: mitarbeiterListe)
        {
            if (mitarbeiter.second.name().rfind(name) || mitarbeiter.second.vorname().rfind(vorname))
                result.insert(result.cend(), mitarbeiter.first);
        }
        return result;
    }

    void serialisieren()
    {
        std::ofstream file(saveToFilename);

        if (!file.is_open())
        {
            std::cerr << "Konnte die Datei nicht öffnen: " << saveToFilename << std::endl;
            return;
        }

        for (const auto &pair: mitarbeiterListe)
        {
            Mitarbeiter mitarbeiter = pair.second;
            file << pair.first << csvSeparator
                 << mitarbeiter.name() << csvSeparator
                 << mitarbeiter.vorname() << csvSeparator
                 << mitarbeiter.postleitzahl() << csvSeparator
                 << mitarbeiter.gehalt() << "\n\n";
        }

        file.close();
    }

    void deserialisieren()
    {
        std::ifstream file(saveToFilename);

        if (!file.is_open())
        {
            std::cerr << "Konnte die Datei nicht öffnen: " << saveToFilename << std::endl;
            return;
        }

        mitarbeiterListe.clear(); // Vorhandene Daten löschen

        std::string line;
        bool lastLineRead = false;

        while (std::getline(file, line))
        {
            //Leere Zeile überspringen
            if (lastLineRead) continue;
            else lastLineRead = true;

            std::stringstream stream(line);
            std::vector<std::string> result;
            std::string token;

            while (std::getline(stream, token, ';'))
            {
                result.push_back(token);
            }

            // Mitarbeiter-Objekt erstellen und zur Map hinzufügen
            mitarbeiterListe.insert({std::stoi(result[0]),
                                     Mitarbeiter(
                                             result[1],
                                             result[2],
                                             result[3],
                                             std::stod(result[4]))
            });
        }

        file.close();
    }

protected:
    int nextId = 0;
    std::map<int, Mitarbeiter> mitarbeiterListe;
    std::string saveToFilename = "mitarbeiter.csv";
    char csvSeparator = ';';
};

#endif //PRUEFUNG_MITARBEITERDATENBANK_H
