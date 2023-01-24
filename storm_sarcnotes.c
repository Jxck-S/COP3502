// January 20th, 2023 10:30 AM - 11:20 AM
// Spring COP3502C
// SI Leader: Jay P.
// THANK YOU JAY!!!!!

#include <stdio.h>
#include <stdlib.h>
#define NAME_LEN

// The array list is an array that holds pointers to other arrays.

typedef struct Boat Boat;
typedef struct ArrayList ArrayList;
struct Boat {
  int start_x, start_y, delta_x, delta_y, start_time;
  char name[NAME_LEN + 1];
};
// start_x and start_y will be the position of the boats on
// the x- and y-axes.
// delta_x and delta_y will be the difference of distance
// in the x- and y-direction.
struct ArrayList {
  struct Boat *array;
  int size, capacity;
};
// Given a point to a list initialize the list
void initArrayList(ArrayList *list) {
  list = (ArrayList *)malloc(sizeof(ArrayList) * 10);
  list->array = (struct Boat *)malloc(sizeof(struct Boat) * 1);
  list->size = 10;
  list->capacity = 10;
}
// Given a list and a boat to add to it, add the boat to the end
// of the list
// Expand the list if necessary

void appendToList(ArrayList *list, Boat newBoat) {
  if (list->capacity == 0) {
    list = (ArrayList *)realloc(list, sizeof(ArrayList) * 10);
  }
}
// Given
// * the x and y location of a storm,
// * the dimensions of the storm,
// * the dimensions of the world,
// * the list of ships under consideration,
// * the time change since the beginning of the program,
// * and a flag whether boats should be printed or not
// Return the number of boats in the storm and the list
// Print the names of the boats if the should_print flag is non-zero
int query(int x, int y, int storm_width, int storm_height, int world_width,
          int world_height, ArrayList *list, int cur_time, int should_print);
// The main function
int main();
{
  FILE *ifp;
  int W, H;
  int x, y;
  char d;
  char name[20];
  int choice;
  Boat *b;

  b = (Boat *)malloc(sizeof(Boat));

  ifp = fopen("input.txt", "r");

  fscanf(ifp, "%d", &W);
  fscanf(ifp, "%d", &H);

  while (W <= 20 || W >= 500000 || H <= 20 || H >= 500000) {
    printf("Wrong input value. Please scan again");
  }

  scanf("%d ", 

    // Why an array list for each row and col
  switch(choice)
    {
  case 1: {
    scanf("%d %d %c %s", &choice, &x, &y, &d, n);
    break;
  }
  case 2: {
    scanf("%d", &t);
    break;
  }
    }

  fscanf(ifp, "%d", &choice);
// A switch choice will allow the user to choose the direction. //

  switch(choice)
    {
  case 1: {
    fscanf(ifp, "%d", &x);
    fscanf(ifp, "%d", &y);
    fscanf(ifp, "%c", &d);
    fscanf(ifp, "%s", &n);

    b.start_x = x b.start_y = y

        switch (d) {
    case 'U': {
      b.delta_y = 1;
      break;
    }
    case 'R': {
      b.delta_x = 1;
      break;
    }
    case 'D': {
      b.delta_y = -1;
      break;
    }
    case 'L': {
      b.delta_x = -1;
      break;
    }
    default: {
      break;
    }

      // 3 more cases for each direction
    }

    strcpy(b.name, n);

    break;
  }
  case 2: {
    break;
  }
  case 3: {
    break;
  }
  case 4: {
    break;
  }
  default: {
    break;
  }
    }
}
// appendToList() comments
// Check if the list is full
// Expand the list
// Add the boat to the end of the list
// Update the list’s size
// query() comments
// Create and initialize the answer
// Loop through all the boats in the list
// Get the current boat
// Get the current location of the boat (based on time)
// Find the offset of the boat from the storm
// Wrap the offsets around the world if necessary (modulo)
// Check if the boat is in the storm by using the offset
// main() comments
// Read the size of the world
// Create the array of array lists for x and y world segments
// Loop through and initialize all the array lists from the two
//    arrays
// Initialize the current time
// Read the first command
// Loop until the exit command is given
// Determine the command type
// ADD COMMAND
// Create a static boat
// Read in the boat values (be careful with the direction)
// Convert the x and y to zero indexed values
// Initialize the delta x and y based on the direction
// Initialize the time the boat arrived
// Check if boat is Left/Right VS Up/Down
// Add boat to the x’s
// Else
// Add boat to the y’s
// TIME COMMAND
// Update the current time
// STORM COMMAND
// Read in the storm information
// Convert the x and y to zero indexed values
// Loop through and determine how many ships will be
// affected
// Update total by querying this particular row list
// Update total by querying this particular column list
// Print the total number of affected ships
// Loop through and print affected ships
// Print the by querying this particular row list
// Print the by querying this particular column list
// Read in the next command
// Clean up memory
// Exit successfully