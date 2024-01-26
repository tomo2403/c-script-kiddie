#include "../Header/Utilities.h"

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
