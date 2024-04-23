set datafile separator ","  # Legt das Trennzeichen für die CSV-Datei fest
set terminal pngcairo       # Ausgabeformat (z.B. PNG)
set output 'plot_drain.png'       # Dateiname für die Ausgabe

# Titel und Achsenbeschriftungen
set title "Messwerte Source-Drain"
set ylabel "Drain Strom in A"
set xlabel "Source Spannung in V"
set autoscale
#set xrange [0:5] # Setze die Grenzen der X-Achse von 0 bis 5
#set yrange [0:5]

# Plot-Befehl für die Daten
plot 'Verstaerkungskennlinie_ID_von_UGS_bei_UDS_von_2.000000V.csv' using 1:2 with lines title "5V", \
     'Verstaerkungskennlinie_ID_von_UGS_bei_UDS_von_3.000000V.csv' using 1:2 with lines title "5V", \
     'Verstaerkungskennlinie_ID_von_UGS_bei_UDS_von_4.000000V.csv' using 1:2 with lines title "5V", \
     'Verstaerkungskennlinie_ID_von_UGS_bei_UDS_von_5.000000V.csv' using 1:2 with lines title "5V"