#!/bin/bash

#SBATCH --job-name="MPI-A2-101"
#SBATCH --output=%j.stdout
#SBATCH --error=%j.stderr
#SBATCH --nodes=1  # Adjust this if you need more nodes
#SBATCH --time=00:30:00
#SBATCH --mem=8000
#SBATCH --cluster=ub-hpc
#SBATCH --partition=general-compute
#SBATCH --qos=general-compute
#SBATCH --constraint=AVX512
#SBATCH --exclusive

hostname

INPUT_SIZES="10, 100, 120, 160, 200"

# Array of processor counts
PROCESSOR_COUNTS="2, 4, 8, 16, 32"

module load intel
export I_MPI_PMI_LIBRARY=/usr/lib64/libpmi.so

for N in $INPUT_SIZES
do
    for P in $PROCESSOR_COUNTS
    do
        echo "Input Size: $N, Using $P processors:"
        srun --mpi=pmi2 --ntasks=$P ./a2 $N
    done
done

