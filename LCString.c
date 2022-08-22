/* File name: LCString.c
 * Last Modified Date: August 22th, 2022
 * Author: Robot_Steve
 * Description: implementation of all functions in the library.
*/

#include "LCString.h"

string initString(void)
{
	/** 
	 * Initialize the string structure.
	 */

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

void addCharacter(string *originStr, char elem)
{
	/**
	 * Add new char to the origin string.
	 */

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

void addString(string *originStr, char *elem)
{
	/**
	 * Add new string to the origin string.
	 */

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

string copyString(const string *originStr)
{
	/**
	 * Copy string.
	 */
	
	string newstr = initString();
	addString(&newstr, originStr->stringData);
	
	return newstr;
}

char *getString(const string *originStr)
{
	/**
	 * Get the string content.
	 */
	
	return originStr->stringData;
}

unsigned int findString(const string *originStr, char *findStr)
{
	/**
	 * Used to locate a string in the original data to determine its location.
	 */
	
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

void replaceString(string *originStr, char *element, char *newElement)
{
	/**
	 * Replace the specified content in the original string with another string.
	 */
	
	// Define a new String object
	string newString  = initString();
	// Temporary string
	string tempString = initString();
	
	// New temporary variable
	string temp    = *originStr;
	char *tempElement = element;
	
	// The position of the string to replace
	unsigned int pos = findString(&temp, element);
	
	while(pos != NO_FOUND)
	{
		// The old string
		char *oldStr = temp.stringData;

		// Collects the characters before the target string
		for(; pos>0; pos--)
		{
			addCharacter(&tempString, *oldStr);
			oldStr ++;
		}
		addString(&newString, tempString.stringData);
		addString(&newString, newElement);
		// Restore the original value of the variable
		clearString(&tempString); 
		// Delete target string(The string to retrieve)
		for(; *element!='\0'; element++) oldStr ++;	
		
		for(; *oldStr!='\0'; oldStr++) addCharacter(&tempString, *oldStr);
		addString(&newString, tempString.stringData);
		
		// Restore the original value of the variable
		temp = strCopy(&newString); element = tempElement;
		clearString(&tempString); 
		clearString(&newString);
		pos = findString(&temp, element);
	}

	free(newString.stringData);
	newString.stringData  = NULL;
	free(tempString.stringData);
	tempString.stringData = NULL;
	
	*originStr = temp;
}

string splitString(string *originStr, unsigned const int start, unsigned const int end)
{
	/**
	 * Cut the qualified string according to the position.
	 */
	
	string finalString = initString();
	for(unsigned int position=start; position<=end; position++)
		addCharacter(&finalString, originStr->stringData[position]);

	return finalString;
}

void clearString(string *originStr)
{
	/**
	 * Clear the contents of the String class.
	 */
	
	string newstring = initString();

	free(originStr->stringData);
	originStr->stringData = NULL;

	*originStr = newstring;
}

unsigned int getLength(string *originStr)
{
	/**
	 * Get string length.
	 * Include \0.
	 */
	
	return originStr->length;
}
