#include "LCString.h"

int main(void)
{
    string a = initString();
    addString(&a, "32t8eo/* 3vuhsdueyuduueuq2 ii */asa1");

    unsigned int pos = findString(&a, "@");

    if (pos == NO_FOUND) 
        printf("NO FOUND\n");

    printf("string: %s %u", getString(&a), NO_FOUND);

    free(a.stringContent);

    return 0;
}