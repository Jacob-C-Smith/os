/** !
 * General utility interface
 * 
 * @file src/stdlib/stdlib.h
 * 
 * @author Jacob Smith
 */

// header guard
#pragma once

// standard library
#include <types.h>

// function declarations
/// dynamic memory management
/** !
 * allocate memory
 * 
 * @param size size of allocation IF not 0 ELSE release all allocations
 * 
 * @return a pointer to `size` bytes
 */
void *alloc ( size_t size );
