#!/bin/bash

for i in 1 2 4 8 16 32
do
	 sbatch --constraint=dwarves --ntasks-per-node=$i --nodes=1 --mem-per-cpu=16G --partition=killable.q openmp-sbatch.sh
done
