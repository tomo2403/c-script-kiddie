#include <array>
#include <vector>
#include <cstdint>
#include <iomanip>
#include <string>
#include <fstream>

// Test
#include <iostream>
#include <ctime>

class Messinstanz
{
private:
    std::array<std::vector<uint16_t>, 1023> messerte_Int_;

    void ausgabeMesswerte(std::ostream &ausgabestrom)
    {
        for (int i = 0; i < messerte_Int_.size(); i++)
        {
            ausgabestrom << std::setw(4) << std::setfill(' ') << i;
            ausgabestrom << std::setw(1) << ": ";

            for (int j = 0; j < messerte_Int_.at(i).size(); j++)
            {
                ausgabestrom << std::setw(4) << std::setfill(' ') << messerte_Int_.at(i).at(j);
                ausgabestrom << std::setw(1) << " ";
            }

            ausgabestrom << std::endl;
        }
        return;
    }

    void messen(int const &anzMesswerte)
    {
        // Test
        std::srand(static_cast<unsigned int>(std::time(nullptr)));

        for (int i = 0; i < 1023; i++)
        {
            std::vector<uint16_t> messdurchlauf_int(anzMesswerte);
            
            // Test
            for (int j = 0; j < anzMesswerte; j++)
            {
                int random = std::rand() % 1025;
                messdurchlauf_int.at(j) = random;
            }
            messerte_Int_.at(i) = messdurchlauf_int;
        }
    }

public:

    Messinstanz(const int &anzMesswerte = 100)
    {
        messen(anzMesswerte);
    }

    void ausgabeTerminal()
    {
        ausgabeMesswerte(std::cout);
    }

    void ausgabeDatei(std::string const &dateiname)
    {
        std::ofstream datei(dateiname);
        if (datei.is_open())
        {
            ausgabeMesswerte(datei);
            datei.close();
        }
        else
        {
            std::cerr << "Öffnen der Datei fehlgeschlagen" << std::endl;
        }
    }
};

int main()
{
    Messinstanz mess;
    mess.ausgabeTerminal();
    mess.ausgabeDatei("Test.txt");

    return 0;
}