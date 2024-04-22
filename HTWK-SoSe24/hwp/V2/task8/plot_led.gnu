set datafile separator ";"  # Legt das Trennzeichen für die CSV-Datei fest
set terminal pngcairo       # Ausgabeformat (z.B. PNG)
set output 'Kennlinie_ID_von_USD_bei_UGS'       # Dateiname für die Ausgabe

# Titel und Achsenbeschriftungen
set title "Messwerte LED"
set ylabel "Durchflussspannung in V"
set xlabel "Spannung in V"
set xrange [0:5] # Setze die Grenzen der X-Achse von 0 bis 5
set yrange [0:5]

# Plot-Befehl für die Daten
plot './aufgabe_8_4/Kennlinie_ID_von_USD_bei_UGS_von_2.000000V.csv' using 1:2 with lines title "Messwerte", './aufgabe_8_4/Kennlinie_ID_von_USD_bei_UGS_von_2.000000V.csv' using 1:1 with lines dashtype 2 title "Eingangsspannung"
