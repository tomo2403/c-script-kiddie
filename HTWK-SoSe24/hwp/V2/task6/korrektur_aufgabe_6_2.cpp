#include <iostream>
#include <fstream>
#include <string>
#include <vector>

struct messwertpaar
{
  double AA0_Volt;
  double AE0_Volt;
};

std::vector<messwertpaar> liesDatei(std::string const &dateiname)
{
  std::string zeile;
  std::ifstream datei(dateiname);
  std::vector<messwertpaar> messwertpaare;
  if (datei.is_open())
  {
    while(std::getline(datei, zeile))
    {
      double AA0_Volt = std::stod(zeile.substr(0, zeile.find(',')));
      double AE0_Volt = std::stod(zeile.substr(zeile.find(',') + 1, zeile.length()));
      messwertpaare.push_back({AA0_Volt, AE0_Volt});
    }
    datei.close();
  }
  return messwertpaare;
}

std::vector<messwertpaar> korrigiere(std::vector<messwertpaar> const &messwertpaare)
{
  std::vector<messwertpaar> messwertpaare_korrigiert;
  for (auto &[AA0_Volt, AE0_Volt] : messwertpaare)
  {
    double AE0_Volt_NEU = AA0_Volt - AE0_Volt;
    messwertpaare_korrigiert.push_back({AA0_Volt, AE0_Volt_NEU});
  }
  return messwertpaare_korrigiert;
}

void druckeDatei(std::vector<messwertpaar> const &messwertpaare)
{
  
    std::ofstream datei("korrigierte_Werte.csv");

    if (datei.is_open())
    {
      for (auto &[AA0_Volt, AE0_Volt] : messwertpaare)
      {
        datei << AA0_Volt << "," << AE0_Volt << std::endl;
      }
      datei.close();
    }
}

int main()
{
  std::vector<messwertpaar> messwertpaare = liesDatei("result2.csv");
  std::vector<messwertpaar> messwertpaare_NEU = korrigiere(messwertpaare);
  druckeDatei(messwertpaare_NEU);
}