#include <b15f/b15f.h>
#include <array>
#include <vector>
#include <cstdint>
#include <iomanip>
#include <string>
#include <fstream>
#include <iostream>

B15F &drv = B15F::getInstance();

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
        for (int i = 0; i < 1023; i++)
        {
            std::vector<uint16_t> messdurchlauf_int(anzMesswerte);
            
            // Schreibt 2x in gleichen Buffer
            drv.analogSequence(0, messdurchlauf_int.data(), 0, 0, messdurchlauf_int.data(), 0, 0, 0, anzMesswerte);
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