//! @file LCString.h
//! Last Modified Date: August 24th, 2022
//! @author RobotBenjaminTang
//! @brief Header file containing functions in this library.
//!

#include <stdlib.h>
#include <stdio.h>
#include <limits.h>
#include <stdbool.h>

#ifndef LCString
#define LCString

#ifndef NO_FOUND
#ifndef __POS_TYPE
#ifndef __FIXED_SIZE
/// A constant that will be returned by `findString()` if we can't find the substring.
#define NO_FOUND (LONG_MAX-1)
/// Character position.
#define __POS_TYPE unsigned long int
typedef __POS_TYPE position;
/// One time fixed pre allocation allocation size.
#define __FIXED_SIZE 5
#endif /* NO_FOUND */
#endif /* __POS_TYPE */
#endif /* __FIXED_SIZE */

#ifdef __cplusplus
extern "C" {
#endif

/**
 * A data structure that stores a String.
 * @see initString()
 * @see replaceString()
 */
typedef struct String {

	/**
	 * The inner content of the string.
	 */
	char* stringContent;

	/**
	 * To manage the actual allocated memory size.
	 */
	size_t capacity;

	/**
	 * The length of the string.
	 */
	size_t length;
} string;

/**
 * Construct an empty string.
 * @returns The constructed string.
 */
string initString(void);

/**
 * Append a new character to the end of the string object.
 * @param self The string object.
 * @param c The character to append.
 */
void addCharacter(string * self, char c);

/**
 * Append a new c string to the end of the string object.
 * This won't change the C string itself.
 * @param self The string object.
 * @param str The C-string to append.
 */
void addString(string * self, const char * str);

/**
 * Get the length of a string object.
 * @param self The string object.
 * @returns The length of the string object.
 */
size_t getLength(string * self);

/**
 * Get the string object's inner content.
 * This method is unsafe. Don't try to modify the content by using the returned pointer, or it may causes undefined behavior.
 * @param self The string object.
 * @returns The inner content of the object.
 */
char *getString(const string * self);

/**
 * Clear all the contents of the string object.
 * @param self The string object.
 */
void clearString(string * self);

/**
 * Deep copies the string object.
 * @param self The string object.
 * @returns The copied string object.
 */
string copyString(const string * self);

/**
 * Find the location of a given substring in the given string object.
 * If the location doesn't exist, `NO_FOUND` will be returned.
 * @param self The string object.
 * @param str The substring to find.
 * @returns The location of the substring. If there are multiple matches, the first will be returned. If nothing matches, `NO_FOUND` will be returned.
*/
position findString(const string * self, char * str);

/**
 * Get the substring of the given string object with a range [begin, end].
 * @param self The string object.
 * @param begin The beginning of the closed-range.
 * @param end The ending of the closed-range.
 * @returns The splitted substring.
 */
string splitString(string * self, const position begin, const position end);

/**
 * Replace the specified content in the original string with another string.
 * @param self The string object.
 * @param pattern_to_match The pattern to match.
 * @param pattern_to_replace The pattern to replace the matched part in the string object.
 * @returns Returns if the replacement succeeded or not.
 */
bool replaceString(string * self, char * pattern_to_match, char * pattern_to_replace);


#ifdef __cplusplus
}
#endif

#endif
