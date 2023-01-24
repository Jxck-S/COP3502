//This program reads in integers until an END-ing value is given
//The program then prints the list and cleans up any dynamic memory

#include <stdio.h>
#include <stdlib.h>

//the defined values
#define END -1
#define DEFAULT_CAP 10 //Always use a positive value around the smallest value you may need

//Struct definitions
typedef struct ArrayList ArrayList;
struct ArrayList {
    int * arr; // the array
    int size; // number of items in the array
    int cap; // number of slots in the array
};

//Prototypes
ArrayList * createList();
void append(ArrayList * list, int value);
void cleanList(ArrayList * list);

//The main function
int main()
{
    ArrayList * list = createList();

    //Read until end is given
    int value;
    scanf("%d", &value);
    while (value != END)
    {
        append(list, value);
        scanf("%d", &value);
    }

    //Print the list
    for (int i = 0; i < list->size; i++) //If you have a pointer in a struct use the '->' notation to dereference it
    {
        printf("%d ", list->arr[i]);
    }

    //Clean up the dynamic memory
    cleanList(list);

    //Exit program
    return 0;
}

ArrayList * createList()
{
    ArrayList * list_ref = (ArrayList *)
        malloc(1 * sizeof(ArrayList));
        
    //initialize the three members of the list
    list_ref->arr = (int *) malloc(sizeof(int) * DEFAULT_CAP);
    list_ref->size = 0;
    list_ref->cap = DEFAULT_CAP;

    return list_ref;
}

void append(ArrayList * list, int value)
{
    //check if list is full
    if (list->size == list->cap)
    {
        list->cap *=2;
        list->arr = (int *) realloc(list->arr, list->cap * sizeof(int));
    }
    list->size++;
    list->arr[list->size -1] = value;
}

void cleanList(ArrayList * list)
{
    free(list->arr);
    free(list);
}