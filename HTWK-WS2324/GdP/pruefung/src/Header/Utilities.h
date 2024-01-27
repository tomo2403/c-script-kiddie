#ifndef PRUEFUNG_UTILITIES_H
#define PRUEFUNG_UTILITIES_H

#include "Mitarbeiter.h"
#include "map"

class Utilities
{
public:
    static void measureTableContents(std::map<int, Mitarbeiter> mitarbeiterMap, int &maxIdWidth, int &maxNameWidth, int &maxVornameWidth, int &maxPLZWidth, int &maxGehaltWidth,
                                     int &maxTotalWidth);

    static bool tryParse(std::string& input, int& output);
    static bool tryGetMitarbeiterId(int& mitarbeiterId);

    static void printMitarbeiter(int mitarbeiterId);

    static void printWarning(const std::string &message);
    static void printError(const std::string &message);
};

#endif //PRUEFUNG_UTILITIES_H
