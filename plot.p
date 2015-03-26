#type into gnuplot load'plot.p'
#set terminal postscript 
#set output "graph.ps"or
set terminal jpeg
set output "graph.jpeg"
set style data boxes
set   autoscale                        # scale axes automatically
unset log                              # remove any log-scaling
unset label                            # remove any previous labels
#set xrange [0:26]
#set yrange [0:15]
set xtic auto                          # set xtics automatically
set ytic auto                          # set ytics automatically
set title "frequency differency between cipherfreq and english freq"
set xlabel "cipher number"
set ylabel "freq diff"
plot    "cipherfreqforgnuplot.dat" using 2:3
