#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "hashtable.h"
int hashcode(char *);

void freenode(struct node *);

struct node *add(hashtable *h, char *key, int freq)
{
    struct node *newnode;
    int index = hashcode(key) % h->tablesize;
    struct node *current = h->table[index];

    while (current != NULL)
    {
        if (strcmp(key, current->key) == 0)
            return current;
        current = current->next;
    }

    newnode = nalloc(key, freq);
    newnode->next = h->table[index];
    h->table[index] = newnode;
    h->currentsize = h->currentsize + 1;
    return newnode;
}

bool contains(hashtable *h, char *key)
{
    int index = hashcode(key) % h->tablesize;
    struct node *current = h->table[index];

    while (current != NULL)
    {
        if (strcmp(key, current->key) == 0)
            return true;
        current = current->next;
    }
    return false;
}

struct node *getnode(hashtable *h, char *key)
{
    int index = hashcode(key) % h->tablesize;
    struct node *current = h->table[index];

    while (current != NULL)
    {
        if (strcmp(key, current->key) == 0)
            return current;
        current = current->next;
    }
    return NULL;
}

void deletenode(hashtable *h, char *key)
{
    int index = hashcode(key) % h->tablesize;
    struct node *current = h->table[index];
    struct node *previous = NULL;

    if (current == NULL)
        return;

    while (current != NULL && strcmp(key, current->key) != 0)
    {
        previous = current;
        current = current->next;
    }

    if (current == NULL)
        return;

    else if (current == h->table[index])
        h->table[index] = current->next;

    else if (current->next == NULL)
        previous->next = NULL;

    else
        previous->next = current->next;

    freenode(current);
}

void mostfrequent(hashtable *h, int freq)
{
    struct node *current = NULL;
    int i;
    printf("\n  Word       Frequency\n");
    printf("  --------------------\n");
    for (i = 0; i < h->tablesize; i++)
    {
        current = h->table[i];
        while (current != NULL)
        {
            if (current->frequency > freq)
                printf("  %-14s %d\n", current->key, current->frequency);
            current = current->next;
        }
    }
}

int hashcode(char *key)
{
    int i, hash = 7;
    int length = strlen(key);

    for (i = 0; i < length; i++)
        hash = (hash * 31) + *(key + i);
    return hash & 0x7FFFFFFF;
}

struct hashtable *createtable(int size)
{
    int i;
    if (size < 1)
        return NULL;
    hashtable *table = (hashtable *)malloc(sizeof(hashtable));
    table->table = (struct node **)malloc(sizeof(struct node *) * size);

    if (table != NULL)
    {
        table->currentsize = 0;
        table->tablesize = size;
    }

    for (i = 0; i < size; i++)
        table->table[i] = NULL;
    return table;
}

struct node *nalloc(char *key, int freq)
{
    struct node *p = (struct node *)malloc(sizeof(struct node));

    if (p != NULL)
    {
        p->key = strdup(key);
        p->frequency = freq;
        p->next = NULL;
    }
    return p;
}

void freenode(struct node *node)
{
    free(node->key);
    free(node);
}

void freetable(hashtable *h)
{
    struct node *current = NULL;
    int i;

    for (i = 0; i < h->tablesize; i++)
    {
        current = h->table[i];
        if (current == NULL)
            continue;

        while (current->next != NULL)
        {
            h->table[i] = h->table[i]->next;
            freenode(current);
            current = h->table[i];
        }
        freenode(current);
    }

    free(h->table);
    free(h);
}
