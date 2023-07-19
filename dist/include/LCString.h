//! @file LCString.h
//! Version: v0.5.0
//! @author RobotBenjaminTang
//! @brief Header file containing functions in this library.
//!

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

#include <stddef.h>

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
 * @param str The string object.
 * @param element The character to append.
 */
void addCharacter(string* str, char element);

/**
 * Append a new c string to the end of the string object.
 * This won't change the C string itself.
 * @param str The string object.
 * @param element The C-string to append.
 */
void addString(string* str, char* element);

/**
 * Get the length of a string object.
 * @param str The string object.
 * @returns The length of the string object.
 */
size_t getLength(string* str);

/**
 * Get the string object's inner content.
 * This method is unsafe. Don't try to modify the content by using the returned pointer, or it may causes undefined behavior.
 * @param str The string object.
 * @returns The inner content of the object.
 */
char* getString(string* str);

/**
 * Clear all the contents of the string object.
 * @param str The string object.
 */
void clearString(string* str);

/**
 * Deep copies the string object.
 * @param str The string object.
 * @returns The copied string object.
 */
string copyString(string* str);

/**
 * Find the location of a given substring in the given string object.
 * If the location doesn't exist, `NO_FOUND` will be returned.
 * @param str The string object.
 * @param foundString The substring to find.
 * @returns The location of the substring. If there are multiple matches, the first will be returned. If nothing matches, `NO_FOUND` will be returned.
*/
position findString(string* str, char* foundString);

/**
 * Get the substring of the given string object with a range [begin, end].
 * @param str The string object.
 * @param begin The beginning of the closed-range.
 * @param end The ending of the closed-range.
 * @returns The splitted substring.
 */
string splitString(string* str, const position start, const position end);

/**
 * Replace the specified content in the original string with another string.
 * @param str The string object.
 * @param pattern_to_match The pattern to match.
 * @param pattern_to_replace The pattern to replace the matched part in the string object.
 * @returns Returns if the replacement succeeded or not.
 */
bool replaceString(string* str, char* pattern_to_match, char* pattern_to_replace);


#ifdef __cplusplus
}
#endif

#endif
