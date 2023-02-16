set title "Runtime vs Threads"
set xlabel "Threads"
set ylabel "Runtime (seconds)"

# Set the size and resolution of the output image
set terminal png size 800,600
set output "runtime_vs_threads_double_MergeSort.png"

# Set the range of the x and y axes
set xrange [1:16]
set yrange [0:1]

# Plot the data using lines
plot "doubleTimes.dat" using 1:2 with lines title "Runtime"
