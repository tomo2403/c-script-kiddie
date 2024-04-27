set datafile separator ","
set terminal pngcairo size 1600,1200 enhanced font 'Verdana,20'
set output 'aufgabe_8_6.png'

# Titel und Achsenbeschriftungen
set title "Aufgabe 8.6"
set ylabel "I_D in Ampere"
set xlabel "U_G_S in Volt"
set autoscale

# Plot-Befehl für die Daten
plot 'Verstaerkungskennlinie_ID_von_UGS_bei_UDS_von_2.000000V.csv' using 1:2 with lines linewidth 3 title "U_D_S = 2.0V", \
     'Verstaerkungskennlinie_ID_von_UGS_bei_UDS_von_3.000000V.csv' using 1:2 with lines linewidth 3 title "U_D_S = 3.0V", \
     'Verstaerkungskennlinie_ID_von_UGS_bei_UDS_von_4.000000V.csv' using 1:2 with lines linewidth 3 title "U_D_S = 4.0V", \
     'Verstaerkungskennlinie_ID_von_UGS_bei_UDS_von_5.000000V.csv' using 1:2 with lines linewidth 3 title "U_D_S = 5.0V"
