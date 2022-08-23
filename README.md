# LightweighCString

A string operation library based on C language. \
It is characterized by . \
It can complete some basic operations on strings.

- [LightweighCString](#lightweighcstring)
- [Overview](#overview)
- [Detailed](#detailed)
  - [String Structure](#string-structure)
  - [Initialize the String Structure](#initialize-the-string-structure)
  - [Add New Content to the String](#add-new-content-to-the-string)
  - [Get the Length of the String](#get-the-length-of-the-string)
  - [Get the content of the String](#get-the-content-of-the-string)
  - [Clear the Contents of the String](#clear-the-contents-of-the-string)
  - [Copy the String](#copy-the-string)
  - [Find the Location of the String](#find-the-location-of-the-string)
  - [Cut the String within the Specified Range](#cut-the-string-within-the-specified-range)
  - [Replace the Matching String in the Original String with a String](#replace-the-matching-string-in-the-original-string-with-a-string)
- [Common Problems](#common-problems)
    - [What happens if OSError is reported?](#what-happens-if-oserror-is-reported)
    - [Why is the value returned by find() a value much larger than the length of the string?](#why-is-the-value-returned-by-find-a-value-much-larger-than-the-length-of-the-string)
- [Examples](#examples)

# Overview 

This library defines a structure -- `string`. It records the string content and string length. \
To operate on a string, you must first define a variable of type string. \
At the same time, after using, you need to use `free()` to process the `stringContent` in the `string` structure.

In addition, if your project needs this library, you need to compile it together.

# Detailed

## String Structure

This structure has two elements -- `stringContent` and `length`. \
`stringContent` is the content of the string and `length` is the length of the string.

The type of `stringContent` is `char*`. After initialization with `initString()`, `stringContent` stores the address of the allocated dynamic memory. 

The type of `length` is `unsigned int`. When formatting the output, you need to use `%u` to print the value of `length`.

## Initialize the String Structure

After a variable of type string is defined, it needs to be initialized with a specific function. Therefore, use `initString()` to initialize a variable of type string. \
This function allocates dynamic memory to `stringContent`, so when a variable of type `string` is used, be sure to use `free()` for processing. \
The return solution of a function is a structure of type string. The length of the origin string is 1 because there is only one character '\0' in the string content. \
This function does not pass in arguments. 

## Add New Content to the String

There are two functions to add new content to a string: `addCharacter()` and `addString()`. 

If you only add characters to a string, you can use `addCharacter()`. This function has no return value, it can be said that its return value is `void`. \
It requires two parameters: the address of the structure and the characters to be added. \
However, if you want to add a string, in addition to using `addCharacter()` in the loop, you can also use `addString()`. This function also has no return value and requires two parameters. \
The two parameters are: the address of the structure and the string content to be added. However, the string to be added is of type `char*`. You can think of it as the address pointed to by the character pointer, and there is a string at the location of this address.\
The working mechanism of `addString()` is not to use `addCharcater()` circularly. 

Both `addCharacter()` and `addString()` end with '\0'. 

## Get the Length of the String

`getLength()` is used to get the string length. The type of its return value is `unsigned int`. It requires one parameter: the address of the structure.

## Get the content of the String

`getString()` is used to get the string content. The type of its return value is `char*`. It requires one parameter: the address of the structure. 

It is worth noting that it actually returns the value of `stringContent`. In other words, it is the same as the value of `stringContent` -- it is the address of the string content after dynamic memory allocation. \
Therefore, if you want to copy a string, you can use `copyString()`.

## Clear the Contents of the String

`clearString()` is used to get the string content. This function has no return value. It requires one parameter: the address of the structure. 

## Copy the String

`copyString()` is used to copy the string. The type of its return value is `string`. It requires one parameter: the address of the structure. 

The string returned by this function is not the same address as the original string. 

## Find the Location of the String

You can use `findstring()` to find the position of the matching string in the original string. The type of its return value is `unsigned int`. It requires two parameter: the address of the structure and the string to match. However, the string to match is of type `char*`. You can also think of it as the address pointed to by the character pointer, and there is a string at the location of this address.

If not found, `NO_FOUND` will be returned. If found, it will be retruned the position of the first character of the matching string in the original string.

## Cut the String within the Specified Range

Use `splitString()` to split a string. The type of its return value is `string`. It requires three parameter: the address of the structure, start position and end position. 

This function will split all characters from the start position to the end position. This function will pack the characters in this range into a `string`. 

## Replace the Matching String in the Original String with a String

Use `replaceString()` to replace the matching string in the original string with a string. The type of its return value is `bool`. It requires three parameter: the address of the structure, matching string and string to replace. \
The last two parameters are of type `char*`.

Returns `true` when the replacement succeeds, `false` otherwise. 

# Common Problems

### What happens if OSError is reported? 

All OSErrors in this library are due to dynamic memory application exceptions. Generally, the dynamic memory application exception is caused by insufficient memory. 

### Why is the value returned by find() a value much larger than the length of the string?

That value is often `LCString.h` - `NO_FOUND`. This value is used to mark not found. However, if this value does not match the value of `NO_FOUND`, there may be some problems. You can choose to report this problem. Thank you.

# Examples

```C
#include "LCString.h"

int main()
{
    string originalString = initString();
    int pos;

    addString(&originalString, "hello, world");
    addCharacter(&originalString, '!');

    printf("#1 originalString: `%s`\n", getString(&originalString));

    pos = findString(&originalString, "llo");
    if (pos != NO_FOUND) 
    {
        printf("#2 found it! the position in original string is %d!\n", pos);
    } 
    else 
    {
        printf("#3 no found...\n");
    }

    replaceString(&originalString, "hello, ", "Good morning, ");

    printf("#4 originalString: `%s`\n", getString(&originalString));

    pos = findString(&originalString, "worldd");
    if (pos != NO_FOUND) 
    {
        printf("#5 found it! the position in original string is %d!\n", pos);
    } 
    else 
    {
        printf("#6 no found...\n");
    }

    printf("#7 The string length is %d.\n", getLength(&originalString));

    string hello = splitString(&originalString, 0, 11);
    printf("#8 The string content of variable hello is `%s`.\n", getString(&hello));
    
    clearString(&originalString);
    addString(&originalString, "original string");

    printf("#9 Its content is: `%s`\n", getString(&originalString));

    originalString = copyString(&hello);
    printf("#10 Its content is: `%s`\n", getString(&originalString));

    free(originalString.stringContent);
    free(hello.stringContent);

    return 0;
}
```