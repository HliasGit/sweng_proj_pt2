# SE4HPCproject

## Step 2 -- From build to release and manual job execution 

Focus now on the correct implementation of the matrix multiplication you
find in <https://github.com/SimoneReale/SE4HPC_project_part2>. This is a
parallel implementation that uses MPI and reads the matrices to be
multiplied from two files, matrixA.txt and matrixB.txt. In these files
the first row contains the matrix dimensions (number of rows and
columns), while the other rows contain the matrix itself.

Your task is to perform the following steps:

**Preparation**: Use the template available here
<https://github.com/SimoneReale/SE4HPC_project_part2> to create your own
github repository. Add to this repository the tests you have created in
Step1.

**Automating the build, test and release processes**: Create a CI/CD
pipeline that, when someone pushes files in the repo, executes the
building and testing process.

**Containerizing the application**: Go through the following steps:

-   Define a Singularity container descriptor for the matrix
    multiplication program and push it in your repo.

-   Extend the created action to create a container image from your
    description.

**Executing on the cluster**: Go through the following steps:

-   Create a job.sh file to run your containerized application. Make
    sure that the standard output and error are mapped to txt files.

-   Transfer on Galileo100 your job script and the container.

-   Submit your job to the cluster and check whether it works correctly.

-   Push on your github repository your job.sh file and the files
    obtained from the execution of the matrix multiplication.

## Step 3 -- Automating a job submission with containerization 

Extend the action you have created at step 3 to automate completely the
process from a push on the repository to the execution of the
containerized software on SLURM. To do so, you will have to move your
container from the runner to the cluster. You can either use the scp
command or you can publish your image on the Singularity registry and
then pull it from the cluster. Don't forget to handle your secrets
properly! You do not want to leave passwords and authentication tokens
visible to everybody, so you will use the [secrets
mechanism](https://docs.github.com/en/actions/security-guides/using-secrets-in-github-actions?tool=cli).

