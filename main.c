#include <stdio.h>
#include <stdlib.h>
#define LARGEVAL 10000000
#include <time.h>
#include <windows.h>
#include "new1.h"


//README
//Limitations: Can only take in max 10 processes.
//There has to be a process that starts at t = 0.

//need to fix menu, continues even with invalid input
//doesnt work when you only enter 1 process


int roundrobin(int numProcesses, int arrival_time[], int burst_time[], int overhead, int time_quantum);
void shortestJobFirst();
int findNext (int numProcesses, int burst_time[], int arrival_time[], int time);
int numSameValues(int tmp_burst_time[], int numProcesses);
void printOutput(int burst_time[], int turnaround_time[], int wait_time[], int numProcesses);
float displayAvgTAT (int numProcesses, int turnaround_time[]);
float displayAvgWT (int numProcesses, int wait_time[]);
void compareValsTAT();
void compareValsWT();
void Input();
//void displayCpuUsage(int numProcesses, int burst_time[], int finalCompletionTime);

float RRAvgTAT, FSFCAvgTAT, SJFAvgTAT;

float RRAvgWT, FSFCAvgWT, SJFAvgWT;
typedef struct node {
    int val;
    struct node* next;
} node_t;

void print_list (node_t* head);
node_t *insertatEnd (node_t *head, int val);
void insertatBeginning (node_t** head, int val);
int removeFirst(node_t ** head);

int numProcesses, arrival_time[10], burst_time[10];

int choice, choice2;

int main(){
    clock_t start_t, end_t, total_t;
    int q = 1;
    choice2 = 0;
     choice = 0;
     
    start_t = clock(); //starts clock

    //ask the user whether they want to run one algorithm or all of them 
    printf("Do you have to run each algorithm individually or together? Please type (1) if you want to run them individually. Type (2) if you want to run them all together\n");
    scanf("%d", &choice2);
    if (choice2 == 1) {
        //the user gets to choose which algorithm to run 
        int choice3;
        printf("Choose which algorithm you want to run: (1) FCFS, (2) SJF, (3) Round Robin w/o Overhead or (4) Round Robin w/ Overhead\n(Enter either 1, 2, 3 or 4 on your keyboard)\n");
        scanf("%d", &choice3);
        switch(choice3) {
            //switch statement for each choice of algorithm
            case 1:
            printf("You have chose the First Come First Serve (FCFS) algorithm\n");
            Input();
            roundrobin(numProcesses, arrival_time, burst_time, 0, LARGEVAL);
             end_t = clock(); //ends clock
            total_t = (end_t - start_t ); //gets the total time
            printf("Total number of clock ticks: %f\n", (double)total_t); 
            printf("Total time taken by the CPU: %fs \n", (double)total_t / CLOCKS_PER_SEC); //divides the number of clock ticks by the number of clocks per second to give the total time
            break;

            case 2:
            printf("You have chosen the Shortest Job First (SJF) scheduling algorithm\n");
            shortestJobFirst();
            end_t = clock();
            total_t = (end_t - start_t );
            printf("Total number of clock ticks: %f\n", (double)total_t);
            printf("Total time taken by the CPU: %fs \n", (double)total_t / CLOCKS_PER_SEC);
            break;

            case 3:
            printf("You have chosen the Round Robin w/o Overhead scheduling algorithm\n");
            Input();
            roundrobin(numProcesses, arrival_time, burst_time, 0, 0);
            end_t = clock();
            total_t = (end_t - start_t );
            printf("Total number of clock ticks: %f\n", (double)total_t);
            printf("Total time taken by the CPU: %fs\n", (double)total_t / CLOCKS_PER_SEC);
            break;

            case 4:
            printf("You have chosen Round Robin w/ Overhead\n");
            Input();
            roundrobin(numProcesses, arrival_time, burst_time, -1, 0);
            end_t = clock();
            total_t = (end_t - start_t );
            printf("Total number of clock ticks: %f\n", (double)total_t);
            printf("Total time taken by the CPU: %fs\n", (double)total_t / CLOCKS_PER_SEC);
            break;
    }
        
    } else if (choice2 != 1) {

        //asks the user if there is any overhead in their workload
    printf("Before entering your input data, is there overhead? If no then choose (1) and if yes then choose (2)\n(Enter either 1 or 2 on your keyboard)\n");
    scanf("%d", &choice);


    if (choice == 1){
        printf("Your input has no overhead\n");
       
    }

    if (choice == 2){
        printf("Your input has overhead\n");
    }


    Input(); //takes input


    //runs all algorithms and compares their average turnaround and waiting time
    if (choice == 1){
        printf("Round Robin Algorithm: \n");
        printf("\n");
        roundrobin(numProcesses, arrival_time, burst_time, 0, 0);
        printf("\n");
        printf("Shortest Job First Algorithm\n");
        printf("Please reinput the workload data:\n");
        shortestJobFirst();
        printf("\n");
        printf("\n");
        printf("First Come First Server Algorithm:");
        roundrobin(numProcesses, arrival_time, burst_time, 0, LARGEVAL);
        
        end_t = clock();

        total_t = (end_t - start_t );
        printf("Total number of clock ticks: %f\n", (double)total_t);
        printf("Total time taken by the CPU: %f\ns", (double)total_t / CLOCKS_PER_SEC);
        printf("\n");
        compareValsTAT();
         printf("\n");
        compareValsWT();
        printf("\n");
    }
    if (choice == 2){
        printf("Round Robin Algorithm:");
        printf("\n");
        roundrobin(numProcesses, arrival_time, burst_time, -1, 0);
        printf("\n");
        printf("Shortest Job First Algorithm");
        printf("\n");
        shortestJobFirst();
        printf("\n");
        printf("\n");
        printf("First Come First Server Algorithm:");
        roundrobin(numProcesses, arrival_time, burst_time, 0, LARGEVAL);
        
        end_t = clock();

        total_t = (end_t - start_t );
        printf("Total number of clock ticks: %f\n", (double)total_t);
        printf("Total time taken by the CPU: %f\ns", (double)total_t / CLOCKS_PER_SEC);
        printf("\n");
        compareValsTAT();
         printf("\n");
        compareValsWT();
        printf("\n");
    }
    }
system("pause");
    return 0;
}

int roundrobin(int numProcesses, int arrival_time[], int burst_time[], int overhead, int time_quantum)
{
        int i, time = 0, x, counter = 0;
            int quantum = time_quantum;
    int process_continue = 0;
    int wait_time[10], turnaround_time[10], tmp_burst_time[10], oriArrivalTimes[10];     //need to check if can handle more than 20 processes.
    int finalCompletionTime;

      node_t* head = NULL;

      x = numProcesses;
      for(i = 0; i < numProcesses; i++)
      {
            tmp_burst_time[i] = burst_time[i]; //initializing the temporary burst time array

            wait_time[i] = 0;   //initialize wait_time
            turnaround_time[i] = 0; //initialize tat
      }
      if (time_quantum == 0){
        printf("\nEnter Time Quantum:\t");
        scanf("%d", &time_quantum);
      }


      if (overhead == -1){
            printf("\nEnter overhead:\t");
            scanf("%d", &overhead);

      }

      printf("\nProcess ID\t\tBurst Time\t Turnaround Time\t Waiting Time\n");


      for(i = 0; i < numProcesses; i++)
      {

            tmp_burst_time[i] = burst_time[i]; //initializing the temporary burst time array

            oriArrivalTimes[i] = arrival_time[i];

            wait_time[i] = 0;   //initialize wait_time
            turnaround_time[i] = 0; //initialize tat
      }

      for(time = 0; x != 0;)
      {
            //This can be an issue if no process arrives at t = 0
            if (time == 0){
                for (int j = 0; j < numProcesses; j++){
                    if (arrival_time[j] <= 0){
                        insertatBeginning(&head, j);
                        arrival_time[j] = LARGEVAL;
                    }
                }
            }

            i = removeFirst(&head);

            if(tmp_burst_time[i] <= time_quantum && tmp_burst_time[i] > 0)  //  0 < temp_burst_time <= time_quantum
            {
                  time = time + tmp_burst_time[i];
                  tmp_burst_time[i] = 0;
                  counter = 1;
            }

            else if(tmp_burst_time[i] > time_quantum)  // temp_burst_time > time_quantum
            {
                process_continue = 1;
                  tmp_burst_time[i] = tmp_burst_time[i] - time_quantum; //update burst remaining burst time for the process
                  time = time + time_quantum; //update time
            }

            //checking if any process arrived while current process is running
             for (int k = 0; k <numProcesses; k++){
                if (arrival_time[k] <= time){
                        if (head == NULL){
                            insertatBeginning(&head, k);
                        }
                        else
                            insertatEnd(head, k);
                        arrival_time[k] = LARGEVAL;
                }
            }

            if (process_continue = 1){
                insertatEnd(head, i);
                process_continue = 0;
            }

            if(tmp_burst_time[i] == 0 && counter == 1)  //Checks if process is completed

            {
                  x--;  //to reach termination condition
                  turnaround_time[i] = time - oriArrivalTimes[i];
                  if (x == 0){
                    turnaround_time[i] -= overhead;
                    finalCompletionTime = time;
                  }
                  wait_time[i] = turnaround_time[i] - burst_time[i];
                  counter = 0;

            }
            if (x != 0){
                time += overhead;
            }
      }

           
      printOutput(burst_time, turnaround_time, wait_time, numProcesses);
      if (overhead == 0 && quantum == LARGEVAL) {
      FSFCAvgTAT = displayAvgTAT(numProcesses, turnaround_time);
      FSFCAvgWT = displayAvgWT(numProcesses, wait_time);
      } else {
       RRAvgTAT = displayAvgTAT(numProcesses, turnaround_time);
       RRAvgWT = displayAvgWT(numProcesses, wait_time);
      }



      return 0;
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


void shortestJobFirst(){
    sum = 0;
    x = 1;
    btTally = 0;
    ta = 0;
    tatTally = 0;
    wtTally = 0;
    n = numProcesses;
    p[10];
    for (int k = 0; k < numProcesses; k++) {
        at[k] = arrival_time[k];
        bt[k] = burst_time[k];
    }

    getInput();
    
    
    arrangePhase1();
    arrangePhase2();
    calcTallies();
    showFinal();
    SJFAvgTAT = AvgTAT();
    SJFAvgWT = AvgWT();
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


int findNext (int numProcesses, int burst_time[], int arrival_time[], int time){
    int location = 0;
    for (int c = 1; c < numProcesses; c++){
        if (arrival_time[c] <= time && (burst_time[c] < burst_time[location]))
            location = c;
    }
    return location;
}

int numSameValues(int tmp_burst_time[], int numProcesses){
    int counter = 0;
    for (int i = 0; i < numProcesses; i++){
        if (tmp_burst_time[i] == LARGEVAL){
            counter++;
        }
    }
    return counter;
}

void printOutput(int burst_time[], int turnaround_time[], int wait_time[], int numProcesses){
    for (int i = 0; i<numProcesses; i++){
        printf("\nProcess[%d]\t\t%d\t\t %d\t\t\t %d", i + 1, burst_time[i], turnaround_time[i], wait_time[i]);
    }
}


float displayAvgTAT (int numProcesses, int turnaround_time[]) {
    float total_turnaroundtime = 0, avg_turnaround_time = 0;
    for (int i = 0; i < numProcesses; i++){
        total_turnaroundtime += turnaround_time[i];
    }
    avg_turnaround_time = total_turnaroundtime * 1.0 / numProcesses;
    printf("\n\nAvg Turnaround Time:\t%f", avg_turnaround_time);
    return avg_turnaround_time;
}

float displayAvgWT (int numProcesses, int wait_time[]){
    float total_waitingtime = 0, avg_waittime = 0;
    for (int i = 0; i < numProcesses; i++){
        total_waitingtime += wait_time[i];
    }
    avg_waittime = total_waitingtime * 1.0 / numProcesses;
    printf("\nAvg Wait Time:\t%f\n", avg_waittime);
    return avg_waittime;
}

//******************Linked List Functions*********************//


void print_list (node_t* head){
    node_t* current = head;

    while (current != NULL){

        printf("\n Printing %d ", current->val);
        current = current->next;
    }
}
node_t *insertatEnd (node_t *head, int val){
    node_t *temp = (node_t *)calloc(sizeof(node_t), 1);
    if(!temp) {
        return NULL;
    }

    temp->val = val;
    temp->next = NULL;

    if(!head) {
        return temp;
    }

    node_t *current = head;

    while (current->next != NULL){
        current = current->next;
    }
    
    current->next = temp;
    return head;
}


void insertatBeginning (node_t** head, int val){
    node_t* new_node = (node_t*) malloc (sizeof(node_t));
    new_node -> val = val;
    new_node -> next = *head;
    *head = new_node;
}

int removeFirst(node_t ** head){
    int retval = -1;
    node_t* next_node = NULL;

    //Checking if there is a pointer to head
    if (*head == NULL){
        return -1;
    }

    next_node = (*head)->next;
    retval = (*head)->val;
    free(*head);
    *head = next_node;

    return retval;
}



void compareValsTAT() {

    printf("When comparing the functions by Turnaround time: \n");
if ( FSFCAvgTAT <= RRAvgTAT && FSFCAvgTAT <= SJFAvgTAT )
      printf("First Come First Serve Algorithm is most optimum for this workload.\n");
   else if (RRAvgTAT <= FSFCAvgTAT && RRAvgTAT <= SJFAvgTAT )
      printf("Round Robin Scheduling Algorithm is most optimum for this workload.\n");
   else if ( SJFAvgTAT <= FSFCAvgTAT && SJFAvgTAT <=RRAvgTAT )
      printf("Shortest Job First Algorithm is most optimum for this workload.\n");


}

void compareValsWT() {
    printf("\nWhen comparing the functions by Wait time: \n");
if ( FSFCAvgWT <= RRAvgWT && FSFCAvgWT <= SJFAvgWT )
      printf("First Come First Serve Algorithm is most optimum for this workload.\n");
   else if (RRAvgWT <= FSFCAvgWT && RRAvgWT <= SJFAvgWT )
      printf("Round Robin Scheduling Algorithm is most optimum for this workload.\n");
   else if ( SJFAvgWT <= FSFCAvgWT && SJFAvgWT <= RRAvgWT )
      printf("Shortest Job First Algorithm is most optimum for this workload.\n");

}

void Input() {
    
   printf("\nEnter Number of Processes:\t");
    scanf("%d", &numProcesses);

    for(int i = 0; i < numProcesses; i++)
      {
            printf("\nEnter Details of Process[%d]\n", i + 1);

            printf("Arrival Time:\t");

            scanf("%d", &arrival_time[i]);

            printf("Burst Time:\t");

            scanf("%d", &burst_time[i]);

      }
}