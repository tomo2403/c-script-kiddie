#include <fstream>
#include <sstream>
#include <iostream>
#include <utility>

#include "../Header/Mitarbeiterdatenbank.h"

int MitarbeiterDatenbank::provideId()
{
    _nextId++;
    return _nextId;
}

int MitarbeiterDatenbank::neuerMitarbeiter(std::string name, std::string vorname, std::string postleitzahl,
                                           double gehalt)
{
    int id = provideId();
    Mitarbeiter mNeu(std::move(name), std::move(vorname), std::move(postleitzahl), gehalt);
    _mitarbeiterListe.insert({id, mNeu});
    return id;
}

void MitarbeiterDatenbank::erhoeheGehalt(int mitarbeiterNummer, double faktor)
{
    if (_mitarbeiterListe.contains(mitarbeiterNummer))
    {
        Mitarbeiter m = _mitarbeiterListe.at(mitarbeiterNummer);
        m.gehalt(m.gehalt() * faktor);
        _mitarbeiterListe.at(mitarbeiterNummer) = m;
    }
}

void MitarbeiterDatenbank::loescheMitarbeiter(int mitarbeiterNummer)
{
    if (_mitarbeiterListe.contains(mitarbeiterNummer))
    {
        _mitarbeiterListe.erase(mitarbeiterNummer);
    }
}

std::vector<int> MitarbeiterDatenbank::findeMitarbeiter(const std::string &name, const std::string &vorname)
{
    std::vector<int> result(0);
    for (auto &mitarbeiter: _mitarbeiterListe)
    {
        if (mitarbeiter.second.name().rfind(name) || mitarbeiter.second.vorname().rfind(vorname))
            result.insert(result.cend(), mitarbeiter.first);
    }
    return result;
}

void MitarbeiterDatenbank::serialisieren()
{
    std::ofstream file(_saveToFilename);

    if (!file.is_open())
    {
        std::cerr << "Konnte die Datei nicht öffnen: " << _saveToFilename << std::endl;
        return;
    }

    for (const auto &pair: _mitarbeiterListe)
    {
        Mitarbeiter mitarbeiter = pair.second;
        file << pair.first << _csvSeparator
             << mitarbeiter.name() << _csvSeparator
             << mitarbeiter.vorname() << _csvSeparator
             << mitarbeiter.postleitzahl() << _csvSeparator
             << mitarbeiter.gehalt() << "\n\n";
    }

    file.close();
}

void MitarbeiterDatenbank::deserialisieren()
{
    std::ifstream file(_saveToFilename);

    if (!file.is_open())
    {
        std::cerr << "Konnte die Datei nicht öffnen: " << _saveToFilename << std::endl;
        return;
    }

    _mitarbeiterListe.clear(); // Vorhandene Daten löschen

    std::string line;
    bool lastLineRead = false;

    while (std::getline(file, line))
    {
        //Leere Zeile überspringen
        if (lastLineRead)
        {
            lastLineRead = false;
            continue;
        }
        else lastLineRead = true;


        std::stringstream stream(line);
        std::vector<std::string> result;
        std::string token;

        while (std::getline(stream, token, ';'))
        {
            result.push_back(token);
        }

        // Mitarbeiter-Objekt erstellen und zur Map hinzufügen
        _mitarbeiterListe.insert({std::stoi(result[0]),
                                  Mitarbeiter(
                                          result[1],
                                          result[2],
                                          result[3],
                                          std::stod(result[4]))
                                 });
    }

    file.close();
}

std::map<int, Mitarbeiter> MitarbeiterDatenbank::alleMitarbeiter()
{
    return _mitarbeiterListe;
}

void MitarbeiterDatenbank::Init(std::string saveToFilename, char csvSeparator, int nextId)
{
    _saveToFilename = std::move(saveToFilename);
    _csvSeparator = csvSeparator;
    _nextId = nextId;
}

Mitarbeiter& MitarbeiterDatenbank::getMitarbeiter(int id)
{
    auto it = _mitarbeiterListe.find(id);
    return it != _mitarbeiterListe.end() ? it->second : throw std::out_of_range("No employee with this id");
}

int MitarbeiterDatenbank::selectedId;
int MitarbeiterDatenbank::_nextId;
std::map<int, Mitarbeiter> MitarbeiterDatenbank::_mitarbeiterListe;
std::string MitarbeiterDatenbank::_saveToFilename;
char MitarbeiterDatenbank::_csvSeparator;