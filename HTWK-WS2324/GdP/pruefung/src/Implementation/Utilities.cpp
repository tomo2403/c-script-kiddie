#include <stdexcept>
#include <string>
#include <iostream>
#include <iomanip>
#include "../Header/ConsoleHelpers.hpp"
#include "../Header/Utilities.hpp"
#include "../Header/Mitarbeiterdatenbank.hpp"

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
    std::cerr << COLOR_RED;
    printMessage(message);
}

void Utilities::printMitarbeiter(int mitarbeiterId)
{
    Mitarbeiter mitarbeiter = MitarbeiterDatenbank::getMitarbeiter(mitarbeiterId);
    MitarbeiterDatenbank::selectedId = mitarbeiterId;
    printMitarbeiter(mitarbeiter);
}

void Utilities::printMitarbeiter(Mitarbeiter mitarbeiter)
{
    try
    {
        std::cout << RESET_STYLE << "\nName: " << mitarbeiter.name() << ", " << mitarbeiter.vorname() << std::endl << "PLZ: "
                  << mitarbeiter.postleitzahl() << std::endl << "Gehalt: " << mitarbeiter.gehalt() << "€" << std::endl;
    } catch (std::out_of_range &)
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
    if (input.length() != 5)
    {
        return false;
    }

    return std::ranges::all_of(input, [](char c)
    {
        return std::isdigit(static_cast<unsigned char>(c));
    });
}

void Utilities::inputMitarbeiter(std::string &name, std::string &vorname, std::string &plz, std::string &gehaltStr, double &gehalt)
{
    while (true)
    {
        std::cout << RESET_STYLE << "Neuer Name: " << COLOR_BLUE;
        std::cin >> name;

        if (containsOnlyLetters(name))
        {
            break;
        }
        Utilities::printError("Wert darf nur aus Buchstaben bestehen!\n");
    }

    while (true)
    {
        std::cout << RESET_STYLE << "Neuer Vorname: " << COLOR_BLUE;
        std::cin >> vorname;

        if (containsOnlyLetters(vorname))
        {
            break;
        }
        Utilities::printError("Wert darf nur aus Buchstaben bestehen!\n");
    }

    while (true)
    {
        std::cout << RESET_STYLE << "Neue PLZ: " << COLOR_BLUE;
        std::cin >> plz;

        if (isValidPostalCode(plz))
        {
            break;
        }
        Utilities::printError("Wert muss eine Zahl sein und 5 Zeichen lang sein!\n");
    }

    while (true)
    {
        std::cout << RESET_STYLE << "Neues Gehalt: " << COLOR_BLUE;
        std::cin >> gehaltStr;

        if (tryParse(gehaltStr, gehalt))
        {
            break;
        }
        Utilities::printError("Wert muss eine Zahl sein!\n");
    }
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

void Utilities::printMitarbeiterTable(std::map<int, Mitarbeiter> mitarbeiterMap)
{
    int maxIdWidth = 0, maxNameWidth = 0, maxVornameWidth = 0, maxPLZWidth = 0, maxGehaltWidth = 0, maxTotalWidth = 0;
    measureTableContents(mitarbeiterMap, maxIdWidth, maxNameWidth, maxVornameWidth, maxPLZWidth, maxGehaltWidth, maxTotalWidth);

    // Tabellenüberschrift
    std::cout << std::setw(maxIdWidth) << "ID" << std::setw(maxNameWidth) << "Name" << std::setw(maxVornameWidth) << "Vorname"
              << std::setw(maxPLZWidth) << "PLZ" << std::setw(maxGehaltWidth) << "Gehalt" << std::endl;
    std::cout << std::setfill('-') << std::setw(maxTotalWidth) << "-" << std::setfill(' ') << std::endl;

    // Mitarbeiterdaten ausgeben
    for (auto &entry: mitarbeiterMap)
    {
        Mitarbeiter &mitarbeiter = entry.second;
        std::cout << std::setw(maxIdWidth) << entry.first << std::setw(maxNameWidth) << mitarbeiter.name() << std::setw(maxVornameWidth)
                  << mitarbeiter.vorname() << std::setw(maxPLZWidth) << mitarbeiter.postleitzahl() << std::setw(maxGehaltWidth)
                  << mitarbeiter.gehalt() << std::setw(0) << std::endl;
    }
}

std::string Utilities::getInput()
{
    std::cout << COLOR_BLUE;
    std::string input;
    std::getline(std::cin, input);
    std::cout << RESET_STYLE;
    return input;
}

void Utilities::handleSalaryChange(Mitarbeiter &mCurrent, std::string &factorStr)
{
    double factor;
    if (tryParse(factorStr, factor))
    {
        std::cout << COLOR_YELLOW << mCurrent.gehalt() << "€" << COLOR_WHITE << "  -->  " << COLOR_GREEN
                  << (mCurrent.gehalt() * factor) << "€" << std::endl << RESET_STYLE << std::endl;

        if (Utilities::askQuestion("Änderungen speichern?", true))
        {
            MitarbeiterDatenbank::erhoeheGehalt(MitarbeiterDatenbank::selectedId, factor);
            Utilities::printSuccess("\nÄnderungen gespeichert!");
        }
    }
    else
    {
        Utilities::printError("Ungültige Eingabe!");
    }
}
