#include <stdio.h>
#include <stdlib.h>

#define GARBAGE -1
#define MAX 11

//Global variable used to compare different permutations of actions
int maxTempChange = 0;
//Answer
int bestOrder[MAX];

void permute(int * used, int * perm, int index, int N, int * baseTemp, int ** respectiveTemp, int currentEngineTemp);

int main(){
    //Scan for the number of actions that can be performed
    int numActions;
    scanf("%d", &numActions);

    //Array to store sequences of actions
    int * actionSequence = (int *)malloc(numActions * sizeof(int));
    int * used = (int *)malloc(numActions * sizeof(int));

    for(int i = 0; i < numActions; i++){
        actionSequence[i] = GARBAGE;
        used[i] = 0;
    }

    //Create an array of the base temp changes that each action will have on the engine
    int baseTempChange[numActions];
    for(int i = 0; i < numActions; i++){
        scanf("%d", &baseTempChange[i]);
    }

    //The change in temp that each action will have on the engine if
    //they are performed in a certain order
    int ** respectiveTempChange = (int **)malloc(numActions * sizeof(int *));
    for(int i = 0; i < numActions; i++){
        respectiveTempChange[i] = (int *)malloc(numActions * sizeof(int *));
    }

    //Scan in the temp changes respective of sequences of actions
    for(int i = 0; i < numActions; i++){
        for(int j = 0; j < numActions; j++){
            scanf("%d", &respectiveTempChange[i][j]);
        }
    }

    permute(used, actionSequence, 0, numActions, baseTempChange, respectiveTempChange, 0);


    //Print answer
    for(int i = 0; i < numActions; i++){
        printf("%d ", bestOrder[i]);
    }
    printf("\n");

    //LAND OF THE FREE
    free(actionSequence);
    free(used);

    for(int i = 0; i < numActions; i++){
        free(respectiveTempChange[i]);
    }
    free(respectiveTempChange);

    return 0;
}

//Function to find the best sequence of actions. Generate permutation first, apply temperature changes, compare temp changes to find the "best" sequence.
void permute(int * used, int * perm, int index, int N, int * baseTemp, int ** respectiveTemp, int currentEngineTemp) {
  //Base Case
    if (N == index) {
        if (currentEngineTemp < maxTempChange) {
            maxTempChange = currentEngineTemp;
            for (int i = 0; i < N; i++) {
                bestOrder[i] = perm[i];
            }
        }
        return;
    }

    // Alternatively loop over index
    for (int curValue = 0; curValue < N; curValue++) {
        // Check if the value is not allowed
        if (used[curValue]) continue; // skip

        // Use the value
        used[curValue] = 1;
        //Generate sequence permutation
        perm[index] = curValue + 1;

        //Calculate temperature changes to engine
        int currentTempChange = baseTemp[curValue];
        for (int j = 0; j < index; j++) {
            currentTempChange += respectiveTemp[curValue][perm[j] - 1];
        }

        // Recurse
        permute(used, perm, index + 1, N, baseTemp, respectiveTemp, currentEngineTemp + currentTempChange);

        // Unuse the value
        used[curValue] = 0;
        perm[index] = GARBAGE;
    }

}