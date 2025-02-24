#include <stdio.h>

#define MAX_PROCESSES 5
#define MAX_RESOURCES 3

int available[MAX_RESOURCES];
int max[MAX_PROCESSES][MAX_RESOURCES];
int allocation[MAX_PROCESSES][MAX_RESOURCES];
int need[MAX_PROCESSES][MAX_RESOURCES];

void calculateNeed(int processes, int resources) {
    for (int i = 0; i < processes; i++) {
        for (int j = 0; j < resources; j++) {
            need[i][j] = max[i][j] - allocation[i][j];
        }
    }
}

int isSafeState(int processes, int resources) {
    int work[MAX_RESOURCES], finish[MAX_PROCESSES] = {0};
    for (int i = 0; i < resources; i++)
        work[i] = available[i];

    int safeSequence[MAX_PROCESSES], count = 0;

    while (count < processes) {
        int found = 0;
        for (int i = 0; i < processes; i++) {
            if (!finish[i]) {
                int canAllocate = 1;
                for (int j = 0; j < resources; j++) {
                    if (need[i][j] > work[j]) {
                        canAllocate = 0;
                        break;
                    }
                }

                if (canAllocate) {
                    for (int j = 0; j < resources; j++)
                        work[j] += allocation[i][j];

                    safeSequence[count++] = i;
                    finish[i] = 1;
                    found = 1;
                }
            }
        }

        if (!found) {
            printf("System is in an UNSAFE state (Deadlock possible!)\n");
            return 0;
        }
    }

    printf("System is in a SAFE state.\nSafe Sequence: ");
    for (int i = 0; i < processes; i++)
        printf("P%d ", safeSequence[i]);
    printf("\n");
    return 1;
}

void requestResources(int process, int request[], int processes, int resources) {
    for (int i = 0; i < resources; i++) {
        if (request[i] > need[process][i]) {
            printf("Error: Process P%d requested more than its declared max!\n", process);
            return;
        }
        if (request[i] > available[i]) {
            printf("P%d must wait (Not enough resources available)\n", process);
            return;
        }
    }

    for (int i = 0; i < resources; i++) {
        available[i] -= request[i];
        allocation[process][i] += request[i];
        need[process][i] -= request[i];
    }

    if (!isSafeState(processes, resources)) {
        for (int i = 0; i < resources; i++) {
            available[i] += request[i];
            allocation[process][i] -= request[i];
            need[process][i] += request[i];
        }
        printf("Request by P%d denied to maintain safety!\n", process);
    } else {
        printf("Request by P%d granted.\n", process);
    }
}

int main() {
    int processes, resources;
    printf("Enter number of processes: ");
    scanf("%d", &processes);
    printf("Enter number of resources: ");
    scanf("%d", &resources);

    printf("Enter available resources: ");
    for (int i = 0; i < resources; i++)
        scanf("%d", &available[i]);

    printf("Enter max resources needed by each process:\n");
    for (int i = 0; i < processes; i++) {
        printf("P%d: ", i);
        for (int j = 0; j < resources; j++)
            scanf("%d", &max[i][j]);
    }

    printf("Enter allocated resources for each process:\n");
    for (int i = 0; i < processes; i++) {
        printf("P%d: ", i);
        for (int j = 0; j < resources; j++)
            scanf("%d", &allocation[i][j]);
    }

    calculateNeed(processes, resources);
    
    printf("\nChecking initial system state...\n");
    isSafeState(processes, resources);

    int process;
    printf("\nEnter process number requesting resources: ");
    scanf("%d", &process);
    
    int request[MAX_RESOURCES];
    printf("Enter request for P%d: ", process);
    for (int i = 0; i < resources; i++)
        scanf("%d", &request[i]);

    requestResources(process, request, processes, resources);

    return 0;
}
