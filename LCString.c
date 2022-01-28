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

string strCopy(string str){
	/* Copy a string object */
	string newstr = initStr();
	newstr = addStr(newstr, str.stringData);
	
	return newstr;
}

char* getData(string str){
	/* Get string data */
	return str.stringData;
}

int find(string str, char* findStr){
	/* Used to locate a string in the original data to determine its location */
	char* oldstr = str.stringData; // Get old string
	
	char* intmeFind = findStr; // Help register variables to be found
	
	int position = 0; // Locate the location after
	/* find variable:
	 * - When the value is -1, it is absolutely not found
	 * - When the value is 0,  it is relatively found
	 * - When the value is 1,  it is absolutely found
	*/
	int find = 0; // whether the string was found
	for(;*oldstr!='\0'; *oldstr++){
		if(*oldstr == *intmeFind){
			for(;*intmeFind!='\0';*intmeFind++){
				if(*intmeFind != *oldstr){
					// Restore the original value of the variable
					intmeFind = findStr;
					find = -1; // It is absolutely not found
					break;
				}
				*oldstr++;
			}
			if(find != -1) // Don't be absolutely not found
				find = 1;
		}
		if(find == 1) // Be absolutely found
			break;
		position ++; // Position variable plus 1
	}
	if(find == 1) // Be absolutely found
		// The position must be returned only in the absolutely found state
		return position;
	else
		return -1; // If not found, -1 is returned
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
	
	while(pos != -1){
		// Old string
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
