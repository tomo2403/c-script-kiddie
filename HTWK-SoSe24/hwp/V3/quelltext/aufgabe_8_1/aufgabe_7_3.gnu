set datafile separator ","
set terminal pngcairo size 1600,1200 enhanced font 'Verdana,20'
set output 'out.png'

# Titel und Achsenbeschriftungen
set title "Aufgabe 8.1"
set ylabel "Frequenz in MHz"
set xlabel "U in V"
set autoscale



# Plot-Befehl für die Daten
plot 'messwerte.csv' using 1:2 with lines linewidth 3 title "Messerte",
