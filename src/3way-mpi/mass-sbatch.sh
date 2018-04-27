#!/bin/bash

for i in 1 2 4 8 16 
do
	 sbatch --constraint=elves --time=04:00:00 --ntasks-per-node=$i --nodes=1 --mem-per-cpu=$((16/$i))G --partition=killable.q mpi-sbatch.sh
done
done
