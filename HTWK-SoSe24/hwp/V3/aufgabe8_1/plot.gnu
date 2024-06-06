set datafile separator ","
set terminal pngcairo size 1600,1200 enhanced font 'Verdana,20'
set output 'out.png'

# Titel und Achsenbeschriftungen
set title "Aufgabe 8.1"
set ylabel "T in ns"
set xlabel "U in V"
set autoscale

# Plot-Befehl für die Daten
plot 'result.csv' using 1:3 with lines lc rgb "blue" linewidth 3 title "Messerte",
