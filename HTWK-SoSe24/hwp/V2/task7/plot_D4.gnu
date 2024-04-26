set datafile separator ","  # Legt das Trennzeichen für die CSV-Datei fest
set terminal pngcairo       # Ausgabeformat (z.B. PNG)
set output 'plot_led_D4.png'       # Dateiname für die Ausgabe

# Titel und Achsenbeschriftungen
set title "Messwerte LED"
set ylabel "Durchflussspannung in V"
set xlabel "Spannung in V"
set xrange [0:5] # Setze die Grenzen der X-Achse von 0 bis 5
set yrange [0:5]

# Plot-Befehl für die Daten
plot 'D4_result_diode.csv' using 1:1 with lines dashtype 2 title "Betriebsspannung", '' using 1:2 with lines linewidth 3 title "Messwert"