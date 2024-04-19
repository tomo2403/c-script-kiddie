set datafile separator ";"  # Legt das Trennzeichen für die CSV-Datei fest
set terminal pngcairo       # Ausgabeformat (z.B. PNG)
set output 'plot_led2.png'       # Dateiname für die Ausgabe

# Titel und Achsenbeschriftungen
set title "Messwerte LED"
set ylabel "Stromstärke in mA"
set xlabel "Spannung in V"
set xrange [0:5] # Setze die Grenzen der X-Achse von 0 bis 5
set yrange [0:5]

# Plot-Befehl für die Daten
plot 'result_led.csv' using 1:2 with lines title "Messwerte", '' using 1:1 with lines dashtype 2 title "Eingangsspannung"