# LightweighCString

String operation Library Based on C language.<br>
It makes it easier for you to manipulate strings.
  
# Some Example:

1. Realize a simple storage and reading
```C
#include "LCString.h"

int main(){
        string a = initStr();
        addStr(&a, "hello, world"); // Add a string

        // Stdio has been introduced into the String library,
        // so you don't need to reference it anymore
        // Get the string in a, Print the contents of a
        printf("%s\n", getData(a));

        // Small programs don't need to add this
        // But the big program must add this!!!
        free(a.stringDate);
        a.stringDate = NULL;

        return 0;
}
```

2. Replace the contents of the string
```C
#include "LCString.h"

int main(){
        string a = initStr();
        addStr(&a, "aaabbbccc"); // Add a string

        // Replace the contents of the string
        // Reassign the return value to a
        replace(&a, "a", ""); 

        // Get the string in a, Print the contents of a
        printf("%s\n", getData(a));

        // Small programs don't need to add this
        // But the big program must add this!!!
        free(a.stringDate);
        a.stringDate = NULL;

        return 0;
}
```

3. Find string position
```C
#include "LCString.h"

int main(){
        string a = initStr();
        addStr(&a, "abcd1edguowgue"); // Add a string

        // Find string position
        // Note: the index of the first letter in the string is 0
        int pos = find(a, "1");

        // Print location
        printf("%d\n", pos);

        // Small programs don't need to add this
        // But the big program must add this!!!
        free(a.stringDate);
        a.stringDate = NULL;

        return 0;
}
```

4. Get string length
```C
#include "LCString.h"

int main(){
        string a = initStr();
        addStr(&a, "abcd1edguowgue"); // Add a string

        // Get the string length
        int length = len(a);

        // Print the length
        printf("%d\n", length);

        // Small programs don't need to add this
        // But the big program must add this!!!
        free(a.stringDate);
        a.stringDate = NULL;

        return 0;
}
```
