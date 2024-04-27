set datafile separator ","
set terminal pngcairo size 1600,1200 enhanced font 'Verdana,20'
set output 'aufgbe_8_11.png'

# Titel und Achsenbeschriftungen
set title "Aufgabe 8.11"
set ylabel "I_C in Ampere"
set xlabel "U_C_E in Volt"
set autoscale



# Plot-Befehl für die Daten
plot 'Kennlinie_IC_von_IB_bei_UB_von_0.000000V.csv' using 1:2 with lines linewidth 3 title "U_A_A = 0.0V", \
     'Kennlinie_IC_von_IB_bei_UB_von_1.000000V.csv' using 1:2 with lines linewidth 3 title "U_A_A = 1.0V", \
     'Kennlinie_IC_von_IB_bei_UB_von_2.000000V.csv' using 1:2 with lines linewidth 3 title "U_A_A = 2.0V", \
     'Kennlinie_IC_von_IB_bei_UB_von_2.500000V.csv' using 1:2 with lines linewidth 3 title "U_A_A = 2.5V", \
     'Kennlinie_IC_von_IB_bei_UB_von_3.000000V.csv' using 1:2 with lines linewidth 3 title "U_A_A = 3.0V", \
     'Kennlinie_IC_von_IB_bei_UB_von_4.000000V.csv' using 1:2 with lines linewidth 3 title "U_A_A = 4.0V", \
     'Kennlinie_IC_von_IB_bei_UB_von_5.000000V.csv' using 1:2 with lines linewidth 3 title "U_A_A = 5.0V"