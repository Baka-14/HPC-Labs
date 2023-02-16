#!/bin/bash 
g++ PlsWorkYourMyLastHope.c++ -o nQueens -fopenmp
for((i=10;i<=16;i=i+2)); do
    ./nQueens $i>> nQueensOutput.dat
    echo "$i Queens done" >> nQueensOutput.dat
done
