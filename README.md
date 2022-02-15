# LightweighCString
### Introduction:<br>
A String library implemented in C<br>
It allows you to easily manipulate strings<br>
(I really don't like the string Library of C language. Is there anyone like me?)<br>
<br>
### Explain:<br>
This is a library I wrote when developing Tranquility programming language. The reason is that it's too troublesome to use C string when developing programming language<br>
I think the operation is very simple. A few sentences of code can solve the problem of operating strings. Personally, it is very convenient :)<br>
<br>
#### Main functions of the Library:<br>
- Initialize String<br>
- Add new string to string<br>
- Add new char to string<br>
- Replace the specified content in the original string with another string<br>
- Used to locate a string in the original data to determine its location<br>
- Clear the contents of the String class<br>
- Get string data<br>
- Get string length<br>
<br><br>
### Some Example:<br>
1. Realize a simple storage and reading<br>
```C
#include "LCString.h"

int main(){
        string a = initStr();
        a = addStr(a, "hello, world"); // Add a string

        // Stdio has been introduced into the String library,
        // so you don't need to reference it anymore
	// Get the string in a, Print the contents of a
        printf("%s\n", getData(a));
	
	// Small programs don't need to add this
	// But the big program must add this!!!
	free(a.stringData);
	
	return 0;
}
```
<br><br>
2. Replace the contents of the string<br>
```C
#include "LCString.h"

int main(){
        string a = initStr();
        a = addStr(a, "aaabbbccc"); // Add a string

        // Replace the contents of the string
        // Reassign the return value to a
        a = replace(a, "a", ""); 

        // Get the string in a, Print the contents of a
        printf("%s\n", getData(a));
	
	// Small programs don't need to add this
	// But the big program must add this!!!
	free(a.stringData);
	
	return 0;
}
```
<br><br>
3. Find string position<br>
```C
#include "LCString.h"

int main(){
        string a = initStr();
        a = addStr(a, "abcd1edguowgue"); // Add a string
        
        // Find string position
        // Note: the index of the first letter in the string is 0
        int pos = find(a, "1");

        // Print location
        printf("%d\n", pos);
	
	// Small programs don't need to add this
	// But the big program must add this!!!
	free(a.stringData);
	
	return 0;
}
```
<br><br>
4. Get string length
```C
#include "LCString.h"

int main(){
        string a = initStr();
        a = addStr(a, "abcd1edguowgue"); // Add a string
        
        // Get the string length
        int length = len(a);

        // Print the length
        printf("%d\n", length);
	
	// Small programs don't need to add this
	// But the big program must add this!!!
	free(a.stringData);
	
	return 0;
}
```
<br><br>

### Feedback:<br>
If you have any questions, you can send an email to robotsteve@163.com
