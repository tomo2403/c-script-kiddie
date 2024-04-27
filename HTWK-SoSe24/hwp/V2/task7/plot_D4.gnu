set datafile separator ","
set terminal pngcairo size 1600,1200 enhanced font 'Verdana,20'
set output 'aufgabe_7_1.png'

# Titel und Achsenbeschriftungen
set title "Aufgabe 7.1"
set ylabel "Spannung über der Diode in Volt"
set xlabel "Betriebsspannung in V"
set xrange [0:5]
set yrange [0:5]
set xtics 0, 0.5, 5
set ytics 0, 0.5, 5


# Plot-Befehl für die Daten
plot 'D4_result_diode.csv' using 1:4 with lines linewidth 3