#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>

void processCSV(const std::string& inputFileName, const std::string& outputFileName) {
	std::ifstream inputFile(inputFileName);
	std::ofstream outputFile(outputFileName);

	if (!inputFile.is_open()) {
		std::cerr << "Fehler beim Öffnen der Datei: " << inputFileName << std::endl;
		return;
	}

	if (!outputFile.is_open()) {
		std::cerr << "Fehler beim Öffnen der Datei: " << outputFileName << std::endl;
		return;
	}

	std::string line;
	while (std::getline(inputFile, line)) {
		std::istringstream iss(line);
		std::vector<std::string> columns;
		std::string value;

		while (std::getline(iss, value, ',')) {
			columns.push_back(value);
		}

		if (columns.size() >= 2) {
			try {
				double col1 = std::stod(columns[0]);
				double col2 = std::stod(columns[1]);
				double col3 = col1 * col2;
				outputFile << columns[0] << "," << columns[1] << "," << col3 << "\n";
			} catch (const std::invalid_argument& e) {
				std::cerr << "Ungültiger Wert in Zeile: " << line << std::endl;
				continue;
			}
		} else {
			std::cerr << "Nicht genügend Spalten in Zeile: " << line << std::endl;
		}
	}

	inputFile.close();
	outputFile.close();
}

int main() {
	std::string inputFileName = "messwerte.csv";
	std::string outputFileName = "result.csv";
	processCSV(inputFileName, outputFileName);
	return 0;
}
