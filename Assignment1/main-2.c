#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define NAME_LEN 20
#define DEFAULT_CAP 10
typedef struct Boat Boat;
typedef struct ArrayList ArrayList;
struct Boat {
    int start_x, start_y, delta_x, delta_y, start_time;
    char name[NAME_LEN + 1];
};
struct ArrayList {
    struct Boat * array;
    int size, capacity;
};
//Creates ArrayList of Default Capacity
ArrayList * createList()
{
    ArrayList * list_ref = (ArrayList *)
            malloc(DEFAULT_CAP * sizeof(ArrayList));

    //initialize the members of the list
    list_ref->array = (Boat *) malloc(sizeof(Boat) * DEFAULT_CAP);
    list_ref->size = 0;
    list_ref->capacity = DEFAULT_CAP;

    return list_ref;
}
//Frees up array inside, and its self
void cleanList(ArrayList * list)
{
    if (list->array != NULL){
        free(list->array);
    }
    free(list);
}
// Given a pointer to a list initialize the list
// List / pointers of arraylists
void initArrayList(ArrayList * list, int size){
    for (int i= 0; i < size; i++){
        list[i].array = NULL;
        list[i].size = 0;
        list[i].capacity = 0;
    }
}
// Given a list and a boat to add to it, add the boat to the end
// of the list
// Expand the list if necessary
void appendToList(ArrayList * list, Boat newBoat){
    //check if list is full
    if (list->size == list->capacity){
        //When list hasn't been used yet setup
        if (list->capacity == 0){
            list->capacity=DEFAULT_CAP;
        }
        else {
            list->capacity *= 2;
        }
        list->array = (Boat *) realloc(list->array, list->capacity * sizeof(Boat));
    }
    list->size++;
    list->array[list->size -1] = newBoat;
}

// Return the number of boats in the storm and the list is modified
int query(int strm_x, int strm_y, int storm_max_x, int storm_max_y,
          int world_width, int world_height,
          ArrayList * list, int cur_time, int should_print) {
    int total_in_storm = 0;
    for (int ship_i=0; ship_i<list->size; ship_i++){
        Boat current_bo = list->array[ship_i];
        int total_move;
        int in_storm = 1;
        //Moving in cols    
        if (current_bo.delta_y != 0){
            //Calculate current y based off time
            total_move = current_bo.delta_y * (cur_time-current_bo.start_time);
            int y_pos = current_bo.start_y +(total_move % (world_height-1));
            //Storm wrap for x check, if needed
            if (storm_max_x > (world_width-1)){
                int storm_second_max_x = storm_max_x % (world_width);
                //Checks out of storm
                if (current_bo.start_x>storm_second_max_x && current_bo.start_x<strm_x){
                    in_storm = 0;
                }
            }
            //When wrap is not needed for x of storm, checks out of
            else if (current_bo.start_x < strm_x || current_bo.start_x > storm_max_x){
                in_storm = 0;
            }

            //Storm wrap for y check, if needed
            if (storm_max_y > (world_height-1)){
                int storm_second_max_y = storm_max_y % (world_height);
                //Checks out of storm
                if (y_pos>storm_second_max_y && y_pos<strm_y){
                    in_storm = 0;
                }
            }
            //When wrap is not needed for y of storm
            else if (y_pos < strm_y || y_pos > storm_max_y){
                in_storm = 0;
            }


        }
        //Moving in rows
        else if (current_bo.delta_x != 0){
            //Calculate current x based off time
            total_move = current_bo.delta_x * (cur_time-current_bo.start_time);
            int x_pos = current_bo.start_x + (total_move % (world_width-1));
            //Storm wrap for x check, if needed
            if (storm_max_x > (world_width-1)){
                int storm_second_max_x = storm_max_x % (world_width);
                if (x_pos>storm_second_max_x && x_pos<strm_x){
                    in_storm = 0;
                }
            }
            //When wrap is not needed for x of storm
            else if (x_pos < strm_x || x_pos > storm_max_x){
                in_storm = 0;
            }
            //Storm wrap for y check, if needed
            if (storm_max_y > (world_height-1)){
                int storm_second_max_y = storm_max_y % (world_height);
                if (current_bo.start_y>storm_second_max_y && current_bo.start_y<strm_y){
                    in_storm = 0;
                }
            }
            //When wrap is not needed for y of storm
            else if (current_bo.start_y < strm_y || current_bo.start_y > storm_max_y){
                in_storm = 0;
            }
        }
        if (in_storm == 1){
            total_in_storm++;
        }
            //NULL out ship name that isn't in storm, so it doesn't get printed
        else {
            list->array[ship_i].name[0] = '\0';
        }
    }
    if (should_print){
        printf("\n%d", total_in_storm);
    }

}
int main() {
    char garbage[5];
    //Take in Width/height of grid
    int gr_width, gr_height;
    int current_time = 0; //Current time is in minutes
    //Get grid Size
    scanf("%d %d", &gr_width, &gr_height);
    fgets(garbage, 5, stdin);
    //Create Array of ArrayLists for cols and rows, and make them NULL
    ArrayList * cols = (ArrayList *) malloc(sizeof(ArrayList)*gr_width);
    initArrayList(cols, gr_width);
    ArrayList * rows = (ArrayList *) malloc(sizeof(ArrayList)*gr_height);
    initArrayList(rows, gr_height);
    int menu_choice = 0;
    while (menu_choice != 4){
        scanf("%d", &menu_choice);
        switch (menu_choice){
            //Load in a boat like (4 14 L BoatOne)
            case 1:{
                int x, y;
                char direction;
                char name[NAME_LEN+1];
                Boat bo;
                scanf(" %d %d %c %s", &bo.start_x, &bo.start_y, &direction, name);
                strcpy(bo.name, name);
                bo.start_time = current_time;
                bo.start_y--;
                bo.start_x--;
                bo.delta_x = 0;
                bo.delta_y = 0;
                switch (direction) {
                    //UP Y goes up 1 every min
                    case 'U': {
                        bo.delta_y = 1;
                        break;
                    }
                    //DOWN Y goes down 1 every min
                    case 'D': {
                        bo.delta_y = -1;
                        break;
                    }
                    //Right X goes right 1 every min
                    case 'R': {
                        bo.delta_x = 1;
                        break;
                    }
                    //Left X goes left
                    case 'L': {
                        bo.delta_x = -1;
                        break;
                    }
                }
                //Add to columns if Y is changing
                if (bo.delta_y != 0) {
                    appendToList(&cols[bo.start_x], bo);
                }
                //Add to rows if X is changing
                else if (bo.delta_x != 0){
                    appendToList(&rows[bo.start_y], bo);
                }

                break;
            }
            // Pass T time
            case 2:{
                int t;
                scanf(" %d", &t);
                current_time += t;
                break;
            }
            //Check storm  x y w h // Also storm warning output
            case 3:{
                int x, y, storm_w, storm_h;
                scanf(" %d %d %d %d", &x, &y, &storm_w, &storm_h);
                int x_zeroed = x -1, y_zeroed = y -1;
                int storm_max_x = x_zeroed + (storm_w-1), storm_max_y = y_zeroed + (storm_h-1);
                ArrayList * considering_ships = createList();
                //Check/collect ships in these cols
                for (int current_col= x_zeroed; current_col <= storm_max_x; current_col++){
                    //Converts/wraps storm over
                    int current_col_wrapped = current_col % gr_width;
                    if (cols[current_col_wrapped].array != NULL){
                        for (int ship_i=0; ship_i<cols[current_col_wrapped].size; ship_i++){
                            appendToList(considering_ships, cols[current_col_wrapped].array[ship_i]);
                        }
                    }
                }
                //Check/collect ships in these rows
                for (int current_row= y_zeroed; current_row <= storm_max_y; current_row++){
                    //Converts/wraps storm over
                    int current_row_wrapped = current_row % gr_height;
                    if (rows[current_row_wrapped].array != NULL){
                        for (int ship_i=0; ship_i<rows[current_row_wrapped].size; ship_i++){
                            appendToList(considering_ships, rows[current_row_wrapped].array[ship_i]);
                        }
                    }
                }
                //Checks for ships actually in storm, considering ships gets modified, if a ship isn't in the storm its name will be removed
                int num_in_storm = query(x_zeroed, y_zeroed, storm_max_x, storm_max_y, gr_width, gr_height, considering_ships, current_time, 1);
                if (num_in_storm != 0 ){
                    for (int current_ship = 0; current_ship<considering_ships->size; current_ship++){
                        if (considering_ships->array[current_ship].name[0] != '\0'){
                            printf("\n%s", considering_ships->array[current_ship].name);
                        }
                    }
                }
                cleanList(considering_ships);
                break;
            }
            //EXIT
            case 4:{
                //Free ArrayLists inside the rows array
                for (int i= 0; i < gr_height; i++){
                    free(rows[i].array);
                }
                //Free actual rows array
                free(rows);
                //Free ArrayLists inside the cols array
                for (int i= 0; i < gr_width; i++){
                    free(cols[i].array);
                }
                //Free actual cols array
                free(cols);
                break;
            }
        }
        fgets(garbage, 5, stdin);
    }
    return 0;
}
