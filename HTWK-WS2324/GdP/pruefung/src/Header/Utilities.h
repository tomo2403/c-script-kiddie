#ifndef PRUEFUNG_UTILITIES_H
#define PRUEFUNG_UTILITIES_H

#include "Mitarbeiter.h"
#include "map"

class Utilities
{
public:
    static void printMitarbeiterTable(std::map<int, Mitarbeiter> mitarbeiterMap);

    static void measureTableContents(std::map<int, Mitarbeiter> mitarbeiterMap, int &maxIdWidth, int &maxNameWidth, int &maxVornameWidth,
                                     int &maxPLZWidth, int &maxGehaltWidth, int &maxTotalWidth);

    static bool tryParse(std::string &input, int &output);

    static bool tryParse(std::string &input, double &output);

    static bool tryGetMitarbeiterId(int &mitarbeiterId);

    static void inputMitarbeiter(std::string &name, std::string &vorname, std::string &plz, std::string &gehaltStr, double &gehalt);

    static void printMitarbeiter(int mitarbeiterId);

    static void printMitarbeiter(Mitarbeiter mitarbeiter);

    static void printSuccess(const std::string &message);

    static void printWarning(const std::string &message);

    static void printError(const std::string &message);

    static bool askQuestion(const std::string &question, bool defaultIsYes);

    static bool containsOnlyLetters(const std::string &input);

    static bool isValidPostalCode(const std::string &input);

    static std::string getInput();

    static void handleSalaryChange(Mitarbeiter &mCurrent, std::string &factorStr);

private:
    static void printMessage(const std::string &message);
};

#endif //PRUEFUNG_UTILITIES_H
