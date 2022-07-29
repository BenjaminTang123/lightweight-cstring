/* File name: LCString.h
 * Last Modified Date: July 26th, 2022
 * Author: Robot_Steve
 * Description: Header file containing functions in this library.
*/

#include <stdlib.h>
#include <stdio.h>

#ifndef TyString_Header
#define TyString_Header

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
void addChar(string *str, char elem);
// Add new string to string
void addStr(string *str, char *elem);
// Copy a string object
string strCopy(const string *str);
// Get string data
char* getData(const string *str);
// Used to locate a string in the original data to determine its location
unsigned int find(const string *Str, char *findStr);
// Replace the specified content in the original string with another string
void replace(string *str, char *elem, char *newelem);
// Cut the qualified string according to the position
string splitStr(string *str, unsigned const int start, unsigned const int end);
// Clear the contents of the String class
void clearStr(string *str);
// Get string length
unsigned int len(string *str);

#ifdef __cplusplus
}
#endif

#endif
