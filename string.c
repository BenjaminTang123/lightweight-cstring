#include "string.h"

/* String Type: 
 * The string of C is too cumbersome,
 * So I wrote a string operation module,
 * This allows you to quickly manipulate string.
 *
 * Functions: initStr, addStr, getData, find ,replace, len
*/

string initStr(){
	/* Initialize String */
	string str;
	
	str.length = 1; // Set length of string
	str.stringData = (char*)malloc(str.length*sizeof(char)); // Allocate dynamic memory
	if(!str.stringData){
		// Report Error
		printf("OSError: An unexpected error occurred at runtime!d\n");
		exit(0);
	}
	str.stringData[0] = '\0'; // End symbol

	return str;
}

string addChar(string str, char elem){
	/* Add new char to string */
	int oldlen = str.length; // Old length
	
	str.stringData = (char*)realloc(str.stringData, (oldlen+1)*sizeof(char)); // Reallocate
	if(!str.stringData){
		// Report Error
		printf("OSError: An unexpected error occurred at runtime!\n");
		exit(0);
	}
	
	str.stringData[oldlen-1] = elem;
	str.stringData[oldlen] = '\0';
	
	str.length ++; // New length
	
	return str;
}

string addStr(string str, char* elem){
	/* Add new string to string */
	while(*elem != '\0'){
		// Add characters to the target string one by one
		str = addChar(str, *elem);

		// Traversal string
		*elem ++;
	}

	return str;
}

char* getData(string str){
	/* Get string data */
	return str.stringData;
}

int find(string str, char *findStr){
	/* Used to locate a string in the original data to determine its location */
	char *getStrData = str.stringData; // Get string
	int len = -1; // The location of the str found
	// Reserve value
	char *resStr = findStr;
	char *resStrData = getStrData;
	int found = 0;
	
	while(*getStrData != '\0'){ // When findStr is not empty
		len ++; 
		if(*findStr == *getStrData){
			// Check Again
			while(*findStr != '\0' && *getStrData != '\0'){
				if(*findStr == *getStrData){
					*findStr++;*getStrData ++;
					found = 1;
				}else{
					// Not Found
					findStr=resStr;resStrData=getStrData; // Replace the value
					found = 0;len=-1;
					break;
				}
			}
			// Check whether is found
			if(found == 1)
			 	break;
		}
		// Check one by one
		*getStrData ++;
	}
	
	// Check the variables and reset len's value
	if(*findStr != '\0' || found == 0)
		len = -1;
	else if(len == 5)
		len = -1;
		
	return len;
}

string replace(string str, char* elem, char* newelem){
	/* Replace the specified content in the original string with another string */
	// Define a String Object
	string oldStr = initStr(); // Old String Object
	oldStr = addStr(oldStr, elem);
	string newStr = initStr(); // New String Object
	newStr = addStr(newStr, newelem);
	
	// Get string length
	int oldlen = len(oldStr);
	int newlen = len(newStr);
	
	char *originalStr = str.stringData; // Get original string
	int pos = find(str, elem); // Find location
	
	if(pos != -1){ // Found
		string resStr = initStr(); // Final string
		if(pos != 0){ // When pos's value isn't 0
			int i;
			for(i=0; i<pos; i++){
				resStr = addChar(resStr, *originalStr);
				*originalStr ++;
			}
		}
		resStr = addStr(resStr, newelem); // Add new string
		while(*elem != '\0'){
			*elem ++;*originalStr ++; // Delete the character to replace
		}
		while(*originalStr != '\0'){
			resStr = addChar(resStr, *originalStr); // Add old string
			*originalStr ++;
		}
		
		return resStr;
	}else{
		// Not found but no error is reported
		return str;
	}
}

string clearStr(string str){
	/* Clear the contents of the String class */
	string newstring = initStr();
	return newstring;
}

int len(string str){
	/* Get string length */
	return str.length;
}
