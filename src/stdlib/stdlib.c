/** !
 * General utility implementation
 * 
 * @file src/stdlib/stdlib.c
 * 
 * @author Jacob Smith
 */

// header
#include <stdlib.h>

// data
unsigned char *p_pool = (void *)0x200000;
size_t used = 0;

// function definitions
void *alloc ( size_t size )
{
    
    // initialized data
    void *p_result = &p_pool[used];

    // step
    used += size;

    // done
    return p_result;
}