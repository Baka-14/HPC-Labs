set title "Runtime vs Threads for Game Of Life of Matrix size 10,000x10,000"
set xlabel "Threads"
set ylabel "Runtime (seconds)"

# Set the size and resolution of the output image
set terminal png size 800,600
set output "runtime_vs_threads_GOL_10kx10k.png"

# Set the range of the x and y axes
set xrange [1:16]
set yrange [0:35]

# Plot the data using lines
plot "temp1.txt" using 1:2 with lines title "Runtime"
