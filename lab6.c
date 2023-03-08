#include <stdio.h>
#include <stdlib.h>

typedef struct node_t node_t;

struct node_t
{
    int value;
    node_t *next;
};

node_t *create_node(int value)
{
    node_t *new_node = malloc(sizeof(node_t));
    new_node->value = value;
    new_node->next = NULL;
    return new_node;
}

node_t *insert_head(node_t *head, node_t *new_node)
{
    new_node->next = head;
    return new_node;
}

void print_list(node_t *head)
{
    while (head != NULL)
    {
        printf("%d ", head->value);
        head = head->next;
    }
    printf("\n");
}

node_t *make_random_numbers(int n)
{
    node_t *head = NULL;

    for (int i = 0; i < n; i++)
    {
        head = insert_head(head, create_node(random() % 4));
    }

    return head;
}

node_t *remove_first_value(node_t *head, int value, int *found)
{
    node_t *prev = NULL;
    node_t *curr = head;

    *found = 0;

    while (curr)
    {
        if (curr->value != value)
        {
            prev = curr;
            curr = curr->next;
        }
        else if (prev == NULL)
        {
            // Removing the head
            head = head->next;
            free(curr);
            *found = 1;
            break;
        }
        else
        {
            prev->next = curr->next;
            free(curr);
            *found = 1;
            break;
        }
    }

    return head;
}

node_t *removeAll(node_t *head, int value)
{
    node_t *prev = NULL;
    node_t *curr = head;

    while (curr)
    {
        if (curr->value != value)
        {
            prev = curr;
            curr = curr->next;
        }
        else if (prev == NULL)
        {
            // Removing the head
            head = head->next;
            free(curr);
            curr = head;
        }
        else
        {
            prev->next = curr->next;
            free(curr);
            curr = prev->next;
        }
    }

    return head;
}

int main()
{
    int found;
    node_t *numbers = make_random_numbers(100);
    // numbers = remove_first_value(numbers, 2, &found);
    print_list(numbers);

    for (int i = 0; i < 4; i++)
    {
        printf("removing %d\n", i);
        numbers = removeAll(numbers, i); // Much faster, O(n) (I think...)
        // found = 1;
        // while (found)
        // {
        //     numbers = remove_first_value(numbers, i, found);
        // } Very slow, O(n^2)
        print_list(numbers);
    }
}