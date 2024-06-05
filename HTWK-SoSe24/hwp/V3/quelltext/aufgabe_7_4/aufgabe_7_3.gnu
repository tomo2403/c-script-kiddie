set datafile separator ","
set terminal pngcairo size 1600,1200 enhanced font 'Verdana,20'
set output 'out.png'

# Titel und Achsenbeschriftungen
set title "Aufgabe 7.4"
set xlabel "U in V"
set ylabel "P in mW"
set autoscale



# Plot-Befehl für die Daten
plot 'messwerte.csv' using 1:2 with lines linewidth 3 title "Messwerte",
