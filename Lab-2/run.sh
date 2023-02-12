#!/bin/bash 
gcc nQueens.c -o nQueens -fopenmp
for((i=10;i<=16;i=i+2)); do
	for((j=1;j<=3;j=j+1)); do
    ./nQueens $i $j >> nQueensOutput.txt
    echo "$i Queens done Using $j threads" >> nQueensOutput.txt
  done
done