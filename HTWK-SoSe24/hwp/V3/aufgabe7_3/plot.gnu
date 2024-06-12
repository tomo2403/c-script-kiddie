set datafile separator ","
set terminal pngcairo size 1600,1200 enhanced font 'Verdana,20'

# Titel und Achsenbeschriftungen
set title "Aufgabe 7.3"
set xlabel "f in kHz"
set ylabel "P in mW"
set autoscale

# Plot-Befehl für die Daten
set output 'K155LA3.png'
plot 'K155LA3.csv' using 1:2 with lines lc rgb "red" linewidth 3 title "K155LA3"

set output 'MM74C00.png'
plot 'MM74C00.csv' using 1:2 with lines lc rgb "blue" linewidth 3 title "MM74C00"

set output 'SN74HC00.png'
plot 'SN74HC00.csv' using 1:2 with lines lc rgb "violet" linewidth 3 title "SN74HC00"
