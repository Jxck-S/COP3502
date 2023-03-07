#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>
//Assignment 4: Tugboat Trouble
//Jack Sweeney 3/3/23

//Boat Struct
typedef struct tugBoat tugboat;
struct tugBoat {
  char name[20];
  long long int x, y;
  long long int x_mod, y_mod;
  long long int dist;
  long long int dp;
};

//Creating a new tug instance
void create_tug(tugboat *tug, int x, int y, int ship_x, int ship_y) {
  scanf("%lld %lld %s", &tug->x, &tug->y, tug->name);
  tug->x_mod = tug->x - ship_x;
  tug->y_mod = tug->y - ship_y;
  tug->dist = (long)pow((tug->x_mod), 2) + (long)pow((tug->y_mod), 2);
  tug->dp = (tug->x_mod * x) + (tug->y_mod * y);
}

void m_sort(tugboat *inital_tugs, int size) {
  //Don't sort if one item.
  if (size <= 1)
    return;

  // Splitting the array
  int l_size = size / 2;
  int r_size = size - l_size;
  tugboat *l_half = inital_tugs;
  tugboat *r_half = &inital_tugs[l_size];

  // Sort each half
  m_sort(l_half, l_size);
  m_sort(r_half, r_size);

  tugboat *sorted = (tugboat *) malloc(sizeof(tugboat) * size);
  //Merging the two sorted arrays
  int l_count = 0;
  int r_count = 0;
  for (int i = 0; i < size; i++) {

    //When left is empty
    if (l_count == l_size) {
      sorted[i] = r_half[r_count];
      r_count++;
    }

    //When Right is empty
    else if (r_count == r_size) {
      sorted[i] = l_half[l_count];
      l_count++;
    }

    //Left side is less
    else if (l_half[l_count].dp < r_half[r_count].dp) {
      sorted[i] = l_half[l_count];
      l_count++;
    }

    //Size/dp is equal
    else if (l_half[l_count].dp == r_half[r_count].dp) {

      if (l_half[l_count].dist < r_half[r_count].dist) {
        sorted[i] = l_half[l_count];
        l_count++;
      }
      //Equal distance for boats
      else if (l_half[l_count].dist == r_half[r_count].dist) {

        if (strcmp(l_half[l_count].name, r_half[r_count].name) < 0) {
          sorted[i] = l_half[l_count];
        }

        else {sorted[i] = r_half[r_count];}
      }

      else {
        sorted[i] = r_half[r_count];
        r_count++;
      }
    }
    // Second was equal or smaller
    else {
      sorted[i] = r_half[r_count];
      r_count++;
    }
  }


  // Copy results
  for (int i = 0; i < size; i++)
    inital_tugs[i] = sorted[i];
  free(sorted);
}

int main(void) {
  int ship_x, ship_y, harb_x, harb_y;
  //Load in main world info
  scanf("%d %d %d %d", &ship_x, &ship_y, &harb_x, &harb_y);

  int boat_num;
  //Load count of boats
  scanf("%d", &boat_num);
  tugboat inital_tugs[boat_num];
  tugboat final[boat_num];
  //Load in tugs using tug creation//scanf
  for (int i = 0; i < boat_num; i++) { create_tug(&inital_tugs[i], (harb_x - ship_x), (harb_y - ship_y), ship_x, ship_y);}
  //Sort the entire array
  m_sort(inital_tugs, boat_num);
  //Calculate the total dot product
  long long int dp = (long)pow((harb_x - ship_x), 2) + (long)pow((harb_y - ship_y), 2);
  tugboat last;
  int count = 0;
  for (int i = 0; i < boat_num; i++) {
    //DP is equal
    if (inital_tugs[i].dp == last.dp && i != 0) {
      last = inital_tugs[i];
      continue;
    }
    //Negative DP
    if (inital_tugs[i].dp <= 0) {
      last = inital_tugs[i];
      continue;
    }
    //Tug DP is larger
    if (inital_tugs[i].dp > dp) {
      last = inital_tugs[i];
      continue;
    }

    final[count] = inital_tugs[i];
    count++;
    last = inital_tugs[i];
  }

  //Print Final output
  //Count
  printf("%d\n", count);
  //Ship names
  for (int i = 0; i < count; i++) {
    printf("%s\n", final[i].name);
  }
  return 0;
}