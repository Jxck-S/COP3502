#include <stdio.h>
#include <stdlib.h>
#include <string.h>
typedef struct author_t {
    char name[20];
    int birthYear;
    int publishings;
} author_t;
typedef struct book_t {
    char name[20];
    int year;
    int numAuthors;
    struct author_t * authors;
} book_t;
int main() {
    int n_books;
    scanf("%d\n", &n_books);
    //Allocate array for n books
    book_t * books = (book_t *) malloc(sizeof(book_t)*n_books);
    for (int i=0; i < n_books; i++){
        scanf("%s", books[i].name);
        scanf("%d", &books[i].year);
        scanf("%d", &books[i].numAuthors);

        books[i].authors = (author_t *) malloc(books[i].numAuthors*sizeof(author_t));
        for (int publish_i=0; publish_i<books[i].numAuthors; publish_i++){
            scanf("%s", books[i].authors[publish_i].name);
            scanf("%d", &books[i].authors[publish_i].birthYear);
            scanf("%d", &books[i].authors[publish_i].publishings);
        }
    }

    //FREE UP
    for (int i=0; i < n_books; i++){
        free(books[i].authors);
        books[i].authors = NULL;
    }
    free(books);
    books = NULL;
    //Changing author details in one book doesn't change it in the other books, copy of author details
    return 0;
}