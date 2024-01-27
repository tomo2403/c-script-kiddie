#include <stdexcept>
#include <string>
#include <iostream>
#include "../Header/ConsoleHelpers.h"
#include "../Header/Utilities.h"
#include "../Header/Mitarbeiterdatenbank.h"

void Utilities::measureTableContents(std::map<int, Mitarbeiter> mitarbeiterMap, int &maxIdWidth, int &maxNameWidth, int &maxVornameWidth,
                                     int &maxPLZWidth, int &maxGehaltWidth, int &maxTotalWidth)
{
    for (auto &entry: mitarbeiterMap)
    {
        Mitarbeiter &mitarbeiter = entry.second;
        maxIdWidth = std::max(maxIdWidth, static_cast<int>(std::to_string(entry.first).length()));
        maxNameWidth = std::max(maxNameWidth, static_cast<int>(mitarbeiter.name().length()));
        maxVornameWidth = std::max(maxVornameWidth, static_cast<int>(mitarbeiter.vorname().length()));
        maxPLZWidth = std::max(maxPLZWidth, static_cast<int>(mitarbeiter.postleitzahl().length()));
        maxGehaltWidth = std::max(maxGehaltWidth, static_cast<int>(std::to_string(static_cast<int>(mitarbeiter.gehalt())).length()));
    }

    maxIdWidth = std::max(10, 2 + maxIdWidth);
    maxNameWidth = std::max(20, 2 + maxNameWidth);
    maxVornameWidth = std::max(20, 2 + maxVornameWidth);
    maxPLZWidth = std::max(15, 2 + maxPLZWidth);
    maxGehaltWidth = std::max(15, 2 + maxGehaltWidth);
    maxTotalWidth = maxIdWidth + maxNameWidth + maxVornameWidth + maxPLZWidth + maxGehaltWidth;
}

bool Utilities::tryParse(std::string &input, int &output)
{
    try
    {
        output = std::stoi(input);
    } catch (std::invalid_argument &)
    {
        return false;
    }
    return true;
}

void Utilities::printWarning(const std::string &message)
{
    std::cout << COLOR_YELLOW << STYLE_BOLD << STYLE_UNDERLINE << message << RESET_STYLE << std::endl;
}

void Utilities::printError(const std::string &message)
{
    std::cout << COLOR_RED << STYLE_BOLD << RESET_UNDERLINE << message << RESET_STYLE << std::endl;
}

void Utilities::printMitarbeiter(int mitarbeiterId)
{
    try
    {
        Mitarbeiter mitarbeiter = MitarbeiterDatenbank::getMitarbeiter(mitarbeiterId);
        MitarbeiterDatenbank::selectedId = mitarbeiterId;

        std::cout << "\nName: " << mitarbeiter.name() << ", " << mitarbeiter.vorname() << std::endl;
        std::cout << "PLZ: " << mitarbeiter.postleitzahl() << std::endl;
        std::cout << "Gehalt: " << mitarbeiter.gehalt() << "€" << std::endl;
    }
    catch (std::out_of_range &)
    {
        Utilities::printWarning("Kein Mitarbeiter unter dieser Id verfügbar!");
    }
}

bool Utilities::tryGetMitarbeiterId(int &mitarbeiterId)
{
    std::string input;
    while (true)
    {
        std::cout << "Mitarbeiternummer: ";
        std::cin >> input;

        if (!Utilities::tryParse(input, mitarbeiterId))
        {
            Utilities::printError("Ungültige Eingabe! (\"0\" eingeben um abzubrechen)\n");
        }
        else
        {
            break;
        }
    }

    return mitarbeiterId != 0;
}
