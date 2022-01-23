/* String Type: 
 * The string of C is too cumbersome,
 * So I wrote a string operation module,
 * This allows you to quickly manipulate string.
 
 * Functions: initStr, addStr, getData, find ,replace, len
*/

#ifndef TyString_Header
#define TyString_Header

#include <stdlib.h>
#include <stdio.h>

typedef struct String {
	char* stringData;
	int length;
} string;

// Initialize String
string initStr();
// Add new string to string
string addStr(string str, char* elem);
// Add new char to string
string addChar(string str, char elem);
// Copy a string object
string strCopy(string str);
// Get string data
char* getData(string str);
// Used to locate a string in the original data to determine its location
int find(string str, char* findStr);
// Replace the specified content in the original string with another string
string replace(string str, char* elem, char* newelem);
// Clear the contents of the String class
string clearStr(string str);
// Get string length
int len(string str);

#endif
