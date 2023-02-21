#include <stdio.h>
#include <stdlib.h>
//Assignment 3 Engine Shutdown
//Jack Sweeney 2/17/23

//Input of actions only goes up to 11, this array is tested for final output
int max_tmp_loss[11];
//For detecting the max temp over iter
int max_tmp_sn = 0;

//Permutation function prototype
void perm_temps(int * tested, int * cur_seq, int idx, int actions_count, int * start_temp, int ** sep_temp, int cur_tmp);
//Actual perm function testing temps and order to find the max temp loss
void perm_temps(int * tested, int * cur_seq, int idx, int actions_count, int * start_temp, int ** sep_temp, int cur_tmp) {
    // base
    if (actions_count == idx) {
        if (cur_tmp < max_tmp_sn) {
            max_tmp_sn = cur_tmp;
            for (int i = 0; i < actions_count; i++) {
                max_tmp_loss[i] = cur_seq[i];
            }
        }
        return;
    }
    // Other cases after base
    for (int current_i = 0; current_i < actions_count; current_i++) {
        // Check if the value has not already been tested
        if (!tested[current_i]){
            // Mark the value
            tested[current_i] = 1;
            cur_seq[idx] = current_i + 1;

            // Actual engine temp check
            int cur_change = start_temp[current_i];
            for (int sec_it = 0; sec_it < idx; sec_it++) {
                cur_change += sep_temp[current_i][cur_seq[sec_it] - 1];
            }

            // Calling it Again
            perm_temps(tested, cur_seq, ++idx, actions_count, start_temp, sep_temp, cur_tmp+cur_change);

            // Set the value as already tested
            tested[current_i] = 0;
            cur_seq[--idx] = -1;
        }
    }
}

int main(){
    int action_count;
    //Get the num of actions
    scanf("%d", &action_count);
    int cur_seq[action_count];
    int tested[action_count];

    for(int i = 0; i < action_count; i++){
        cur_seq[i] = -1;
        tested[i] = 0;
    }

    //Starting temps and actions array, where each is loaded in
    int start_temp[action_count];
    for(int i = 0; i < action_count; i++){ scanf("%d", &start_temp[i]); }
    //Double for order of action/temp
    int ** sep_temp = (int **) malloc(action_count * sizeof(int *));
    for(int i = 0; i < action_count; i++){
        sep_temp[i] = (int *) malloc(action_count * sizeof(int *));
    }

    //Get the temps for each action
    for(int outer = 0; outer < action_count; outer++){
        for(int inner = 0; inner < action_count; inner++){
            scanf("%d", &sep_temp[outer][inner]);
        }
    }
    perm_temps(tested, cur_seq, 0, action_count, start_temp, sep_temp, 0);
    //The best part the output
    for(int i = 0; i < action_count; i++){ printf("%d ", max_tmp_loss[i]); }
    printf("\n");

    //Freeing memory in the heap
    //Inner objects first
    for(int i = 0; i < action_count; i++){ free(sep_temp[i]); }
    free(sep_temp);
    return 0;
}