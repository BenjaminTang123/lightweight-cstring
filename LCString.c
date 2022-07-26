/* File name: LCString.c
 * Last Modified Date: July 26th, 2022
 * Author: Robot_Steve
 * Description: implementation of all functions in the library.
*/

#include "LCString.h"

string initStr()
{
	/* Initialize the String */
	string str;
	
	str.length = 1; // Set length of string
	str.stringData = (char*)malloc(str.length*sizeof(char)); // Allocate dynamic memory
	if(!str.stringData)
	{
		// Report Error
		printf("OSError: An unexpected error occurred at runtime!\n");
		exit(0);
	}
	str.stringData[0] = '\0'; // End symbol

	return str;
}

void addChar(string *str, char elem)
{
	/* Add new char to the String */
	str->stringData = (char*)realloc(str->stringData, (str->length+1)*sizeof(char)); // Reallocate
	if(!str->stringData)
	{
		// Report Error
		printf("OSError: An unexpected error occurred at runtime!\n");
		exit(0);
	}
	
	str->stringData[str->length-1] = elem;
	str->stringData[str->length]   = '\0';
	
	str->length ++; // New length
}

void addStr(string *str, char *elem)
{
	/* Add new the String to the String */
	unsigned int length; char *addElem = elem;
	for(length=0; *elem!='\0'; elem++) length ++;
	
	str->stringData = (char*)realloc(str->stringData, (str->length+length+1)*sizeof(char));
	if(!str->stringData)
	{
		printf("OSError: An unexpected error occurred at runtime!\n");
		exit(0);
	}

	unsigned int i; for(i=-1; length>i+1; i++)
	{
		str->stringData[str->length+i] = *addElem;
		addElem ++; 
	}
	str->stringData[str->length+i] = '\0';
	str->length += (i+1);
}

string strCopy(const string *str)
{
	/* Copy a string object */
	string newstr = initStr();
	addStr(&newstr, str->stringData);
	
	return newstr;
}

char *getData(const string *str)
{
	/* Get the string data */
	return str->stringData;
}

unsigned int find(const string *Str, char *findStr)
{
	/* Used to locate a string in the original data to determine its location */
	char *str = Str->stringData;
	char *ALTERNATE = findStr;

	// The location of found. 
	// When it is -1: No find
	// When it is another value: found, and at this time it is the location of the record
	unsigned int found = -1; 
	for(unsigned int pos=0; *str!='\0'; str++)
	{
		if(*str == *findStr)
		{
			found = pos; // Record the position first
			for(; *findStr!='\0'; findStr ++)
			{
				// One character is different
				// Set to "Not found" and reset
				if(*str != *findStr || *findStr == '\0')
				{
					found = -1; findStr = ALTERNATE;
					break;
				}
				str ++;
			}
		}
		pos ++;
	}

	return found;
}

void replace(string *str, char *elem, char *newelem)
{
	/* Replace the specified content in the original string with another string */
	// Define a new String object
	string newString  = initStr();
	// Temporary string
	string tempString = initStr();
	
	// New temporary variable
	string temp    = *str;
	char *tempElem = elem;
	
	// The position of the string to replace
	unsigned int pos = find(&temp, elem);
	
	while(pos != -1)
	{
		// The old string
		char *oldStr = temp.stringData;

		// Collects the characters before the target string
		for(; pos>0; pos--)
		{
			addChar(&tempString, *oldStr);
			oldStr ++;
		}
		addStr(&newString, tempString.stringData);
		addStr(&newString, newelem);
		// Restore the original value of the variable
		clearStr(&tempString); 
		// Delete target string(The string to retrieve)
		for(; *elem!='\0'; elem++) oldStr ++;	
		
		for(; *oldStr!='\0'; oldStr++) addChar(&tempString, *oldStr);
		addStr(&newString, tempString.stringData);
		
		// Restore the original value of the variable
		temp = strCopy(&newString); elem = tempElem;
		clearStr(&tempString); 
		clearStr(&newString);
		pos = find(&temp, elem);
	}

	free(newString.stringData);
	newString.stringData  = NULL;
	free(tempString.stringData);
	tempString.stringData = NULL;
	
	*str = temp;
}

string splitStr(string *str, unsigned const int start, unsigned const int end)
{
	/* Cut the qualified string according to the position */
	string finalString = initStr();
	for(unsigned int position=start; position<=end; position++)
		addChar(&finalString, str->stringData[position]);

	return finalString;
}

void clearStr(string *str)
{
	/* Clear the contents of the String class */
	string newstring = initStr();

	free(str->stringData);
	str->stringData = NULL;

	*str = newstring;
}

unsigned int len(string *str)
{
	/* Get string length 
	 * Include \0
	*/
	return str->length;
}
