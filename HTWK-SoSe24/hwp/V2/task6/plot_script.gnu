set datafile separator ","
set terminal pngcairo size 1600,1200 enhanced font 'Verdana,20'
set output 'aufgabe_6_1.png'

# Titel und Achsenbeschriftungen
set title "Aufgabe 6.1"
set ylabel "AE0 in Volt"
set xlabel "AA0 in Volt"
set autoscale

# Plot-Befehl für die Daten
plot 'result.csv' using 1:1 with lines dashtype 2 title "Betriebsspannung", '' using 1:2 with lines linewidth 3 title "Messwert"
#plot 'result2.csv' using 1:1 with lines dashtype 2 title "Betriebsspannung", '' using 1:2 with lines linewidth 3 title "Messwert"