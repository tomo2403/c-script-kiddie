set datafile separator ","  # Legt das Trennzeichen für die CSV-Datei fest
set terminal pngcairo size 1600,1200 enhanced font 'Verdana,20'      # Ausgabeformat (z.B. PNG)
set output 'plot_drain.png'       # Dateiname für die Ausgabe

# Titel und Achsenbeschriftungen
set title "I_D(U_G_S)"
set ylabel "I_D in Ampere"
set xlabel "U_G_S in Volt"
set autoscale
#set xrange [0:5] # Setze die Grenzen der X-Achse von 0 bis 5
#set yrange [0:5]



# Plot-Befehl für die Daten
plot 'Kennlinie_IC_von_IB_bei_UB_von_2.000000V.csv' using 1:2 with lines linewidth 3 title "U_G_S = 0.0V", \
     'Kennlinie_IC_von_IB_bei_UB_von_3.000000V.csv' using 1:2 with lines linewidth 3 title "U_G_S = 1.0V", \
     'Kennlinie_IC_von_IB_bei_UB_von_4.000000V.csv' using 1:2 with lines linewidth 3 title "U_G_S = 2.0V", \
     'Kennlinie_IC_von_IB_bei_UB_von_5.000000V.csv' using 1:2 with lines linewidth 3 title "U_G_S = 2.5V", \