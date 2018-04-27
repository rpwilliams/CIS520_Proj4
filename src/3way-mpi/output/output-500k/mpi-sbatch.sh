#!/bin/bash -l

module load OpenMPI

mpirun	//usr/bin/time -o /homes/rpwilliams96/CIS520_Proj4/src/3way-mpi/time/time-500k/time-$RANDOM.txt /homes/rpwilliams96/CIS520_Proj4/src/3way-mpi/output/output-500k/mpi-500k
