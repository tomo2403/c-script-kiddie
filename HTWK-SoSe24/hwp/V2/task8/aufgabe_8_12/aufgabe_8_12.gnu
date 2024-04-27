set datafile separator ","
set terminal pngcairo size 1600,1200 enhanced font 'Verdana,10'
set output 'aufgabe_8_12.png'

# Titel und Achsenbeschriftungen
set title "Aufgabe 8.12"
set ylabel "I_C in Ampere"
set xlabel "I_B in Ampere"
set autoscale
set xtics 0, 0.00015



# Plot-Befehl für die Daten
plot 'Kennlinie_IC_von_IB_bei_UB_von_2.000000V.csv' using 1:2 with lines linewidth 3 title "U_A_A = 2.0V", \
     'Kennlinie_IC_von_IB_bei_UB_von_3.000000V.csv' using 1:2 with lines linewidth 3 title "U_A_A = 3.0V", \
     'Kennlinie_IC_von_IB_bei_UB_von_4.000000V.csv' using 1:2 with lines linewidth 3 title "U_A_A = 4.0V", \
     'Kennlinie_IC_von_IB_bei_UB_von_5.000000V.csv' using 1:2 with lines linewidth 3 title "U_A_A = 5.0V"