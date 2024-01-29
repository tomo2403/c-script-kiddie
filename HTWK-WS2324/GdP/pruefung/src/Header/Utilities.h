#pragma once
#include "Mitarbeiter.h"
#include "map"

/// \brief Bietet verschiedene Hilfsfunktionen für die Anwendung im Zusammenhang mit Mitarbeitern.
class Utilities
{
public:
    /// \brief Gibt eine formatierte Tabelle der Mitarbeiterinformationen aus.
    /// \param mitarbeiterMap Die Map von Mitarbeiter-IDs auf Mitarbeiter-Objekte.
    static void printMitarbeiterTable(std::map<int, Mitarbeiter> mitarbeiterMap);

    /// \brief Misst die Breite der einzelnen Spalten in der Mitarbeiter-Tabelle.
    /// \param mitarbeiterMap Die Map von Mitarbeiter-IDs auf Mitarbeiter-Objekte.
    /// \param maxIdWidth Die maximale Breite der Mitarbeiter-ID-Spalte.
    /// \param maxNameWidth Die maximale Breite der Nachname-Spalte.
    /// \param maxVornameWidth Die maximale Breite der Vorname-Spalte.
    /// \param maxPLZWidth Die maximale Breite der Postleitzahl-Spalte.
    /// \param maxGehaltWidth Die maximale Breite der Gehalt-Spalte.
    /// \param maxTotalWidth Die Gesamtbreite der Tabelle.
    static void measureTableContents(std::map<int, Mitarbeiter> mitarbeiterMap, int &maxIdWidth, int &maxNameWidth, int &maxVornameWidth,
                                     int &maxPLZWidth, int &maxGehaltWidth, int &maxTotalWidth);

    /// \brief Versucht, eine Zeichenkette in eine Ganzzahl umzuwandeln.
    /// \param input Die Eingabezeichenkette.
    /// \param output Die Ausgabe-Ganzzahl (falls erfolgreich).
    /// \return true, wenn die Umwandlung erfolgreich war, andernfalls false.
    static bool tryParse(std::string &input, int &output);

    /// \brief Versucht, eine Zeichenkette in eine Gleitkommazahl umzuwandeln.
    /// \param input Die Eingabezeichenkette.
    /// \param output Die Ausgabe-Gleitkommazahl (falls erfolgreich).
    /// \return true, wenn die Umwandlung erfolgreich war, andernfalls false.
    static bool tryParse(std::string &input, double &output);

    /// \brief Versucht, die Mitarbeiter-ID vom Benutzer zu erhalten.
    /// \param mitarbeiterId Die abgefragte Mitarbeiter-ID (falls erfolgreich).
    /// \return true, wenn die Mitarbeiter-ID erfolgreich abgefragt wurde, andernfalls false.
    static bool tryGetMitarbeiterId(int &mitarbeiterId);

    /// \brief Liest die Benutzereingabe für Mitarbeiterinformationen.
    /// \param name Der Nachname des Mitarbeiters (nach Benutzereingabe).
    /// \param vorname Der Vorname des Mitarbeiters (nach Benutzereingabe).
    /// \param plz Die Postleitzahl des Mitarbeiters (nach Benutzereingabe).
    /// \param gehaltStr Die Gehalt-Information als Zeichenkette (nach Benutzereingabe).
    /// \param gehalt Das Gehalt des Mitarbeiters (nach Umwandlung der Zeichenkette).
    static void inputMitarbeiter(std::string &name, std::string &vorname, std::string &plz, std::string &gehaltStr, double &gehalt);

    /// \brief Gibt die Informationen eines Mitarbeiters mit der angegebenen ID aus.
    /// \param mitarbeiterId Die ID des Mitarbeiters.
    static void printMitarbeiter(int mitarbeiterId);

    /// \brief Gibt die Informationen eines Mitarbeiters aus.
    /// \param mitarbeiter Das Mitarbeiter-Objekt.
    static void printMitarbeiter(Mitarbeiter mitarbeiter);

    /// \brief Gibt eine Erfolgsmeldung aus.
    /// \param message Die Erfolgsmeldung.
    static void printSuccess(const std::string &message);

    /// \brief Gibt eine Warnung aus.
    /// \param message Die Warnung.
    static void printWarning(const std::string &message);

    /// \brief Gibt eine Fehlermeldung aus.
    /// \param message Die Fehlermeldung.
    static void printError(const std::string &message);

    /// \brief Fragt den Benutzer nach einer Ja/Nein-Frage.
    /// \param question Die Frage, die gestellt werden soll.
    /// \param defaultIsYes Der Standardwert (true, wenn die Standardantwort Ja ist, andernfalls false).
    /// \return Die Antwort des Benutzers (true für Ja, false für Nein).
    static bool askQuestion(const std::string &question, bool defaultIsYes);

    /// \brief Überprüft, ob die Zeichenkette nur Buchstaben enthält.
    /// \param input Die zu überprüfende Zeichenkette.
    /// \return true, wenn die Zeichenkette nur Buchstaben enthält, andernfalls false.
    static bool containsOnlyLetters(const std::string &input);

    /// \brief Überprüft, ob die Zeichenkette eine gültige Postleitzahl ist.
    /// \param input Die zu überprüfende Zeichenkette.
    /// \return true, wenn die Zeichenkette eine gültige Postleitzahl ist, andernfalls false.
    static bool isValidPostalCode(const std::string &input);

    /// \brief Liest eine Benutzereingabe.
    /// \return Die eingegebene Zeichenkette.
    static std::string getInput();

    /// \brief Verarbeitet die Gehaltsänderung für einen Mitarbeiter basierend auf einem Faktor.
    /// \param mCurrent Das aktuelle Mitarbeiter-Objekt.
    /// \param factorStr Der Faktor für die Gehaltsänderung als Zeichenkette.
    static void handleSalaryChange(Mitarbeiter &mCurrent, std::string &factorStr);

private:
    /// \brief Gibt eine allgemeine Nachricht aus.
    /// \param message Die Nachricht.
    static void printMessage(const std::string &message);
};
