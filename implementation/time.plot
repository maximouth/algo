plot '<sort -g -k3 time.csv' u 3:8 w l
replot '<sort -g -k4 time.csv' u 4:8 w l

set term png
set xlabel "titi"
set ylabel "Time"

set output "time.png"

replot
quit