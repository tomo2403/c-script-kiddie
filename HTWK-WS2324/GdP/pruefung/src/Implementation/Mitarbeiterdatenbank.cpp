#include <map>
#include <string>
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include "../Header/Mitarbeiterdatenbank.hpp"

void MitarbeiterDatenbank::Init(std::string saveToFilename, char csvSeparator, int nextId)
{
    _saveToFilename = std::move(saveToFilename);
    _csvSeparator = csvSeparator;
    _nextId = nextId;
}

int MitarbeiterDatenbank::neuerMitarbeiter(std::string name, std::string vorname, std::string postleitzahl, double gehalt)
{
    int id = provideId();
    Mitarbeiter mNeu(std::move(name), std::move(vorname), std::move(postleitzahl), gehalt);
    _mitarbeiterListe.insert({id, mNeu});
    return id;
}

void MitarbeiterDatenbank::erhoeheGehalt(int mitarbeiterNummer, double faktor)
{
    auto it = _mitarbeiterListe.find(mitarbeiterNummer);
    if (it != _mitarbeiterListe.end())
    {
        Mitarbeiter &m = it->second;
        m.gehalt(m.gehalt() * faktor);
    }
}

void MitarbeiterDatenbank::loescheMitarbeiter(int mitarbeiterNummer)
{
    _mitarbeiterListe.erase(mitarbeiterNummer);
}

std::vector<int> MitarbeiterDatenbank::findeMitarbeiter(const std::string &name, const std::string &vorname)
{
    std::vector<int> result;
    for (auto &mitarbeiter: _mitarbeiterListe)
    {
        if (mitarbeiter.second.name().rfind(name) != std::string::npos || mitarbeiter.second.vorname().rfind(vorname) != std::string::npos)
        {
            result.push_back(mitarbeiter.first);
        }
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
        file << pair.first << _csvSeparator << mitarbeiter.name() << _csvSeparator << mitarbeiter.vorname() << _csvSeparator
             << mitarbeiter.postleitzahl() << _csvSeparator << mitarbeiter.gehalt() << "\n\n";
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
    bool skipNextLine = false;

    while (std::getline(file, line))
    {
        if (skipNextLine)
        {
            skipNextLine = false;
            continue;
        }
        else
        {
            skipNextLine = true;
        }

        std::stringstream stream(line);
        std::vector<std::string> result;
        std::string token;

        while (std::getline(stream, token, _csvSeparator))
        {
            result.push_back(token);
        }

        if (result.size() == 5)
        {
            _mitarbeiterListe.insert({std::stoi(result[0]), Mitarbeiter(result[1], result[2], result[3], std::stod(result[4]))});
        }
        else
        {
            std::cerr << "Ungültige Zeile in der Datei: " << line << std::endl;
        }
    }

    file.close();
}

std::map<int, Mitarbeiter> MitarbeiterDatenbank::alleMitarbeiter()
{
    return _mitarbeiterListe;
}

Mitarbeiter &MitarbeiterDatenbank::getMitarbeiter(int id)
{
    auto it = _mitarbeiterListe.find(id);
    if (it != _mitarbeiterListe.end())
    {
        return it->second;
    }
    throw std::out_of_range("Kein Mitarbeiter mit dieser ID gefunden");
}

int MitarbeiterDatenbank::provideId()
{
    _nextId++;
    return _nextId;
}

int MitarbeiterDatenbank::selectedId;
int MitarbeiterDatenbank::_nextId;
std::map<int, Mitarbeiter> MitarbeiterDatenbank::_mitarbeiterListe;
std::string MitarbeiterDatenbank::_saveToFilename;
char MitarbeiterDatenbank::_csvSeparator;