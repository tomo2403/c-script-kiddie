#pragma once
#include <string>

/// \brief Repräsentiert einen Mitarbeiter.
class Mitarbeiter
{
public:
	/*!
	 * \brief Erstellt ein neues Mitarbeiter-Objekt.
	 * \param name Der Nachname des Mitarbeiters.
	 * \param vorname Der Vorname des Mitarbeiters.
	 * \param postleitzahl Die Postleitzahl des Wohnorts des Mitarbeiters.
	 * \param gehalt Das Gehalt des Mitarbeiters.
	 */
	Mitarbeiter(std::string name, std::string vorname, std::string postleitzahl, double gehalt);

	/*!
	 * \brief Getter-Funktion für den Nachnamen des Mitarbeiters.
	 * \return Der Nachname des Mitarbeiters.
	 *
	 * Gewährt Lesezugriff auf den privaten Member \a _name.
	 */
	std::string name();

	/*!
	 * \brief Getter-Funktion für den Vornamen des Mitarbeiters.
	 * \return Der Vorname des Mitarbeiters.
	 *
	 * Gewährt Lesezugriff auf den privaten Member \a _vorname.
	 */
	std::string vorname();

	/*!
	 * \brief Getter-Funktion für die Postleitzahl des Wohnortes des Mitarbeiters.
	 * \return Die Postleitzahl des Wohnortes des Mitarbeiters.
	 *
	 * Gewährt Lesezugriff auf den privaten Member \a _postleitzahl.
	 */
	std::string postleitzahl();

	/*!
	 * \brief Getter- und Setter-Funktion für das Gehalt des Mitarbeiters.
	 * \param neuesGehalt Das neue Gehalt, das gesetzt werden soll (optional).
	 * \return Das aktuelle Gehalt des Mitarbeiters.
	 *
	 * Gewährt Lese- und Schreibzugriff auf den privaten Member \a _gehalt.
	 */
	double gehalt(double neuesGehalt = 0);

protected:
    std::string _name; ///< Der Nachname des Mitarbeiters.
    std::string _vorname; ///< Der Vorname des Mitarbeiters.
    std::string _postleitzahl; ///< Die Postleitzahl des Wohnorts des Mitarbeiters.
    double _gehalt; ///< Das Gehalt des Mitarbeiters.
};
