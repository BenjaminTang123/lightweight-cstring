/* File name: LCString.c
 * Last Modified Date: July 26th, 2022
 * Author: Robot_Steve
 * Description: implementation of all functions in the library.
*/

#include "LCString.h"

string initStr(void)
{
	/* Initialize the String */
	string originStr;
	
	originStr.length = 1; // Set length of string
	originStr.stringData = (char*)malloc(originStr.length*sizeof(char)); // Allocate dynamic memory
	if(!originStr.stringData)
	{
		// Report Error
		printf("OSError: An unexpected error occurred at runtime!\n");
		exit(0);
	}
	originStr.stringData[0] = '\0'; // End symbol

	return originStr;
}

void addChar(string *originStr, char elem)
{
	/* Add new char to the String */
	originStr->stringData = (char*)realloc(originStr->stringData, (originStr->length+1)*sizeof(char)); // Reallocate
	if(!originStr->stringData)
	{
		// Report Error
		printf("OSError: An unexpected error occurred at runtime!\n");
		exit(0);
	}
	
	originStr->stringData[originStr->length-1] = elem;
	originStr->stringData[originStr->length]   = '\0';
	
	originStr->length ++; // New length
}

void addStr(string *originStr, char *elem)
{
	/* Add new the String to the String */
	unsigned int length; char *addElem = elem;
	for(length=0; *elem!='\0'; elem++) length ++;
	
	originStr->stringData = (char*)realloc(originStr->stringData, (originStr->length+length+1)*sizeof(char));
	if(!originStr->stringData)
	{
		printf("OSError: An unexpected error occurred at runtime!\n");
		exit(0);
	}

	unsigned int i; for(i=-1; length>i+1; i++)
	{
		originStr->stringData[originStr->length+i] = *addElem;
		addElem ++; 
	}
	originStr->stringData[originStr->length+i] = '\0';
	originStr->length += (i+1);
}

string strCopy(const string *originStr)
{
	/* Copy a string object */
	string newstr = initStr();
	addStr(&newstr, originStr->stringData);
	
	return newstr;
}

char *getData(const string *originStr)
{
	/* Get the string data */
	return originStr->stringData;
}

unsigned int find(const string *originStr, char *findStr)
{
	/* Used to locate a string in the original data to determine its location */
	char *str = originStr->stringData;
	char *alternate = findStr;

	// The location of found. 
	// When it is -1: No find
	// When it is another value: found, and at this time it is the location of the record
	unsigned int found = NO_FOUND; 
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
					found = NO_FOUND; findStr = alternate;
					break;
				}
				str ++;
			}
		}
		pos ++;
	}

	return found;
}

void replace(string *originStr, char *element, char *newElement)
{
	/* Replace the specified content in the original string with another string */
	// Define a new String object
	string newString  = initStr();
	// Temporary string
	string tempString = initStr();
	
	// New temporary variable
	string temp    = *originStr;
	char *tempElement = element;
	
	// The position of the string to replace
	unsigned int pos = find(&temp, element);
	
	while(pos != NO_FOUND)
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
		addStr(&newString, newElement);
		// Restore the original value of the variable
		clearStr(&tempString); 
		// Delete target string(The string to retrieve)
		for(; *element!='\0'; element++) oldStr ++;	
		
		for(; *oldStr!='\0'; oldStr++) addChar(&tempString, *oldStr);
		addStr(&newString, tempString.stringData);
		
		// Restore the original value of the variable
		temp = strCopy(&newString); element = tempElement;
		clearStr(&tempString); 
		clearStr(&newString);
		pos = find(&temp, element);
	}

	free(newString.stringData);
	newString.stringData  = NULL;
	free(tempString.stringData);
	tempString.stringData = NULL;
	
	*originStr = temp;
}

string splitStr(string *originStr, unsigned const int start, unsigned const int end)
{
	/* Cut the qualified string according to the position */
	string finalString = initStr();
	for(unsigned int position=start; position<=end; position++)
		addChar(&finalString, originStr->stringData[position]);

	return finalString;
}

void clearStr(string *originStr)
{
	/* Clear the contents of the String class */
	string newstring = initStr();

	free(originStr->stringData);
	originStr->stringData = NULL;

	*originStr = newstring;
}

unsigned int len(string *originStr)
{
	/* Get string length 
	 * Include \0
	*/
	return originStr->length;
}
