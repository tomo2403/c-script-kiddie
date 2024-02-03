#include <map>
#include <string>
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include "../Header/Utilities.hpp"
#include "../Header/Mitarbeiterdatenbank.hpp"

void MitarbeiterDatenbank::Init(std::string path, char separator, int startId)
{
	saveToFilename = std::move(path);
	csvSeparator = separator;
	currentId = startId;
}

int MitarbeiterDatenbank::neuerMitarbeiter(std::string name, std::string vorname, std::string postleitzahl, double gehalt)
{
    int id = provideId();
    Mitarbeiter mNeu(std::move(name), std::move(vorname), std::move(postleitzahl), gehalt);
    mitarbeiterDb.insert({id, mNeu});
    return id;
}

void MitarbeiterDatenbank::erhoeheGehalt(int mitarbeiterNummer, double faktor)
{
    auto it = mitarbeiterDb.find(mitarbeiterNummer);
    if (it != mitarbeiterDb.end())
    {
        Mitarbeiter &m = it->second;
        m.gehalt(m.gehalt() * faktor);
    }
}

void MitarbeiterDatenbank::loescheMitarbeiter(int mitarbeiterNummer)
{
    mitarbeiterDb.erase(mitarbeiterNummer);
}

std::vector<int> MitarbeiterDatenbank::findeMitarbeiter(const std::string &name, const std::string &vorname)
{
    std::vector<int> result;
    for (auto &mitarbeiter: mitarbeiterDb)
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
    std::ofstream file(saveToFilename);

    if (!file.is_open())
    {
		Utilities::printError("Konnte die Datei nicht öffnen: " + saveToFilename);
        return;
    }

    for (const auto &pair: mitarbeiterDb)
    {
        Mitarbeiter mitarbeiter = pair.second;
        file << pair.first << csvSeparator << mitarbeiter.name() << csvSeparator << mitarbeiter.vorname() << csvSeparator
			 << mitarbeiter.postleitzahl() << csvSeparator << mitarbeiter.gehalt() << "\n\n";
    }

    file.close();
}

void MitarbeiterDatenbank::deserialisieren()
{
    std::ifstream file(saveToFilename);

    if (!file.is_open())
    {
        std::cerr << "Konnte die Datei nicht öffnen: " << saveToFilename << std::endl;
        return;
    }

    mitarbeiterDb.clear(); // Vorhandene Daten löschen

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

        while (std::getline(stream, token, csvSeparator))
        {
            result.push_back(token);
        }

        if (result.size() == 5 && !mitarbeiterDb.contains(std::stoi(result[0])))
        {
            mitarbeiterDb.insert({std::stoi(result[0]), Mitarbeiter(result[1], result[2], result[3], std::stod(result[4]))});
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
    return mitarbeiterDb;
}

Mitarbeiter &MitarbeiterDatenbank::getMitarbeiter(int id)
{
    auto it = mitarbeiterDb.find(id);
    if (it != mitarbeiterDb.end())
    {
        return it->second;
    }
    throw std::out_of_range("Kein Mitarbeiter mit dieser ID gefunden");
}

int MitarbeiterDatenbank::provideId()
{
    currentId++;
    return currentId;
}

int MitarbeiterDatenbank::selectedId;
int MitarbeiterDatenbank::currentId;
std::map<int, Mitarbeiter> MitarbeiterDatenbank::mitarbeiterDb;
std::string MitarbeiterDatenbank::saveToFilename;
char MitarbeiterDatenbank::csvSeparator;
