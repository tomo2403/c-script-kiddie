#include <utility>

#ifndef PRUEFUNG_MITARBEITER_H
#define PRUEFUNG_MITARBEITER_H

class Mitarbeiter
{
public:
    Mitarbeiter(std::string name, std::string vorname, std::string postleitzahl, double gehalt)
            : _name(std::move(name)), _vorname(std::move(vorname)), _postleitzahl(std::move(postleitzahl)),
              _gehalt(gehalt)
    { }

    std::string name()
    {
        return _name;
    }

    std::string vorname()
    {
        return _vorname;
    }

    std::string postleitzahl()
    {
        return _postleitzahl;
    }

    double gehalt(double neuesGehalt = 0)
    {
        if (neuesGehalt == 0)
            return _gehalt;

        _gehalt = neuesGehalt;
        return _gehalt;
    }

protected:
    std::string _name;
    std::string _vorname;
    std::string _postleitzahl;
    double _gehalt;
};

#endif //PRUEFUNG_MITARBEITER_H
