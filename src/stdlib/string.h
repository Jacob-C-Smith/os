/** !
 * Null terminated byte string interface
 * 
 * @file src/stdlib/string.h
 * 
 * @author Jacob Smith
 */

// header guard
#pragma once

// standard library
#include <types.h>
#include <stdlib.h>

// function declarations
/// string examination
/** !
 * string length
 * 
 * @param p_string the string
 * 
 * @return the length of the string
 */
size_t strlen ( const char *p_string );

/** !
 * compare strings
 * 
 * @param p_a string A
 * @param p_b string B
 * @param len maximum quantity of characters to compare
 * 
 * @return -1 IF A > B ELSE 1 IF A < B ELSE 0 IF A == B
 */
int strcmp ( const char *const p_a, const char *const p_b, size_t len );

/// string manipulation
/** !
 * copy strings
 * 
 * @param p_destination pointer to destination
 * @param p_source      pointer to source
 * @param size          number of characters to copy
 * 
 * @return NULL on success, NOT NULL on error
 */
char *strcpy ( char *restrict p_destination, const char *restrict p_source, size_t size );

/** !
 * save a copy of a string
 * 
 * @param p_string pointer to string
 * @param size     number of characters to copy
 * 
 * @return pointer to a copy of `p_string`
 */
char *strdup ( const char *p_string, size_t size );

/// memory
/** !
 * copy memory area
 * 
 * @param p_destination pointer to destination
 * @param p_source      pointer to source
 * @param size          number of bytes to copy
 * 
 * @return NULL on success, NOT NULL on error
 */
void *memcpy ( void *restrict p_destination, const void *restrict p_source, size_t size );
