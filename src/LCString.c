/* File name: LCString.c
 * Version: v0.5.0
 * Author: RobotBenjaminTang
 * Description: implementation of all functions in the library.
*/ 

#include "lcstring.h"

string initString(void)
{
	/** 
	 * Initialize the string structure.
	 */

	string originString;
	originString.length = 1; // Set length of string
	originString.stringContent = (char*)malloc(originString.length*sizeof(char)); // Allocate dynamic memory
	if (!originString.stringContent)
	{
		fprintf(stderr, "OSError: An unexpected error occurred at runtime!\n");
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
	if (!originString->stringContent)
	{
		fprintf(stderr, "OSError: An unexpected error occurred at runtime!\n");
		exit(0);
	}
	
	originString->stringContent[originString->length-1] = element;
	originString->stringContent[originString->length]   = '\0';
	
	originString->length ++; // New length
}

void addString(string *originString, const char *element)
{
	/**
	 * Add new string to the origin string.
	 */

	size_t length; const char *addElement = element;
	for (length=0; *element!='\0'; element++) length ++;
	originString->stringContent = (char*)realloc(originString->stringContent, (originString->length+length+1)*sizeof(char));
	if (!originString->stringContent)
	{
		fprintf(stderr, "OSError: An unexpected error occurred at runtime!\n");
		exit(0);
	}

	size_t i; for (i=-1; length>i+1; i++)
	{
		originString->stringContent[originString->length+i] = *addElement;
		addElement ++; 
	}
	originString->stringContent[originString->length+i] = '\0';
	originString->length += (i+1);
}

inline size_t getLength(string *originString)
{
	/**
	 * Get string length.
	 * Include \0.
	 */

	return originString->length;
}

inline char *getString(const string *originString)
{
	/**
	 * Get the string content.
	 */
	
	return originString->stringContent;
}

inline void clearString(string *originString)
{
	/**
	 * Clear the contents of the string.
	 */
	
	string newstring = initString();

	free(originString->stringContent);
	originString->stringContent = NULL;

	*originString = newstring;
}

inline string copyString(const string *originString)
{
	/**
	 * Copy string.
	 */
	
	string newstr = initString();
	addString(&newstr, originString->stringContent);
	
	return newstr;
}


position findString(const string *originString, char *foundString)
{
	/**
	 * Used to locate a string in the original data to determine its location.
	 */
	
	char *stringContent = originString->stringContent;
	position length = originString->length;

	// Records the position when the stringContent matches the first character of the string to be searched.
	position sign = NO_FOUND;
	// variable index represents the position of traversing to stringContent.
	for (position index=0; ; index++) 
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

string splitString(string *originString, const position start, const position end)
{
	/**
	 * Cut the qualified string according to the position.
	 */
	
	string finalString = initString();
	for (position pos=start; pos<end; pos++)
	{
		addCharacter(&finalString, (originString->stringContent)[pos]);
	}

	return finalString;
}

bool replaceString(string *originString, char *originElement, char *newElement)
{
	/**
	 * Replace the specified content in the original string with another string.
	 */
	
	bool replacement = true;
	string newString = initString();
	string followingString = *originString;
	position originElementLength = 0;
	// Get the length of originElement string.
	for (; originElement[originElementLength] != '\0'; originElementLength++);

	for (; ; )
	{
		position originElementPosition = findString(&followingString, originElement);
		if (originElementPosition == NO_FOUND)
		{
			if (replacement == false) replacement = false;
			break;
		}

		string frontString = splitString(&followingString, 0, originElementPosition);
		addString(&newString, frontString.stringContent);
		free(frontString.stringContent);
		frontString.stringContent = NULL;
		addString(&newString, newElement);

		string oldFollowingString = followingString;
		followingString = splitString(&followingString, originElementPosition+originElementLength, followingString.length);
		free(oldFollowingString.stringContent);
		oldFollowingString.stringContent = NULL;
	}

	if (replacement == true)
	{
		addString(&newString, followingString.stringContent);
		*originString = newString;
	}
	else
	{
		free(newString.stringContent);
		newString.stringContent = NULL;
	}
	
	return replacement;
}
