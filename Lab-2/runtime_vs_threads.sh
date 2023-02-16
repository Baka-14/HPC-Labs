set title "Runtime vs Threads for 10 Queens"
set xlabel "Threads"
set ylabel "Runtime (seconds)"

# Set the size and resolution of the output image
set terminal png size 800,600
set output "runtime_vs_threads_10_Queens.png"

# Set the range of the x and y axes
set xrange [1:16]
set yrange [0:0.05]

# Plot the data using lines
plot "times_for_10_Queens.dat" using 1:2 with lines title "Runtime"
