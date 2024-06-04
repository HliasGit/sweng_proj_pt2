#!/bin/bash -l
#SBATCH --cpus-per-task=1                                            # Set the number of CORES per task
#SBATCH --qos=default                                                # SLURM qos
#SBATCH --nodes=1                                                   # number of nodes
#SBATCH --ntasks=2                                                   # number of tasks
#SBATCH --ntasks-per-node=2                                        # number of tasks per node
#SBATCH --time=01:00:00                                              # time (HH:MM:SS)
#SBATCH --partition=g100_usr_prod                                           # partition
#SBATCH --account=a08trb66                                            # project account

singularity run ../my_project.sif