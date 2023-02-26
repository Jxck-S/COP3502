#include <stdio.h>
#include<stdlib.h>
#include<math.h>
#include<string.h>
//Assignment 2 Jack S Boat Rescue
//MAX hours/pictures, 1 less actually in practice bc notice arrives after hour
#define MAX_HOURS 24
//Maximum max
#define MAX 100
//Minimum min
#define MIN 1

//Prototype for guess function
int calc_gu(int max1, int max2, int org_arr[max1+1][max2+1]);
//Actual guess function
int calc_gu(int max1, int max2, int org_arr[max1+1][max2+1]){
    int modified_arr[(max1+1)*(max2+1)+2];
    int current = 0;
    //Inital moodified array
    for(int outer_i = 0; outer_i <= max1; outer_i++){
        for(int inner_i=0; inner_i<=max2; inner_i++){
            if(org_arr[outer_i][inner_i] != -1){
                modified_arr[current] = org_arr[outer_i][inner_i];
                current++;
            }
        }
    }

    //Finialized modified array
    for(int outer_i = 0; outer_i < current; outer_i++){
        for(int inner_i = outer_i; inner_i < current; inner_i++){
            if(modified_arr[outer_i] > modified_arr[inner_i]){
                int replace = modified_arr[outer_i];
                modified_arr[outer_i] = modified_arr[inner_i];
                modified_arr[inner_i] = replace;
            }
        }
    }

    if(current == 1) return modified_arr[0];

    //When no remainder
    else if(current % 2 == 0) return modified_arr[(current/2) - 1];

    else return modified_arr[((current+1)/2) - 1];

}

int main(){
    int mx_spd, mx_loc;
    //Load in Max speed and location
    scanf("%d %d", &mx_spd, &mx_loc);

    //2d array for possible locations as suggested
    int bo_locs[mx_loc + 1][mx_spd + 1];

    for(int outer_i= 0; outer_i <= mx_loc; outer_i++){
        for(int inner_i= 0; inner_i <= mx_spd; inner_i++){
            bo_locs[outer_i][inner_i] = outer_i + inner_i;
        }
    }


    int pic_num = 0;
    //Used to determine how many more to go
    int locs = (mx_loc+1)*(mx_spd+1);
    char inp[10];
    //Loop to take pictures until max
    while(pic_num < MAX_HOURS){
        int guess;
        guess = calc_gu(mx_loc,mx_spd, bo_locs);
        //gives the boats location
        if(locs == 1){
            printf("! %d\n", guess);
            fflush(stdout);
            break;
        }
        //gives our guess and check input for wake, no wake or boat
        else {
            printf("? %d\n", guess);
            fflush(stdout);
            scanf("%s", inp);
        }
        //When wake picture is detected
        if(strcmp(inp, "Wake") == 0){
            for(int outer_i= 0; outer_i <= mx_loc; outer_i++){
                for(int inner_i= 0; inner_i <= mx_spd; inner_i++){
                    //Remove locations that arent possible ie setting it to -1
                    if(bo_locs[outer_i][inner_i] <= guess && !(bo_locs[outer_i][inner_i] == -1)){
                        bo_locs[outer_i][inner_i] = -1;
                        locs--;
                    }
                    else if(!(bo_locs[outer_i][inner_i] == -1)){
                        bo_locs[outer_i][inner_i] = bo_locs[outer_i][inner_i] + inner_i;
                    }
                }
            }
        }
        //When No wake picture is detected
        else if(strcmp(inp, "No") == 0){
            scanf("%s", inp);
            for(int outer_i= 0; outer_i <= mx_loc; outer_i++){
                for(int inner_i= 0; inner_i <= mx_spd; inner_i++){
                    //Removing non posssibles again
                    if(bo_locs[outer_i][inner_i] >= guess&& !(bo_locs[outer_i][inner_i] == -1)){
                        bo_locs[outer_i][inner_i] = -1;
                        locs--;
                    }

                    else if (!(bo_locs[outer_i][inner_i] == -1)){
                        bo_locs[outer_i][inner_i] = bo_locs[outer_i][inner_i] + inner_i;
                    }
                }
            }
        }
        //When Boat is detected in picture
        else if(strcmp(inp, "Boat!") == 0){
            for(int outer_i= 0; outer_i <= mx_loc; outer_i++){
                for(int inner_i= 0; inner_i <= mx_spd; inner_i++){
                    if(bo_locs[outer_i][inner_i] != guess && !(bo_locs[outer_i][inner_i] == -1)){
                        bo_locs[outer_i][inner_i] = -1;
                        locs--;
                    }

                    else if (!(bo_locs[outer_i][inner_i] == -1)){
                        bo_locs[outer_i][inner_i] = bo_locs[outer_i][inner_i] + inner_i;
                    }
                }
            }
        }
        pic_num++;
    }
    return 0;
}
