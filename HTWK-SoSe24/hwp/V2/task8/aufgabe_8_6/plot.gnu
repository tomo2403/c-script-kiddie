set datafile separator ","
set terminal pngcairo size 1600,1200 enhanced font 'Verdana,20'
set output 'aufgabe_8_6.png'

# Titel und Achsenbeschriftungen
set title "Transistor-Kennlinie: I_D(U_S_D) <=> I_D geplottet auf U_S_D"
set ylabel "I_D in Ampere"
set xlabel "U_S_D in Volt"
set autoscale

# Plot-Befehl für die Daten
plot 'Verstaerkungskennlinie_ID_von_UGS_bei_UDS_von_2.000000V.csv' using 1:2 with lines linewidth 3 title "5V", \
     'Verstaerkungskennlinie_ID_von_UGS_bei_UDS_von_3.000000V.csv' using 1:2 with lines linewidth 3 title "5V", \
     'Verstaerkungskennlinie_ID_von_UGS_bei_UDS_von_4.000000V.csv' using 1:2 with lines linewidth 3 title "5V", \
     'Verstaerkungskennlinie_ID_von_UGS_bei_UDS_von_5.000000V.csv' using 1:2 with lines linewidth 3 title "5V"
