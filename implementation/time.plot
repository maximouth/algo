plot '<sort -g -k1 time.csv' u 1:8 w l

set term png
set xlabel "Nodes"
set ylabel "Time"

set output "time.png"

replot
quit