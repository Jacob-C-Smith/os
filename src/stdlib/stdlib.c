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
unsigned char *p_pool = (void *)(1024*1024*3);
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

int atoi ( const char *p_string )
{

    // initialized data
    int result = 0;
    int i = 0;

    // iterate through the string
    while ( p_string[i] >= '0' && p_string[i] <= '9' )
    {
        result = result * 10 + p_string[i] - '0';
        i++;
    }

    // done
    return result;
}