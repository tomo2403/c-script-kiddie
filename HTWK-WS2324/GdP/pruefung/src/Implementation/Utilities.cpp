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
    }
    catch (std::invalid_argument &)
    {
        return false;
    }
    return true;
}

bool Utilities::tryParse(std::string &input, double &output)
{
    try
    {
        output = std::stod(input);
    } catch (std::invalid_argument &)
    {
        return false;
    }
    return true;
}

void Utilities::printMessage(const std::string &message)
{
    std::cout << STYLE_BOLD << STYLE_UNDERLINE << message << RESET_STYLE << std::endl;
}

void Utilities::printSuccess(const std::string &message)
{
    std::cout << COLOR_GREEN;
    printMessage(message);
}

void Utilities::printWarning(const std::string &message)
{
    std::cout << COLOR_YELLOW;
    printMessage(message);
}

void Utilities::printError(const std::string &message)
{
    std::cout << COLOR_RED;
    printMessage(message);
}

void Utilities::printMitarbeiter(int mitarbeiterId)
{
    try
    {
        Mitarbeiter mitarbeiter = MitarbeiterDatenbank::getMitarbeiter(mitarbeiterId);
        MitarbeiterDatenbank::selectedId = mitarbeiterId;

        std::cout << RESET_STYLE << "\nName: " << mitarbeiter.name() << ", " << mitarbeiter.vorname() << std::endl << "PLZ: "
                  << mitarbeiter.postleitzahl() << std::endl << "Gehalt: " << mitarbeiter.gehalt() << "€" << std::endl;
    }
    catch (std::out_of_range &)
    {
        Utilities::printWarning("Kein Mitarbeiter unter dieser Id verfügbar!");
        MitarbeiterDatenbank::selectedId = 0;
    }
}

bool Utilities::tryGetMitarbeiterId(int &mitarbeiterId)
{
    std::string input;
    while (true)
    {
        std::cout << RESET_STYLE << "Mitarbeiternummer: " << COLOR_BLUE;
        std::getline(std::cin, input);

        if (input.empty())
        {
            return false;
        }
        else if (!Utilities::tryParse(input, mitarbeiterId))
        {
            Utilities::printError("Ungültige Eingabe!\n");
        }
        else
        {
            return true;
        }
    }
}

bool Utilities::containsOnlyLetters(const std::string &input)
{
    return std::ranges::all_of(input, [](char c)
    {
        return std::isalpha(static_cast<unsigned char>(c));
    });
}

bool Utilities::isValidPostalCode(const std::string &input)
{
    // Überprüfen, ob die Länge 5 ist
    if (input.length() != 5)
    {
        return false;
    }

    // Überprüfen, ob alle Zeichen Ziffern sind
    return std::ranges::all_of(input, [](char c)
    {
        return std::isdigit(static_cast<unsigned char>(c));
    });
}

void Utilities::inputMitarbeiter(std::string &name, std::string &vorname, std::string &plz, std::string &gehaltStr)
{
    std::cin.ignore();

    std::cout << "Neuer Name: ";
    std::getline(std::cin, name);

    std::cout << "Neuer Vorname: ";
    std::getline(std::cin, vorname);

    std::cout << "Neue PLZ: ";
    std::getline(std::cin, plz);

    std::cout << "Neues Gehalt: ";
    std::getline(std::cin, gehaltStr);
}

void Utilities::printMitarbeiterDifferences(Mitarbeiter &m1, Mitarbeiter &m2)
{
    std::cout << RESET_STYLE << m1.name() << " --> ";
    if (m2.name().empty())
        std::cout << COLOR_YELLOW << "Ungültige Änderung!";
    else std::cout << (m1.name() == m2.name() ? COLOR_RED : COLOR_GREEN) << m2.name();

    std::cout << RESET_STYLE << std::endl << m1.vorname() << " --> ";
    if (m2.vorname().empty())
        std::cout << COLOR_YELLOW << "Ungültige Änderung!";
    else std::cout << (m1.vorname() == m2.vorname() ? COLOR_RED : COLOR_GREEN) << m2.vorname();

    std::cout << RESET_STYLE << std::endl << m1.postleitzahl() << " --> ";
    if (m2.postleitzahl().empty())
        std::cout << COLOR_YELLOW << "Ungültige Änderung!";
    else std::cout << (m1.postleitzahl() == m2.postleitzahl() ? COLOR_RED : COLOR_GREEN) << m2.postleitzahl();

    std::cout << RESET_STYLE << std::endl << m1.gehalt() << " --> ";
    if (m2.gehalt() == 0)
        std::cout << COLOR_YELLOW << "Ungültige Änderung!";
    else std::cout << (m1.gehalt() == m2.gehalt() ? COLOR_RED : COLOR_GREEN) << m2.gehalt();
    std::cout << RESET_STYLE << std::endl;
}

Mitarbeiter Utilities::validateMitarbeiter(std::string &name, std::string &vorname, std::string &plz, std::string &gehaltStr)
{
    name = containsOnlyLetters(name) ? name : "";
    vorname = containsOnlyLetters(vorname) ? vorname : "";
    plz = isValidPostalCode(plz) ? plz : "";
    double gehalt = tryParse(gehaltStr, gehalt) ? gehalt : 0.0;
    return {name, vorname, plz, gehalt};
}

bool Utilities::askQuestion(const std::string &question, bool defaultIsYes)
{
    std::string answer;
    while (true)
    {
        std::cout << question << " " << (defaultIsYes ? "(Y/n)" : "(y/N)") << ": " << COLOR_BLUE;
        std::getline(std::cin, answer);
        std::cout << RESET_STYLE;
        if (answer.empty())
            return defaultIsYes;
        else
        {
            switch (std::tolower(answer[0]))
            {
                case 'y':
                    return true;
                case 'n':
                    return false;
                default:
                    break;
            }
        }
    }
}