#include <stdio.h>
#include <stdlib.h>

#define MAX_BLOCKS 10
#define MAX_PROCESSES 5

// Function to implement First Fit strategy
void firstFit(int blockSize[], int blocks, int processSize[], int processes) {
    int allocation[MAX_PROCESSES] = {-1};  // Store allocated block index for each process

    for (int i = 0; i < processes; i++) {  
        for (int j = 0; j < blocks; j++) {  
            if (blockSize[j] >= processSize[i]) {  
                allocation[i] = j;
                blockSize[j] -= processSize[i];  
                break;
            }
        }
    }

    printf("\nFirst Fit Allocation:\n");
    for (int i = 0; i < processes; i++) {
        printf("Process %d (%d KB) -> Block %d\n", i + 1, processSize[i], allocation[i] + 1);
    }
}

// Function to implement Best Fit strategy
void bestFit(int blockSize[], int blocks, int processSize[], int processes) {
    int allocation[MAX_PROCESSES] = {-1};

    for (int i = 0; i < processes; i++) {
        int bestIdx = -1;
        for (int j = 0; j < blocks; j++) {
            if (blockSize[j] >= processSize[i]) {
                if (bestIdx == -1 || blockSize[j] < blockSize[bestIdx]) {
                    bestIdx = j;
                }
            }
        }

        if (bestIdx != -1) {
            allocation[i] = bestIdx;
            blockSize[bestIdx] -= processSize[i];
        }
    }

    printf("\nBest Fit Allocation:\n");
    for (int i = 0; i < processes; i++) {
        printf("Process %d (%d KB) -> Block %d\n", i + 1, processSize[i], allocation[i] + 1);
    }
}

// Function to implement Worst Fit strategy
void worstFit(int blockSize[], int blocks, int processSize[], int processes) {
    int allocation[MAX_PROCESSES] = {-1};

    for (int i = 0; i < processes; i++) {
        int worstIdx = -1;
        for (int j = 0; j < blocks; j++) {
            if (blockSize[j] >= processSize[i]) {
                if (worstIdx == -1 || blockSize[j] > blockSize[worstIdx]) {
                    worstIdx = j;
                }
            }
        }

        if (worstIdx != -1) {
            allocation[i] = worstIdx;
            blockSize[worstIdx] -= processSize[i];
        }
    }

    printf("\nWorst Fit Allocation:\n");
    for (int i = 0; i < processes; i++) {
        printf("Process %d (%d KB) -> Block %d\n", i + 1, processSize[i], allocation[i] + 1);
    }
}

int main() {
    int blocks, processes;

    printf("Enter number of memory blocks: ");
    scanf("%d", &blocks);
    int blockSize[MAX_BLOCKS];

    printf("Enter sizes of %d memory blocks:\n", blocks);
    for (int i = 0; i < blocks; i++) {
        scanf("%d", &blockSize[i]);
    }

    printf("Enter number of processes: ");
    scanf("%d", &processes);
    int processSize[MAX_PROCESSES];

    printf("Enter sizes of %d processes:\n", processes);
    for (int i = 0; i < processes; i++) {
        scanf("%d", &processSize[i]);
    }

    // Copy original block sizes (to prevent modifying original values)
    int blockSizeCopy1[MAX_BLOCKS], blockSizeCopy2[MAX_BLOCKS], blockSizeCopy3[MAX_BLOCKS];
    for (int i = 0; i < blocks; i++) {
        blockSizeCopy1[i] = blockSize[i];
        blockSizeCopy2[i] = blockSize[i];
        blockSizeCopy3[i] = blockSize[i];
    }

    firstFit(blockSizeCopy1, blocks, processSize, processes);
    bestFit(blockSizeCopy2, blocks, processSize, processes);
    worstFit(blockSizeCopy3, blocks, processSize, processes);

    return 0;
}
