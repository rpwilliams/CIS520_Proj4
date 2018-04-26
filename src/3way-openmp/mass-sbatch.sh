#!/bin/bash

for i in 1 2 4 8 16 
do
	 sbatch --constraint=elves --time=04:00:00 --ntasks-per-node=$i --nodes=1 --mem-per-cpu=$((16/$i))G --partition=killable.q openmp-sbatch.sh
<<<<<<< HEAD
done
=======
done
>>>>>>> 55f0ce63f63eab174bd870225c7a329e11f3efed
