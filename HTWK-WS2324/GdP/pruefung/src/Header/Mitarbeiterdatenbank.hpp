#pragma once

#include <map>
#include <string>
#include "Mitarbeiter.hpp"

/// \brief Verwaltet eine Datenbank von Mitarbeitern und bietet Funktionen für deren Verwaltung.
class MitarbeiterDatenbank
{
public:
    /// \brief Initialisiert die Mitarbeiterdatenbank mit den angegebenen Parametern.
    /// \param saveToFilename Der Dateiname, in den die Datenbank serialisiert werden soll.
    /// \param csvSeparator Der Trennzeichen-Charakter für CSV-Dateien.
    /// \param nextId Die nächste verfügbare ID für einen neuen Mitarbeiter.
    static void Init(std::string saveToFilename, char csvSeparator, int nextId);

    /// \brief Fügt einen neuen Mitarbeiter zur Datenbank hinzu und gibt die zugewiesene Mitarbeiter-ID zurück.
    /// \param name Der Nachname des Mitarbeiters.
    /// \param vorname Der Vorname des Mitarbeiters.
    /// \param postleitzahl Die Postleitzahl des Wohnortes des Mitarbeiters.
    /// \param gehalt Das Gehalt des Mitarbeiters.
    /// \return Die ID des neu hinzugefügten Mitarbeiters.
    static int neuerMitarbeiter(std::string name, std::string vorname, std::string postleitzahl, double gehalt);

    /// \brief Erhöht das Gehalt eines Mitarbeiters basierend auf der Mitarbeiter-ID und einem Faktor.
    /// \param mitarbeiterNummer Die ID des Mitarbeiters.
    /// \param faktor Der Faktor, um den das Gehalt erhöht werden soll.
    static void erhoeheGehalt(int mitarbeiterNummer, double faktor);


    /// \brief Löscht einen Mitarbeiter aus der Datenbank basierend auf der Mitarbeiter-ID.
    /// \param mitarbeiterNummer Die ID des zu löschenden Mitarbeiters.
    static void loescheMitarbeiter(int mitarbeiterNummer);

    /// \brief Sucht nach Mitarbeitern basierend auf dem Nachnamen und Vornamen und gibt die IDs der gefundenen Mitarbeiter zurück.
    /// \param name Der Nachname des gesuchten Mitarbeiters.
    /// \param vorname Der Vorname des gesuchten Mitarbeiters.
    /// \return Eine Liste von IDs der gefundenen Mitarbeiter.
    static std::vector<int> findeMitarbeiter(const std::string &name, const std::string &vorname);

    /// \brief Gibt eine Map mit allen Mitarbeitern in der Datenbank zurück.
    /// \return Eine Map, die Mitarbeiter-IDs auf Mitarbeiter-Objekte abbildet.
    static std::map<int, Mitarbeiter> alleMitarbeiter();

    /// \brief Gibt einen Mitarbeiter anhand seiner ID zurück.
    /// \param id Die ID des gesuchten Mitarbeiters.
    /// \return Referenz auf das Mitarbeiter-Objekt.
    static Mitarbeiter &getMitarbeiter(int id);

    /// \brief Serialisiert die Mitarbeiterdatenbank und speichert sie in der angegebenen Datei.
    static void serialisieren();

    /// \brief Deserialisiert die Mitarbeiterdatenbank aus der angegebenen Datei.
    static void deserialisieren();

    static int selectedId; ///< Die ID des ausgewählten Mitarbeiters für Operationen mit einem ausgewählten Mitarbeiter.

protected:
    static int _nextId; ///< Die nächste verfügbare ID für einen neuen Mitarbeiter.
    static std::map<int, Mitarbeiter> _mitarbeiterListe; ///< Eine Map, die Mitarbeiter-IDs auf Mitarbeiter-Objekte abbildet.
    static std::string _saveToFilename; ///< Der Dateiname, in den die Datenbank serialisiert wird.
    static char _csvSeparator; ///< Das Trennzeichen für CSV-Dateien.
    
    /// \brief Generiert und gibt eine neue ID für einen Mitarbeiter zurück.
    /// \return Die nächste verfügbare Mitarbeiter-ID.
    static int provideId();
};
