#include "LCString.h"

int main(void)
{
    string a = initString();
    addString(&a, "helloworld123");

    unsigned int pos = findString(&a, "@");

    if (pos == NO_FOUND) 
        printf("NO FOUND\n");

    replaceString(&a, "owo", "OWO");
    
    printf("string: %s %u", getString(&a), NO_FOUND);

    free(a.stringContent);

    return 0;
}