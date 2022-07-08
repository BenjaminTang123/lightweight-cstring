/* File name: LCString.h
 * Date: July 8th, 2022
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

// Initialize String
string initStr();
// Add new string to string
void addStr(string *str, char *elem);
// Add new char to string
void addChar(string *str, char elem);
// Copy a string object
string strCopy(const string *str);
// Get string data
char* getData(const string *str);
// Used to locate a string in the original data to determine its location
int find(const string *Str, char *findStr);
// Replace the specified content in the original string with another string
void replace(string *str, char *elem, char *newelem);
// Clear the contents of the String class
void clearStr(string *str);
// Get string length
int len(string *str);

#endif
