/* File name: LCString.h
 * Last Modified Date: August 22th, 2022
 * Author: Robot_Steve
 * Description: Header file containing functions in this library.
*/

#include <stdlib.h>
#include <stdio.h>
#include <limits.h>

#ifndef TyString_Header
#define TyString_Header

#define NO_FOUND (UINT_MAX)

typedef struct String {
	char* stringContent;
	unsigned int length;
} string;

#ifdef __cplusplus
extern "C" {
#endif

// Initialize the string structure.
string initString(void);
// Add new char to the origin string.
void addCharacter(string *, char);
// Add new string to the origin string.
void addString(string *, char *);
// Get string length.
unsigned int getLength(string *);
// Get the string content.
char *getString(const string *);
// Clear the contents of the string.
void clearString(string *);
// Copy string.
string copyString(const string *);
// Used to locate a string in the original data to determine its location.
unsigned int findString(const string *, char *);
// Cut the qualified string according to the position
string splitString(string *, const unsigned int, const unsigned int);
// Replace the specified content in the original string with another string.
void replaceString(string *, char *, char *);


#ifdef __cplusplus
}
#endif

#endif
