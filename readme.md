# Process Scheduling in C

The program consists of four files:
	1- main.c
	2- new1.c
	3- new1.h
	4- main.exe
You can test the program by running the main.exe file. However, if the user wishes to compile it themself, 
they can do so by running the "gcc -o main.exe *.c" command in the command line.

When the user opens the main.exe file, they will be asked whether they want to run one algorithm individually or all of them simultaneously. 
If they chose to run the algorithms individually (by keying 1), they are prompted to choose one of the four algorithms.

If they want to run all algorithms, they are then prompted to indicate whether or not there is overhead in their workload (the overhead only applies to the Round Robin algorithm).
After, that they are prompted to input the number of processes, the arrival time, and the burst time.

If the user successfully inputs the data, the results of round robin scheduling, Shortest Job First, and First Come First Serve algorithms respectively.

***Important***

For the program to work correctly,
1. it is a must for one of the processes to have an arrival time of 0
2. Also, there cannot be a gap between 2 processes where no process arrives.

Please Note:
When running all algorithms at once (by keying 2 in the initial prompt), the user will be prompted to enter the workload twice.
So please make sure to enter the same workload both times in order to have a fair comparison.

###Made by Abhinav, Mohanad & Salman for OSC COMP2035
