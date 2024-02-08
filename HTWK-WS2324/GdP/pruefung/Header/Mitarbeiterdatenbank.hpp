#pragma once

#include <map>
#include <string>
#include <vector>
#include "Mitarbeiter.hpp"

/// \brief Verwaltet eine Datenbank von Mitarbeitern und bietet Funktionen für deren Verwaltung.
class MitarbeiterDatenbank
{
public:
	/*!
	 * \brief Initialisiert die Mitarbeiterdatenbank mit den angegebenen Parametern.
	 * \param path Der Dateiname, in den die Datenbank serialisiert werden soll.
	 * \param csvSeparator Der Trennzeichen-Charakter für CSV-Dateien.
	 * \param startId Die nächste verfügbare ID für einen neuen Mitarbeiter.
	 *
	 * Wird benötigt, um Informationen über den Speicherort und die Trennung von Attributwerten in Dateien zu bestimmen.
	 */
	MitarbeiterDatenbank(std::string path, char csvSeparator, int startId);

	/*!
	 * \brief Fügt einen neuen Mitarbeiter zur Datenbank hinzu und gibt die zugewiesene Mitarbeiter-ID zurück.
	 * \param name Der Nachname des Mitarbeiters.
	 * \param vorname Der Vorname des Mitarbeiters.
	 * \param postleitzahl Die Postleitzahl des Wohnortes des Mitarbeiters.
	 * \param gehalt Das Gehalt des Mitarbeiters.
	 * \return Die ID des neu hinzugefügten Mitarbeiters.
	 *
	 * Erstellt ein neues Mitarbeiterobjekt mit den Werten der übergebenen Parameter, fügt diesen in die Datenbank ein und gibt dessen ID zurück.
	 */
	int neuerMitarbeiter(std::string name, std::string vorname, std::string postleitzahl, double gehalt);

	/*!
	 * \brief Erhöht das Gehalt eines Mitarbeiters basierend auf der Mitarbeiter-ID und einem Faktor.
	 * \param mitarbeiterNummer Die ID des Mitarbeiters.
	 * \param faktor Der Faktor, um den das Gehalt erhöht werden soll.
	 *
	 * Ermittelt den Mitarbeiter zu \a mitarbeiterNummer und multipliziert dessen Gehalt mit \a faktor.
	 */
	void erhoeheGehalt(int mitarbeiterNummer, double faktor);

	/*!
	 * \brief Löscht einen Mitarbeiter aus der Datenbank basierend auf der Mitarbeiter-ID.
	 * \param mitarbeiterNummer Die ID des zu löschenden Mitarbeiters.
	 *
	 * Sucht den Mitarbeiter zur ID \a mitarbeiterNummer und entfernt diesen Eintrag aus der Datenbank.
	 */
	void loescheMitarbeiter(int mitarbeiterNummer);

	/*!
	 * \brief Sucht nach Mitarbeitern basierend auf dem Nachnamen und Vornamen und gibt die IDs der gefundenen Mitarbeiter zurück.
	 * \param name Der Nachname des gesuchten Mitarbeiters.
	 * \param vorname Der Vorname des gesuchten Mitarbeiters.
	 * \return Eine Liste von IDs der gefundenen Mitarbeiter.
	 *
	 * Gibt die Nummern aller Mitarbeiter zurück, deren Name mit \a _name oder Vorname mit \a vorname beginnt.
	 */
	std::vector<int> findeMitarbeiter(const std::string &name, const std::string &vorname);

	/*!
	 * \brief Gibt den Inhalt der gesamten Datenbank zurück.
	 * \return Eine Map, die Mitarbeiter-IDs auf Mitarbeiter-Objekte abbildet.
	 *
	 * Gibt eine Map mit allen Mitarbeitern in der Datenbank zurück.
	 */
	std::map<int, Mitarbeiter> alleMitarbeiter();

	/*!
	 * \brief Gibt einen Mitarbeiter anhand seiner ID zurück.
	 * \param id Die ID des gesuchten Mitarbeiters.
	 * \return Referenz auf das Mitarbeiter-Objekt.
	 *
	 * Ermittelt einen Mitarbeiter anhand seiner Mitarbeiternummer \a id und gibt diesen als Referenz zurück.
	 */
	Mitarbeiter &getMitarbeiter(int id);

	/*!
	 * \brief Serialisiert die Mitarbeiterdatenbank und speichert sie in der angegebenen Datei.
	 *
	 * Speichert die Datenbank in CSV unter dem Pfad \a _filePath und mit den Trennzeichen \a _csvSeparator.
	 */
	void serialisieren();

	/*!
	 * \brief Deserialisiert die Mitarbeiterdatenbank aus der angegebenen Datei.
	 *
	 * Liest die Datenbank aus dem Pfad \a _filePath und mit dem Trennzeichen \a _csvSeparator und fügt die Inhalte der Datei in die Datenbank ein.
	 */
	void deserialisieren();

	int selectedId = -1; ///< Die ID des ausgewählten Mitarbeiters für Operationen mit einem ausgewählten Mitarbeiter.

protected:
	int _currentId; ///< Die nächste verfügbare ID für einen neuen Mitarbeiter.
	std::map<int, Mitarbeiter> mitarbeiterDb = {}; ///< Eine Map, die Mitarbeiter-IDs auf Mitarbeiter-Objekte abbildet.
	std::string _filePath; ///< Der Dateiname, in den die Datenbank serialisiert wird.
	char _csvSeparator; ///< Das Trennzeichen für CSV-Dateien.

	/*!
	 * \brief Generiert und gibt eine neue ID für einen Mitarbeiter zurück.
     * \return Die nächste verfügbare Mitarbeiter-ID.
     *
     * Stellt sicher, dass neue IDs fortlaufend sind und nicht doppelt vergeben werden.
     */
	int provideId();
};
