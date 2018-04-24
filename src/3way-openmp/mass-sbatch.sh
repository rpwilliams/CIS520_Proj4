#!/bin/bash

for i in 1 2 4 8 16
do
	 sbatch --job-name=testkill --ntasks-per-node=$i --nodes=1 --mem-per-cpu=$((128/$i))G --partition=killable.q openmp-sbatch.sh
done
