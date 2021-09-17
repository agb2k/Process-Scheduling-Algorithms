#include <stdio.h>

// n - total processes
// p - process no. array
// bt - burst time array
// at - arrival time array
// wt - the time taken for the process to start from it's arrival time array
// tat - time spent by process in cpu array
int i, n, j, m, min, idleTime = 0, sum = 0, x = 1, btTally = 0, p[10], bt[10], at[10], wt[10], tat[10], ta = 0;
float tatTally = 0, wtTally = 0;
  float AvgTAT();
  float AvgWT();
//function grabs arrival and burst times of each process and stores it in its respective array
void getInput(){
    printf("\nEnter the total number of processes: ");
    scanf("%d", & n);

    // For Loop for user to input info about the processes
    for (i = 0; i < n; i++) {
        p[i] = i + 1;
        printf("\nEnter the arrival time of process %d: ", p[i]);
        scanf(" %d", & at[i]);
        printf("\nEnter the burst time of process %d: ", p[i]);
        scanf(" %d", & bt[i]);
    }
}
//Function arranges processes according to their arrival times
void arrangePhase1(){
    for (i = 0; i < n; i++) {
        for (j = 0; j < n; j++) {
            if (at[j] > at[i]) {
                m = p[j];
                p[j] = p[i];
                p[i] = m;

                m = at[j];
                at[j] = at[i];
                at[i] = m;

                m = bt[j];
                bt[j] = bt[i];
                bt[i] = m;
            }
        }
    }
}

//Function arranges the processes according to Burst time
void arrangePhase2(){
    btTally = bt[i];
    for (i = 1; i < n; i++) {
        btTally = btTally + bt[i];
        for (int j = 1; j < n; j++) {
            if (bt[j] > bt[i] && btTally >= at[j]) {
                m = p[j];
                p[j] = p[i];
                p[i] = m;

                m = at[j];
                at[j] = at[i];
                at[i] = m;

                m = bt[j];
                bt[j] = bt[i];
                bt[i] = m;
            }
        }
    }
}

//Function calculates the tallies of turnaround time and waiting time
void calcTallies(){

    wt[0] = 0;
    sum = at[0];
    for (i = 1; i < n; i++) {
        sum = sum + bt[i - 1];
        wt[i] = sum - at[i];

        if (wt[i] < 0) {
            idleTime = idleTime + wt[i];
            wt[i] = 0;
        }
        wtTally = wtTally + wt[i];

    }

    for (i = 0; i < n; i++) {
        tat[i] = wt[i] + bt[i];

        tatTally = tatTally + tat[i];
    }

}


//Function displays all of the information about the algorithm running
void showFinal(){
    printf("\nProcess\t Arrival Time\t Burst Time\t Waiting Time\t Turnaround Time");
    for (i = 0; i < n; i++) {
        printf("\n p%d\t %d\t\t %d\t\t %d\t\t %d", p[i], at[i], bt[i], wt[i], tat[i]);
    }


    printf("\nAverage Waiting Time: %.2f", AvgWT());
    printf("\nAverage Turn Around Time: %.2f", AvgTAT());
}

float AvgWT(){
    return (wtTally / n);
}
float AvgTAT() {
    return (tatTally / n);
}