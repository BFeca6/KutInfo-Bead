set term png 
set out "pendulum.png"

set title "Inga "


set xrange[0:100]
set yrange[-1.2:1.2]
set xlabel "idő"
set ylabel "kitérés"

plot "pendulum.data" u 1:2 w linespoints
replot
