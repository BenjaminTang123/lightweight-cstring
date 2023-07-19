/* File name: LCString.c
 * Version: v0.5.1
 * Author: Benjamin Tang(BenjainTang123)
 * Description: implementation of all functions in the library.
*/ 

#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <string.h>
#include <stdarg.h>

#include "lcstring.h"

string initString(void)
{
	/** 
	 * Initialize the string structure.
	 */

	string str;
	str.length = 1; // Set length of string
	str.stringContent = (char*)malloc(str.length*sizeof(char)); // Allocate dynamic memory
	if (!str.stringContent)
	{
		fprintf(stderr, "OSError: An unexpected error occurred at runtime!\n");
		exit(0);
	}
	str.stringContent[0] = '\0'; // End symbol
	
	return str;
}

string formatString(const char* format, ...)
{
	/**
	 * Obtain formatted string.
	*/
	va_list args;
	va_start(args, format);
	int length = vsnprintf(NULL, 0, format, args);
	va_end(args);

	string str = initString();
	str.stringContent = (char*)realloc(str.stringContent, (length+1)*sizeof(char));
	str.length = length;

	va_start(args, format);
	vsnprintf(str.stringContent, length+1, format, args);
	va_end(args);

	return str;
}

void addCharacter(string* str, char element)
{
	/**
	 * Add new char to the origin string.
	 */

	str->stringContent = (char*)realloc(str->stringContent, (str->length+1)*sizeof(char)); // Reallocate
	if (!str->stringContent)
	{
		fprintf(stderr, "OSError: An unexpected error occurred at runtime!\n");
		exit(0);
	}
	
	str->stringContent[str->length-1] = element;
	str->stringContent[str->length]   = '\0';
	
	str->length ++; // New length
}

void addString(string* str, char* element)
{
	/**
	 * Add new string to the origin string.
	 */

	size_t length; const char *addElement = element;
	for (length=0; *element!='\0'; element++) length ++;
	str->stringContent = (char*)realloc(str->stringContent, (str->length+length+1)*sizeof(char));
	if (!str->stringContent)
	{
		fprintf(stderr, "OSError: An unexpected error occurred at runtime!\n");
		exit(0);
	}

	size_t i; for (i=-1; length>i+1; i++)
	{
		str->stringContent[str->length+i] = *addElement;
		addElement ++; 
	}
	str->stringContent[str->length+i] = '\0';
	str->length += (i+1);
}

inline size_t getLength(string* str)
{
	/**
	 * Get string length.
	 * Include \0.
	 */

	return str->length;
}

inline char* getString(string* str)
{
	/**
	 * Get the string content.
	 */
	
	return str->stringContent;
}

inline void clearString(string* str)
{
	/**
	 * Clear the contents of the string.
	 */
	
	string newstring = initString();

	free(str->stringContent);
	str->stringContent = NULL;

	*str = newstring;
}

inline void deleteString(string* str)
{
	/**
	 * Delete the string object.
	*/
	free(str->stringContent);
}

inline string copyString(string* str)
{
	/**
	 * Copy string.
	 */
	
	string newstr = initString();
	addString(&newstr, str->stringContent);
	
	return newstr;
}

position findString(string* str, char* foundString)
{
	/**
	 * Used to locate a string in the original data to determine its location.
	 */
	
	char *stringContent = str->stringContent;
	position length = str->length;

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

size_t countString(string* str, char* foundString)
{
	/**
	 * Find how many matching strings are in a string.
	*/

	char *stringContent = str->stringContent;
	position length = str->length;

	position sign = NO_FOUND;
	size_t count = 0;
	for (position index=0; index<length; index++) 
	{
		if (sign != NO_FOUND) 
		{
			if (foundString[index-sign] == '\0') count ++;
			if (stringContent[index] != foundString[index-sign]) sign = NO_FOUND;
		}
		if (sign == NO_FOUND && stringContent[index] == *foundString) sign = index;
	}

	return count;
}

string splitString(string* str, const position start, const position end)
{
	/**
	 * Cut the qualified string according to the position.
	 */
	
	string finalString = initString();
	for (position pos=start; pos<end; pos++)
	{
		addCharacter(&finalString, (str->stringContent)[pos]);
	}

	return finalString;
}

bool replaceString(string* str, char* pattern_to_match, char* pattern_to_replace)
{
	/**
	 * Replace the specified content in the original string with another string.
	 */
	
	bool replacement = true;
	string newString = initString();
	string followingString = *str;
	position originalStringLength = 0;
	// Get the length of originElement string.
	for (; pattern_to_match[originalStringLength] != '\0'; originalStringLength++);

	for (; ; )
	{
		position originalStringPosition = findString(&followingString, pattern_to_match);
		if (originalStringPosition == NO_FOUND)
		{
			if (replacement == false) replacement = false;
			break;
		}

		string frontString = splitString(&followingString, 0, originalStringPosition);
		addString(&newString, frontString.stringContent);
		free(frontString.stringContent);
		frontString.stringContent = NULL;
		addString(&newString, pattern_to_replace);

		string oldFollowingString = followingString;
		followingString = splitString(&followingString, originalStringPosition+originalStringLength, followingString.length);
		free(oldFollowingString.stringContent);
		oldFollowingString.stringContent = NULL;
	}

	if (replacement == true)
	{
		addString(&newString, followingString.stringContent);
		*str = newString;
	}
	else
	{
		free(newString.stringContent);
		newString.stringContent = NULL;
	}
	
	return replacement;
}
