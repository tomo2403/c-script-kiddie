set datafile separator ","
set terminal pngcairo size 1600,1200 enhanced font 'Verdana,20'
set output 'aufgabe_8_4.png'

# Titel und Achsenbeschriftungen
set title "Transistor-Kennlinie: I_D(U_S_D) <=> I_D geplottet auf U_S_D"
set ylabel "I_D in Ampere"
set xlabel "U_S_D in Volt"
set autoscale

# Plot-Befehl für die Daten
plot 'Kennlinie_ID_von_USD_bei_UGS_von_0.000000V.csv' using 1:2 with lines linewidth 3 title "U_G_S = 0.0V", \
     'Kennlinie_ID_von_USD_bei_UGS_von_1.000000V.csv' using 1:2 with lines linewidth 3 title "U_G_S = 1.0V", \
     'Kennlinie_ID_von_USD_bei_UGS_von_2.000000V.csv' using 1:2 with lines linewidth 3 title "U_G_S = 2.0V", \
     'Kennlinie_ID_von_USD_bei_UGS_von_2.500000V.csv' using 1:2 with lines linewidth 3 title "U_G_S = 2.5V", \
     'Kennlinie_ID_von_USD_bei_UGS_von_3.000000V.csv' using 1:2 with lines linewidth 3 title "U_G_S = 3.0V", \
     'Kennlinie_ID_von_USD_bei_UGS_von_4.000000V.csv' using 1:2 with lines linewidth 3 title "U_G_S = 4.0V", \
     'Kennlinie_ID_von_USD_bei_UGS_von_5.000000V.csv' using 1:2 with lines linewidth 3 title "U_G_S = 5.0V"
