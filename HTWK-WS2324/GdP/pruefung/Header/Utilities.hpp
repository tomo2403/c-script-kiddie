#pragma once

#include "map"
#include "Mitarbeiter.hpp"
#include "Mitarbeiterdatenbank.hpp"

/// \brief Bietet verschiedene Hilfsfunktionen für die Anwendung im Zusammenhang mit Mitarbeitern.
class Utilities
{
public:
	/*!
	 * \brief Gibt eine formatierte Tabelle der Mitarbeiterinformationen aus.
	 * \param mitarbeiterMap Die Map von Mitarbeiter-IDs auf Mitarbeiter-Objekte.
	 *
	 * Stellt die Mitarbeiter aus \a mitarbeiterMap anschaulich in der Konsole dar.
	 */
	static void printMitarbeiterTable(std::map<int, Mitarbeiter> mitarbeiterMap);

	/*!
	 * \brief Misst die Breite der einzelnen Spalten in der Mitarbeiter-Tabelle.
	 * \param mitarbeiterMap Die Map von Mitarbeiter-IDs auf Mitarbeiter-Objekte.
	 * \param maxIdWidth Die maximale Breite der Mitarbeiter-ID-Spalte.
	 * \param maxNameWidth Die maximale Breite der Nachname-Spalte.
	 * \param maxVornameWidth Die maximale Breite der Vorname-Spalte.
	 * \param maxPLZWidth Die maximale Breite der Postleitzahl-Spalte.
	 * \param maxGehaltWidth Die maximale Breite der Gehalt-Spalte.
	 * \param maxTotalWidth Die Gesamtbreite der Tabelle.
	 *
	 * Passt die Breite der Tabelle dynamisch in den Inhalt an, damit alle Daten übersichtlich dargestellt werden können.
	 */
	static void measureTableContents(std::map<int, Mitarbeiter> mitarbeiterMap, int &maxIdWidth, int &maxNameWidth, int &maxVornameWidth,
									 int &maxPLZWidth, int &maxGehaltWidth, int &maxTotalWidth);

	/*!
	 * \brief Versucht, eine Zeichenkette in eine Ganzzahl umzuwandeln.
	 * \param input Die Eingabezeichenkette.
	 * \param output Die Ausgabe-Ganzzahl (falls erfolgreich).
	 * \return true, wenn die Umwandlung erfolgreich war, andernfalls false.
	 *
	 * Hilft dabei, Eingaben des Benutzers in ein verarbeitbares Format zu bringen.
	 */
	static bool tryParse(std::string &input, int &output);

	/*!
	 * \brief Versucht, eine Zeichenkette in eine Gleitkommazahl umzuwandeln.
	 * \param input Die Eingabezeichenkette.
	 * \param output Die Ausgabe-Gleitkommazahl (falls erfolgreich).
	 * \return true, wenn die Umwandlung erfolgreich war, andernfalls false.
	 *
	 * Hilft dabei, Eingaben des Benutzers in ein verarbeitbares Format zu bringen.
	 */
	static bool tryParse(std::string &input, double &output);

	/*!
	 * \brief Versucht, die Mitarbeiter-ID vom Benutzer zu erhalten.
	 * \param mitarbeiterId Die abgefragte Mitarbeiter-ID (falls erfolgreich).
	 * \return true, wenn die Mitarbeiter-ID erfolgreich abgefragt wurde, andernfalls false.
	 *
	 * Fragt den Benutzer nach einer Mitarbeiternummer und prüft dessen Eingabe.
	 */
	static bool tryGetMitarbeiterId(int &mitarbeiterId);

	/*!
	 * \brief Liest die Benutzereingabe für Mitarbeiterinformationen.
	 * \param name Der Nachname des Mitarbeiters (nach Benutzereingabe).
	 * \param vorname Der Vorname des Mitarbeiters (nach Benutzereingabe).
	 * \param plz Die Postleitzahl des Mitarbeiters (nach Benutzereingabe).
	 * \param gehaltStr Die Gehalt-Information als Zeichenkette (nach Benutzereingabe).
	 * \param gehalt Das Gehalt des Mitarbeiters (nach Umwandlung der Zeichenkette).
	 *
	 * Stellt den Dialog in der Konsole bereit, um alle nötigen Informationen für einen neuen Mitarbeiter zu erhalten.
	 */
	static void inputMitarbeiter(std::string &name, std::string &vorname, std::string &plz, std::string &gehaltStr, double &gehalt);

	/*!
	 * \brief Gibt die Informationen eines Mitarbeiters mit der angegebenen ID aus.
	 * \param mitarbeiterId Die ID des Mitarbeiters.
	 *
	 * Ermittelt den Mitarbeiter anhand seiner Nummer \a mitarbeiterId und stellt dessen Informationen anschaulich inder Konsole dar.
	 */
	static void printMitarbeiter(int mitarbeiterId, MitarbeiterDatenbank *db);

	/*!
	 * \brief Gibt die Informationen eines Mitarbeiters aus.
	 * \param mitarbeiter Das Mitarbeiter-Objekt.
	 *
	 * Stellt die Informationen des Mitarbeiters \a mitarbeiter anschaulich inder Konsole dar.
	 */
	static void printMitarbeiter(Mitarbeiter mitarbeiter, MitarbeiterDatenbank *db);

	/*!
	 * \brief Gibt eine Erfolgsmeldung aus.
	 * \param message Die Erfolgsmeldung.
	 *
	 * Stellt den Inhalt von \a message anschaulich in der Konsole dar.
	 */
	static void printSuccess(const std::string &message);

	/*!
	 * \brief Gibt eine Warnung aus.
	 * \param message Die Warnung.
	 *
	 * Stellt den Inhalt von \a message anschaulich in der Konsole dar.
	 */
	static void printWarning(const std::string &message);

	/*!
	 * \brief Gibt eine Fehlermeldung aus.
	 * \param message Die Fehlermeldung.
	 *
	 * Stellt den Inhalt von \a message anschaulich in der Konsole dar.
	 */
	static void printError(const std::string &message);

	/*!
	 * \brief Fragt den Benutzer nach einer Ja/Nein-Frage.
	 * \param question Die Frage, die gestellt werden soll.
	 * \param defaultIsYes Der Standardwert (true, wenn die Standardantwort Ja ist, andernfalls false).
	 * \return Die Antwort des Benutzers (true für Ja, false für Nein).
	 *
	 * Gibt eine Frage aus und fragt den Benutzer nach einer Antwort, welche nach Eingabe auf Gültigkeit geprüft wird.
	 */
	static bool askQuestion(const std::string &question, bool defaultIsYes);

	/*!
	 * \brief Überprüft, ob die Zeichenkette nur Buchstaben enthält.
	 * \param input Die zu überprüfende Zeichenkette.
	 * \return true, wenn die Zeichenkette nur Buchstaben enthält, andernfalls false.
	 *
	 * Hilft dabei festzustellen, ob die Eingabe des Benutzers nur Buchstaben enthält.
	 */
	static bool containsOnlyLetters(const std::string &input);

	/*!
	 * \brief Überprüft, ob die Zeichenkette eine gültige Postleitzahl ist.
	 * \param input Die zu überprüfende Zeichenkette.
	 * \return true, wenn die Zeichenkette eine gültige Postleitzahl ist, andernfalls false.
	 *
	 * Hilft dabei festzustellen, ob die Eingabe des Benutzers eine Postleitzahl ist.
	 */
	static bool isValidPostalCode(const std::string &input);

	/*!
	 * \brief Liest eine Benutzereingabe.
	 * \return Die eingegebene Zeichenkette.
	 *
	 * Erhält die Eingabe des Benutzers und stellt diese Farblich dar.
	 */
	static std::string getInput();

	/*!
	 * \brief Verarbeitet die Gehaltsänderung für einen Mitarbeiter basierend auf einem Faktor.
	 * \param mCurrent Das aktuelle Mitarbeiter-Objekt.
	 * \param factorStr Der Faktor für die Gehaltsänderung als Zeichenkette.
	 *
	 * Formatiert die Benutzereingabe zur Gehaltsänderung und wartet auf die Bestätigung der Änderungen.
	 */
	static void handleSalaryChange(Mitarbeiter &mCurrent, std::string &factorStr, MitarbeiterDatenbank *db);

private:
	/*!
	 * \brief Gibt eine allgemeine Nachricht aus.
	 * \param message Die Nachricht.
	 *
	 * Gibt eine Nachricht auf der Konsole aus und setzt eventuelle Formatierungen zurück.
	 */
	static void printMessage(const std::string &message);
};
