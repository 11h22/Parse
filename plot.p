#type into gnuplot load'plot.p'
#set terminal postscript 
#set output "graph.ps"or
set terminal jpeg
set output "graph.jpeg"
#set style data boxes
set pm3d map
set palette defined ( 0 '#000090',\ 
                      1 '#000fff',\
                      2 '#0090ff',\
                      3 '#0fffee',\
                      4 '#90ff70',\
                      5 '#ffee00',\
                      6 '#ff7000',\
                      7 '#ee0000',\
                      8 '#7f0000')   #Matlab color palette
#set log cb
#set   autoscale                        # scale axes automatically
unset log                              # remove any log-scaling
unset label                            # remove any previous labels
set xrange [0:26]
set yrange [0:26]
set xtic auto                          # set xtics automatically
set ytic auto                          # set ytics automatically
set title "frequency differency between cipherfreq and english freq"
set xlabel "cipher number"
set ylabel "freq diff"
splot    "cipherfreq.text" matrix

