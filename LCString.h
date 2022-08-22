/* File name: LCString.h
 * Last Modified Date: July 26th, 2022
 * Author: Robot_Steve
 * Description: Header file containing functions in this library.
*/

#include <stdlib.h>
#include <stdio.h>
#include <limits.h>

#ifndef TyString_Header
#define TyString_Header

#define NO_FOUND (UINT_MAX-1)

typedef struct String {
	char* stringData;
	unsigned int length;
} string;

#ifdef __cplusplus
extern "C" {
#endif

// Initialize String
string initStr(void);
// Add new char to string
void addChar(string *, char);
// Add new string to string
void addStr(string *, char *);
// Copy a string object
string strCopy(const string *);
// Get string data
char* getData(const string *);
// Used to locate a string in the original data to determine its location
unsigned int find(const string *, char *);
// Replace the specified content in the original string with another string
void replace(string *, char *, char *);
// Cut the qualified string according to the position
string splitStr(string *, unsigned const int, unsigned const int);
// Clear the contents of the String class
void clearStr(string *);
// Get string length
unsigned int len(string *);

#ifdef __cplusplus
}
#endif

#endif
