/** !
 * Pack interface
 * 
 * @file src/os/pack.h 
 * 
 * @author Jacob Smith
 */

// header guard
#pragma once

// standard library
#include <va.h>
#include <limits.h>
#include <ctype.h>
#include <string.h>

// function declarations
/// pack
/** !
 * Pack data into a buffer
 * 
 * @param p_buffer the buffer
 * @param format   format string
 * @param ...      variadic arguments
 * 
 * @return bytes written on success, 0 on error
 */
size_t pack_pack ( void *p_buffer, const char *restrict format, ... );

/// unpack
/** !
 * Unpack data from a buffer
 * 
 * @param p_buffer the buffer
 * @param format   format string
 * @param ...      variadic arguments
 * 
 * @return quantity of matched fields on success, 0 on error
 */
size_t pack_unpack ( void *p_buffer, const char *restrict format, ... );
