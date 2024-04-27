set datafile separator ","
set terminal pngcairo size 1600,1200 enhanced font 'Verdana,20'
set output 'aufgabe_7_3.png'

# Titel und Achsenbeschriftungen
set title "Aufgabe 7.3"
set ylabel "Stromstärke in Milliampere"
set xlabel "Spannung in Volt"
set autoscale


# Plot-Befehl für die Daten
plot 'D1_result_diode.csv' using 4:2 with lines linewidth 3 title "Diode 1", \
     'D2_result_diode.csv' using 4:2 with lines linewidth 3 title "Diode 2", \
     'D3_result_diode.csv' using 4:2 with lines linewidth 3 title "Diode 3", \
     'D4_result_diode.csv' using 4:2 with lines linewidth 3 title "Diode 4", \
     'D5_result_diode.csv' using 4:2 with lines linewidth 3 title "Diode 5", \
     'D6_result_diode.csv' using 4:2 with lines linewidth 3 title "Diode 6"
