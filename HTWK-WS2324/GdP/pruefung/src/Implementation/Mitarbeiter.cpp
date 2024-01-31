#include "../Header/Mitarbeiter.hpp"

Mitarbeiter::Mitarbeiter(std::string name, std::string vorname, std::string postleitzahl, double gehalt) : _name(
        std::move(name)), _vorname(std::move(vorname)), _postleitzahl(std::move(postleitzahl)), _gehalt(gehalt)
{ }

std::string Mitarbeiter::name()
{
    return _name;
}

std::string Mitarbeiter::vorname()
{
    return _vorname;
}

std::string Mitarbeiter::postleitzahl()
{
    return _postleitzahl;
}

double Mitarbeiter::gehalt(double neuesGehalt)
{
    if (neuesGehalt == 0)
        return _gehalt;

    _gehalt = neuesGehalt;
    return _gehalt;
}