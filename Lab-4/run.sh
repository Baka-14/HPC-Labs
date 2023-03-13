#!/bin/bash 
javac List_Test.java

for((i=1;i<=5;i=i+1)); do
    for((j=200000;j<=20000000;j=j*10)); do
        for((k=2;k<=16;k=k+2)); do
            java List_Test $k $j 1000000 50 100 100
        done
    done
done