#ifndef HASHTABLE_H_INCLUDED
#define HASHTABLE_H_INCLUDED
#include <stdbool.h>
struct node {
    char *key;
    int frequency;
    struct node *next;
};

struct hashtable {
    struct node **table;
    int currentsize;
    int tablesize;
};

typedef struct hashtable hashtable;

struct node * add(hashtable *, char *, int);

bool contains(hashtable *, char *);

struct node * getnode(hashtable *, char *);

void deletenode(hashtable *, char *);

void mostfrequent(hashtable *, int);

hashtable * createtable(int);

struct node * nalloc(char *, int);

void freetable(hashtable *);

#endif 