set datafile separator ","
set terminal pngcairo size 1600,1200 enhanced font 'Verdana,10'
set output 'out.png'

# Titel und Achsenbeschriftungen
set title "Aufgabe 8.12"
set ylabel "I_C in Ampere"
set xlabel "I_B in Ampere"
set autoscale



# Plot-Befehl für die Daten
plot 'messwerte_v401.csv' using 1:2 with lines linewidth 3 title "U_A_A = 2.0V",