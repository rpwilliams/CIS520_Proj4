#!/bin/bash

for i in 1 2 4 8 16 
do
	for j in 1 2 3 4 5 6 7 8 9 10
	do
		sbatch --time=04:00:00 --ntasks-per-node=$i --nodes=1 --mem-per-cpu=$((16/$i))G mpi-sbatch.sh
	done
done
