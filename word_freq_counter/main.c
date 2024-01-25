
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "hashtable.h"

int main()
{

    FILE *in = fopen("book.txt", "r");
    hashtable *hash = createtable(50000);
    struct node *node = NULL;
    char word[100];
    int length = 0;

    while (1)
    {
        if (fscanf(in, "%s", word) != 1)
            break;
        length = strlen(word) - 1;
        if (ispunct(word[length]))
            *(word + length) = '\0';
        if (strlen(word) > 0)
            node = add(hash, word, 1);
        node->frequency++;
    }
    fclose(in);

    mostfrequent(hash, 250);
    freetable(hash);
    return 0;
}
