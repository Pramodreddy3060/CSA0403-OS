#include <stdio.h>

struct Process {
    int id, arrivalTime, burstTime, remainingTime, completionTime, waitingTime, turnaroundTime;
};

void roundRobin(struct Process p[], int n, int quantum) {
    int time = 0, completed = 0;
    
    while (completed < n) {
        for (int i = 0; i < n; i++) {
            if (p[i].remainingTime > 0) {
                if (p[i].remainingTime > quantum) {
                    time += quantum;
                    p[i].remainingTime -= quantum;
                } else {
                    time += p[i].remainingTime;
                    p[i].completionTime = time;
                    p[i].turnaroundTime = p[i].completionTime - p[i].arrivalTime;
                    p[i].waitingTime = p[i].turnaroundTime - p[i].burstTime;
                    p[i].remainingTime = 0;
                    completed++;
                }
                printf("Process %d executed till time %d\n", p[i].id, time);
            }
        }
    }
}

void display(struct Process p[], int n) {
    printf("\nProcess\tAT\tBT\tCT\tTAT\tWT\n");
    for (int i = 0; i < n; i++) {
        printf("%d\t%d\t%d\t%d\t%d\t%d\n", p[i].id, p[i].arrivalTime, p[i].burstTime, 
               p[i].completionTime, p[i].turnaroundTime, p[i].waitingTime);
    }
}

int main() {
    int n, quantum;
    
    printf("Enter number of processes: ");
    scanf("%d", &n);
    
    struct Process p[n];
    
    printf("Enter Time Quantum: ");
    scanf("%d", &quantum);
    
    for (int i = 0; i < n; i++) {
        printf("Enter Arrival Time and Burst Time for Process %d: ", i + 1);
        scanf("%d %d", &p[i].arrivalTime, &p[i].burstTime);
        p[i].id = i + 1;
        p[i].remainingTime = p[i].burstTime;
    }
    
    roundRobin(p, n, quantum);
    display(p, n);
    
    return 0;
}
