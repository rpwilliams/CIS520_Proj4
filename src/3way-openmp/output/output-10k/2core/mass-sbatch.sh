#!/bin/bash


for j in 1 2 3 4 5 6 7 8 9 10
do
	sbatch --constraint=elves --time=04:00:00 --ntasks-per-node=2 --nodes=1 --mem-per-cpu=$((16/2))G --partition=killable.q openmp-sbatch.sh
done

