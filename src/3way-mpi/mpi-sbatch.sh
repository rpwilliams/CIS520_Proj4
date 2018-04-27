#!/bin/bash -l

module load OpenMPI

mpirun	//usr/bin/time -o /homes/mspicer60/CIS520_Proj4/src/3way-mpi/time/time-10k/time-$RANDOM.txt /homes/mspicer60/CIS520_Proj4/src/3way-mpi/output/output-10k/mpi-10k
