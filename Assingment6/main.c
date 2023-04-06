//Assignment 6 Layout
//Jack Sweeney
//4/3/23
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>

typedef struct Stack Stack;
typedef struct StackNode StackNode;

struct StackNode {
    int data;
    StackNode * next;
};

struct Stack {
    StackNode *head;
};

// Prototypes
StackNode * create_stack_node(int data);
StackNode * insert_head(StackNode * head, int data);
StackNode * rm_head(StackNode * head);

Stack * create_stack();
int isEmpty(Stack * stack);
void push(Stack * stack, int data);
void pop(Stack * stack);
int top(Stack * stack);
void del_stack(Stack * stack);

StackNode * create_stack_node(int data){
    StackNode * result = (StackNode *)malloc(sizeof(StackNode));
    result->data = data;
    result->next = NULL;
    return result;
}

// Function to insert a node to the head of a linked list
StackNode * insert_head(StackNode *head, int data){
    StackNode * new_head = create_stack_node(data);
    new_head->next = head;
    return new_head;
}

// Function to remove the head of a given linked list
StackNode * rm_head(StackNode * head){
    if (head == NULL){return NULL;}// When List is empty
    StackNode *new_head = head->next;
    free(head);
    return new_head;
}

// Creates stack with linked list
Stack * create_stack(){
    Stack * result = (Stack *)malloc(sizeof(Stack));
    result->head = NULL;
    return result;
}

// Check if the stack is empty
int isEmpty(Stack * stack) { return stack->head == NULL; }

// Add an element to the top of the stack
void push(Stack * stack, int data){
    stack->head = insert_head(stack->head, data);
}

// Remove element from top of stack
void pop(Stack * stack) { stack->head = rm_head(stack->head); }

// Allows access to top of a stack
int top(Stack * stack){
    assert(stack->head != NULL);
    return stack->head->data;
}

// Frees up stack
void del_stack(Stack * stack){
    while (!isEmpty(stack)) pop(stack);
    free(stack);
}

// Searches for value in stack
int find_data(Stack * cor, int value){
    StackNode * tmp = cor->head;
    while (tmp != NULL)
    {
        if (tmp->data == value)
        {
            return 1;
        }
        tmp = tmp->next;

    }
    return 0;
}
// Calculates the distance between the top of the given stack and the bottom of the stack.
// The distance is defined as the number of elements in the stack
int cor_to_q(Stack * cor){
    StackNode * tmp = cor->head;

    // Starts at 1
    int dist = 0;
    // Iterate through the stack and increment the distance for each element.
    while (tmp != NULL)
    {
        dist++;
        tmp = tmp->next;

    }
    return dist;
}

int main(){
    int num_q = 0;
    int distance = 0;
    Stack * r_stack = create_stack();
    Stack * cor_stack = create_stack();
    // Current room input
    int current_rm;
    scanf("%d", &current_rm);
    push(r_stack, current_rm);
    while (current_rm != -1){
        // Get all the values from user
        scanf("%d", &current_rm);
        push(r_stack, current_rm);
    }
    pop(r_stack);

    StackNode * top_rm;
    StackNode * pos_q;
    StackNode * bot_rm;
    top_rm = r_stack->head;
    pos_q = r_stack->head->next;
    bot_rm = pos_q->next;

    while (!isEmpty(r_stack)){
        if (isEmpty(cor_stack) || find_data(cor_stack, r_stack->head->data) == 0){
            push(cor_stack, r_stack->head->data);
        }
        if (cor_stack->head->next != NULL) {
            if (top_rm->data == cor_stack->head->data){if (pos_q->data == cor_stack->head->next->data){pop(cor_stack);}}
        }
        if (bot_rm != NULL) {
            if (top_rm->data == bot_rm->data){
                num_q++;
                distance += cor_to_q(cor_stack);
                pop(r_stack);
            }
        }
        pop(r_stack);
        top_rm = r_stack->head;
        if (top_rm->next == NULL){
            break;
        } else if (top_rm->next->next == NULL){
            if (isEmpty(cor_stack) || find_data(cor_stack, r_stack->head->data) == 0){push(cor_stack, r_stack->head->data);}
            break;
        }
        pos_q = r_stack->head->next;
        bot_rm = pos_q->next;
    }
    //Final outputs
    printf("%d %d", num_q, distance);
    //Cleanup
    del_stack(r_stack);
    del_stack(cor_stack);

    return 0;
}