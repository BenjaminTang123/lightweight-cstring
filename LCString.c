/* File name: LCString.c
 * Last Modified Date: August 23th, 2022
 * Author: Robot_Steve
 * Description: implementation of all functions in the library.
*/

#include "LCString.h"

string initString(void)
{
	/** 
	 * Initialize the string structure.
	 */

	string originString;
	
	originString.length = 1; // Set length of string
	originString.stringContent = (char*)malloc(originString.length*sizeof(char)); // Allocate dynamic memory
	if(!originString.stringContent)
	{
		// Report Error
		printf("OSError: An unexpected error occurred at runtime!\n");
		exit(0);
	}
	originString.stringContent[0] = '\0'; // End symbol

	return originString;
}

void addCharacter(string *originString, char element)
{
	/**
	 * Add new char to the origin string.
	 */

	originString->stringContent = (char*)realloc(originString->stringContent, (originString->length+1)*sizeof(char)); // Reallocate
	if(!originString->stringContent)
	{
		// Report Error
		printf("OSError: An unexpected error occurred at runtime!\n");
		exit(0);
	}
	
	originString->stringContent[originString->length-1] = element;
	originString->stringContent[originString->length]   = '\0';
	
	originString->length ++; // New length
}

void addString(string *originString, char *element)
{
	/**
	 * Add new string to the origin string.
	 */

	unsigned int length; char *addElement = element;
	for(length=0; *element!='\0'; element++) length ++;
	
	originString->stringContent = (char*)realloc(originString->stringContent, (originString->length+length+1)*sizeof(char));
	if(!originString->stringContent)
	{
		printf("OSError: An unexpected error occurred at runtime!\n");
		exit(0);
	}

	unsigned int i; for(i=-1; length>i+1; i++)
	{
		originString->stringContent[originString->length+i] = *addElement;
		addElement ++; 
	}
	originString->stringContent[originString->length+i] = '\0';
	originString->length += (i+1);
}

unsigned int getLength(string *originString)
{
	/**
	 * Get string length.
	 * Include \0.
	 */

	return originString->length;
}

char *getString(const string *originString)
{
	/**
	 * Get the string content.
	 */
	
	return originString->stringContent;
}

void clearString(string *originString)
{
	/**
	 * Clear the contents of the string.
	 */
	
	string newstring = initString();

	free(originString->stringContent);
	originString->stringContent = NULL;

	*originString = newstring;
}

string copyString(const string *originString)
{
	/**
	 * Copy string.
	 */
	
	string newstr = initString();
	addString(&newstr, originString->stringContent);
	
	return newstr;
}

unsigned int findString(const string *originString, char *foundString)
{
	/**
	 * Used to locate a string in the original data to determine its location.
	 */
	
	char *stringContent = originString->stringContent;
	unsigned int length = originString->length;

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

string splitString(string *originString, const unsigned int start, const unsigned int end)
{
	/**
	 * Cut the qualified string according to the position.
	 */
	
	string finalString = initString();
	for(unsigned int position=start; position<=end; position++)
		addCharacter(&finalString, originString->stringContent[position]);

	return finalString;
}

void replaceString(string *originString, char *originElement, char *newElement)
{
	/**
	 * Replace the specified content in the original string with another string.
	 */
	
	int originElementIndex = 0;

	// Get the length of originElement string.
	for (; originElement[originElementIndex] != '\0'; originElementIndex++);
	// Get the position of originElement string.
	int originElementPosition = findString(originString, originElement);
	// Split the string before originElement string.
	string newString = splitString(originString, 0, originElementPosition-1);
	// Split the string after originElement string.
	string followingString = splitString(originString, originElementPosition+originElementIndex, (originString->length)-1);

	// Splice string.
	addString(&newString, newElement);
	addString(&newString, followingString.stringContent);

	// Free dynamic memory
	free(followingString.stringContent);
	free(originString->stringContent);

	*originString = newString;
}
