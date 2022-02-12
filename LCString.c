#include "LCString.h"

/* String Type: 
 * The string of C is too cumbersome,
 * So I wrote a string operation module,
 * This allows you to quickly manipulate string.
 *
 * Functions: initStr, addStr, getData, find ,replace, len
*/

string initStr(){
	/* Initialize the String */
	string str;
	
	str.length = 1; // Set length of string
	str.stringData = (char*)malloc(str.length*sizeof(char)); // Allocate dynamic memory
	if(!str.stringData){
		// Report Error
		printf("OSError: An unexpected error occurred at runtime!\n");
		exit(0);
	}
	str.stringData[0] = '\0'; // End symbol

	return str;
}

string addChar(string str, char elem){
	/* Add new char to the String */
	str.stringData = (char*)realloc(str.stringData, (str.length+1)*sizeof(char)); // Reallocate
	if(!str.stringData){
		// Report Error
		printf("OSError: An unexpected error occurred at runtime!\n");
		exit(0);
	}
	
	str.stringData[str.length-1] = elem;
	str.stringData[str.length]   = '\0';
	
	str.length ++; // New length
	
	return str;
}

string addStr(string str, char* elem){
	/* Add new the String to the String */
	while(*elem != '\0'){
		// Add characters to the target string one by one
		str = addChar(str, *elem);

		// Traversal the string
		*elem ++;
	}

	return str;
}

string strCopy(string str){
	/* Copy a string object */
	string newstr = initStr();
	newstr = addStr(newstr, str.stringData);
	
	return newstr;
}

char* getData(string str){
	/* Get the string data */
	return str.stringData;
}

int find(string Str, char* findStr){
	/* Used to locate a string in the original data to determine its location */
	char* str = Str.stringData;
	char* alternate = findStr;

	// The location of found. 
	// When it is -1: No find
	// When it is another value: found, and at this time it is the location of the record
	int found = -1; 
	printf("=====================================================\n");
	printf("Check(debug): (findStr: %s)\n", findStr);
	for(int pos=0; *str!='\0'; *str++){
		printf("Check(debug): (pos: %d), (*str: %c), (str: %s)\n", pos, *str, str);
		if(*str == *findStr){
			found = pos; // Record the position first
			for(; *findStr!='\0'; *findStr ++){
				// One character is different
				// Set to "Not found" and reset
				if(*str != *findStr || *findStr == '\0'){
					found = -1; findStr = alternate;
					break;
				}
				*str ++;
			}
		}
		pos ++;
	}
	printf("Check(debug): (found: %d)\n", found);
	printf("=====================================================\n");

	return found;
}

string replace(string str, char* elem, char* newelem){
	/* Replace the specified content in the original string with another string */
	// Define a new String object
	string newString  = initStr();
	// Temporary string
	string tempString = initStr();
	
	// New temporary variable
	string temp    = str;
	char* tempElem = elem;
	
	// The position of the string to replace
	int pos = find(temp, elem);
	printf("foundPos: %s - %d -%s-\n", getData(str), pos, elem);
	
	while(pos != -1){
		// The old string
		char* oldStr = temp.stringData;

		// Collects the characters before the target string
		for(;pos>0; pos--){
			tempString = addChar(tempString, *oldStr);
			*oldStr ++;
		}
		newString  = addStr(newString, tempString.stringData);
		newString  = addStr(newString, newelem);
		// Restore the original value of the variable
		tempString = clearStr(tempString); 
		// Delete target string(The string to retrieve)
		for(;*elem!='\0';*elem++) oldStr ++;	
		
		for(;*oldStr!='\0';*oldStr++) tempString = addChar(tempString, *oldStr);
		newString = addStr(newString, tempString.stringData);
		
		// Restore the original value of the variable
		temp = strCopy(newString); elem = tempElem;
		tempString = clearStr(tempString); 
		newString  = clearStr(newString);
		pos = find(temp, elem);
	}

	printf("temp: %s\n", getData(temp));
	
	return temp;
}

string clearStr(string str){
	/* Clear the contents of the String class */
	string newstring = initStr();

	free(str.stringData);
	str.stringData = NULL;

	return newstring;
}

int len(string str){
	/* Get string length */
	return str.length;
}
