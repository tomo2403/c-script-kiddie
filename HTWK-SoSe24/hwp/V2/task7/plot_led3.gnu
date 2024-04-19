set datafile separator ";"  # Legt das Trennzeichen für die CSV-Datei fest
set terminal pngcairo       # Ausgabeformat (z.B. PNG)
set output 'plot_led3.png'  # Dateiname für die Ausgabe

# Titel und Achsenbeschriftungen
set title "Messwerte LED"
set ylabel "Spannung über Diode in V"
set xlabel "Spannung in V"
set xrange [0:5] # Setze die Grenzen der X-Achse von 0 bis 5
set yrange [0:5]

# Plot-Befehl für die Daten
plot 'result_diode_blackbox.csv' using 1:1 with lines dashtype 2 title "Eingangsspannung", '' using 1:4 with lines title "Schwarz", 'result_diode_blue.csv' using 1:4 with lines title "Blau", 'result_diode_ir.csv' using 1:4 with lines title "IR", 'result_diode_smd.csv' using 1:4 with lines title "SMD", 'result_diode_white.csv' using 1:4 with lines title "Weiß", 'result_diode_yellow.csv' using 1:4 with lines title "Gelb"