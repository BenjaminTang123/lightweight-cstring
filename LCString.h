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

// Initialize String
string initString(void);
// Add new char to string
void addCharacter(string *, char);
// Add new string to string
void addString(string *, char *);
// Copy a string object
string copyString(const string *);
// Get string data
char *getString(const string *);
// Used to locate a string in the original data to determine its location
unsigned int findString(const string *, char *);
// Replace the specified content in the original string with another string
void replaceString(string *, char *, char *);
// Cut the qualified string according to the position
string splitString(string *, unsigned const int, unsigned const int);
// Clear the contents of the String class
void clearString(string *);
// Get string length
unsigned int getLength(string *);

#ifdef __cplusplus
}
#endif

#endif
