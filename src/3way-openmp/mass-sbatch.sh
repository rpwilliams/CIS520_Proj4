#!/bin/bash

for i in 1 2 4 8 16
do
	 sbatch --constraint=dwarves --ntasks-per-node=$i --nodes=1 openmp-sbatch.sh
done
