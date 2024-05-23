#include <b15f/b15f.h>

using namespace std;
B15F &drv = B15F::getInstance();

using digital_voltage_t = uint16_t;
using voltage_t = double;

voltage_t toVolt(const digital_voltage_t spannung_Integer)
{
    return spannung_Integer * (5.0 / 1023.0);
}

// rechnet eine Spannung [0-5] in Volt in einen Integer Wert [0-1023]
digital_voltage_t toInt(const voltage_t spannung_Volt)
{
    return round(spannung_Volt * (1023.0 / 5.0));
}

void aufgabe_6_1()
{
    int last = 0;
    int i = 0;
    while (true)
    {
        i = drv.analogRead(7);
        if (last != i)
        {
            drv.analogWrite0(i);
            std::cout << i << endl;
            last = i;
        }
    }
}

void aufgabe_6_2()
{
    for (int k = 0; k < 6; k++)
    {
        std::cout << "Gatter: ";
        string filename;
        int input;
        std::cin >> input;
        switch (input)
        {
            case 1:
                filename = "CD74HCT00E";
                break;
            case 2:
                filename = "SN74HC00";
                break;
            case 3:
                filename = "V4012D";
                break;
            case 4:
                filename = "K155LA3";
                break;
            case 5:
                filename = "SN74LS26N";
                break;
            case 6:
                filename = "MM74C00";
                break;
            default:
                return;
        }

        std::ofstream file("result_" + filename + ".csv");

        if (!file.is_open())
        {
            std::cerr << "Konnte die Datei nicht öffnen";
            return;
        }

        std::array<uint16_t, 1024> buffer_AE0_up{}, buffer_AE0_down{};
        drv.analogSequence(0, buffer_AE0_up.data(), 0, 1, nullptr, 0, 0, 1, 1024);
        //drv.analogSequence(0, buffer_AE0_down.data(), 0, 1, nullptr, 0, 1023, -1, 1024);

        for (int i = 1023; i > 0; i--){
            drv.analogWrite0(i);
            buffer_AE0_down.at(i) = drv.analogRead(0);
        }

        file << filename << ",Up,Down" << std::endl;
        for (long unsigned int i = 0; i < buffer_AE0_up.size(); i++)
        {
            file << toVolt(i) << "," << toVolt(buffer_AE0_up[i]) << "," << toVolt(buffer_AE0_down[i]) << std::endl;
        }

        file.close();
    }
}

int main()
{
    aufgabe_6_1();
}