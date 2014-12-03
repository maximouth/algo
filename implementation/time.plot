<<<<<<< HEAD
plot '<sort -g -k1 time.csv' u 1:8 w l

set term png
set xlabel "Nodes"
=======
plot '<sort -g -k2 time.csv' u 2:7 w l
plot '<sort -g -k6 time.csv' u 6:7 w l

set term png
set xlabel "Nb Sommet / Nb Arete"
>>>>>>> 6085a4d540354153149b082fb56431b8740a840a
set ylabel "Time"

set output "time2.png"

replot
quit