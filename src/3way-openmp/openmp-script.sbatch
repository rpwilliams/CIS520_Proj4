#!/bin/bash -l
#SBATCH --job-name=openmp

#SBATCH --mem-per-cpu=4G	# Memory per core, use --mem for memory per node
#SBATCH --time=1  # Use the form DD-HH:MM:SS
#SBATCH --nodes=1
#SBATCH --ntasks-per-node=32

#SBATCH --mail-user=rpwilliams96@ksu.edu
#SBATCH --mail-type=ALL   # same as =BEGIN,FAIL,END


