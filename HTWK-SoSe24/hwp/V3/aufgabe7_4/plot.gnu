set datafile separator ","
set terminal pngcairo size 1600,1200 enhanced font 'Verdana,20'
set output 'out.png'

# Titel und Achsenbeschriftungen
set title "Aufgabe 7.4"
set xlabel "U in V"
set ylabel "P in mW"
set autoscale

# Plot-Befehl für die Daten
plot 'result.csv' using 1:3 with lines lc rgb "blue" linewidth 3 title "Messwerte",
