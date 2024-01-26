#ifndef PRUEFUNG_UTILITIES_H
#define PRUEFUNG_UTILITIES_H

class Utilities
{
public:
    static void measureTableContents(std::map<int, Mitarbeiter> mitarbeiterMap, int &maxIdWidth, int &maxNameWidth, int &maxVornameWidth, int &maxPLZWidth, int &maxGehaltWidth,
                                     int &maxTotalWidth);
};

#endif //PRUEFUNG_UTILITIES_H
