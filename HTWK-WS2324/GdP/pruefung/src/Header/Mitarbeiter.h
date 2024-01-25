#ifndef PRUEFUNG_MITARBEITER_H
#define PRUEFUNG_MITARBEITER_H

#include <string>

class Mitarbeiter
{
public:
    Mitarbeiter(std::string name, std::string vorname, std::string postleitzahl, double gehalt);

    std::string name();
    std::string vorname();
    std::string postleitzahl();
    double gehalt(double neuesGehalt = 0);

protected:
    std::string _name;
    std::string _vorname;
    std::string _postleitzahl;
    double _gehalt;
};

#endif //PRUEFUNG_MITARBEITER_H
