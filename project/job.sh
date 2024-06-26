#!/bin/bash -l
#SBATCH --job-name=cluster_project                                  # Job name
#SBATCH --cpus-per-task=1                                           # Set the number of CORES per task
#SBATCH --nodes=1                                                   # number of nodes
#SBATCH --ntasks=2                                                  # number of tasks
#SBATCH --ntasks-per-node=2                                         # number of tasks per node
#SBATCH --time=01:00:00                                             # time (HH:MM:SS)
#SBATCH --partition=g100_usr_prod                                   # partition
#SBATCH --account=tra24_sepolimi                                    # project account
#SBATCH -o %x-out.txt                                            # output file name
#SBATCH -e %x-err.txt                                            # error file name

# the flag -C allows execution without super user permission thanks to the setting of environment and file system
singularity run -C cluster_project.sif 