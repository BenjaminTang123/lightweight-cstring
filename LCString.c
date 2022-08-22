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
	originStr.stringContent = (char*)malloc(originStr.length*sizeof(char)); // Allocate dynamic memory
	if(!originStr.stringContent)
	{
		// Report Error
		printf("OSError: An unexpected error occurred at runtime!\n");
		exit(0);
	}
	originStr.stringContent[0] = '\0'; // End symbol

	return originStr;
}

void addCharacter(string *originStr, char elem)
{
	/**
	 * Add new char to the origin string.
	 */

	originStr->stringContent = (char*)realloc(originStr->stringContent, (originStr->length+1)*sizeof(char)); // Reallocate
	if(!originStr->stringContent)
	{
		// Report Error
		printf("OSError: An unexpected error occurred at runtime!\n");
		exit(0);
	}
	
	originStr->stringContent[originStr->length-1] = elem;
	originStr->stringContent[originStr->length]   = '\0';
	
	originStr->length ++; // New length
}

void addString(string *originStr, char *elem)
{
	/**
	 * Add new string to the origin string.
	 */

	unsigned int length; char *addElem = elem;
	for(length=0; *elem!='\0'; elem++) length ++;
	
	originStr->stringContent = (char*)realloc(originStr->stringContent, (originStr->length+length+1)*sizeof(char));
	if(!originStr->stringContent)
	{
		printf("OSError: An unexpected error occurred at runtime!\n");
		exit(0);
	}

	unsigned int i; for(i=-1; length>i+1; i++)
	{
		originStr->stringContent[originStr->length+i] = *addElem;
		addElem ++; 
	}
	originStr->stringContent[originStr->length+i] = '\0';
	originStr->length += (i+1);
}

unsigned int getLength(string *originStr)
{
	/**
	 * Get string length.
	 * Include \0.
	 */

	return originStr->length;
}

char *getString(const string *originStr)
{
	/**
	 * Get the string content.
	 */
	
	return originStr->stringContent;
}

void clearString(string *originStr)
{
	/**
	 * Clear the contents of the string.
	 */
	
	string newstring = initString();

	free(originStr->stringContent);
	originStr->stringContent = NULL;

	*originStr = newstring;
}

string copyString(const string *originStr)
{
	/**
	 * Copy string.
	 */
	
	string newstr = initString();
	addString(&newstr, originStr->stringContent);
	
	return newstr;
}

unsigned int findString(const string *originStr, char *foundString)
{
	/**
	 * Used to locate a string in the original data to determine its location.
	 */
	
	char *stringContent = originStr->stringContent;
	unsigned int length = originStr->length;

	// Records the position when the stringContent matches the first character of the string to be searched.
	unsigned int sign = NO_FOUND;
	// variable index represents the position of traversing to stringContent.
	for (unsigned int index=0; ; index++) 
	{
		// If the index reaches the end of the string but the loop does not end,
		// there is no matching string for this string.
		if (length == index) return NO_FOUND;

		// When the value of variable sign is not NO_FOUND,
		// The representative has determined the position when
		// the stringContent matches the first character of the string to be searched.
		if (sign != NO_FOUND) 
		{
			// If foundstring reaches the end but the value of variable sign is not NO_FOUND,
			// Represents finding a matching string and jumping out of the loop.
			if (foundString[index-sign] == '\0') break;
			// When the characters do not match, 
			// reset the value of variable sign to NO_FOUND.
			if (stringContent[index] != foundString[index-sign]) sign = NO_FOUND;
		} 
		// When stringContent matches the first character of the string to be searched
		if (sign == NO_FOUND && stringContent[index] == *foundString) sign = index;
	}

	return sign;
}

string splitString(string *originStr, const unsigned int start, const unsigned int end)
{
	/**
	 * Cut the qualified string according to the position.
	 */
	
	string finalString = initString();
	for(unsigned int position=start; position<=end; position++)
		addCharacter(&finalString, originStr->stringContent[position]);

	return finalString;
}

void replaceString(string *originStr, char *originElement, char *newElement)
{
	/**
	 * Replace the specified content in the original string with another string.
	 */
	
	int originElementIndex = 0;

	// Get the length of originElement string.
	for (; originElement[originElementIndex] != '\0'; originElementIndex++);
	// Get the position of originElement string.
	int originElementPosition = findString(originStr, originElement);
	// Split the string before originElement string.
	string newString = splitString(originStr, 0, originElementPosition-1);
	// Split the string after originElement string.
	string followingString = splitString(originStr, originElementPosition+originElementIndex, (originStr->length)-1);

	// Splice string.
	addString(&newString, newElement);
	addString(&newString, followingString.stringContent);

	// Free dynamic memory
	free(followingString.stringContent);
	free(originStr->stringContent);

	*originStr = newString;
}
