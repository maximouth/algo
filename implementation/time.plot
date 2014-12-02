plot '<sort -g -k2 time.csv' u 2:7 w l
plot '<sort -g -k6 time.csv' u 6:7 w l

set term png
set xlabel "Nb Sommet / Nb Arete"
set ylabel "Time"

set output "time2.png"

replot
quit