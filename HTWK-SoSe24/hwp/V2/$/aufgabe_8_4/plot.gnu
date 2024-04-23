set terminal pngcairo
set output 'out.png'
set datafile separator ";"
set style data lines
plot "Kennlinie_ID_von_USD_bei_UGS_von_5.000000V.csv" using 1:2