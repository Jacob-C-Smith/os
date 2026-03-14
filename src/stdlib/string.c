/** !
 * Null terminated byte string implementation
 * 
 * @file src/stdlib/string.c
 * 
 * @author Jacob Smith
 */

// header
#include <string.h>

// function definitions
size_t strlen ( const char *p_string )
{

	// initialized data
	size_t len = 0;

	// count bytes
	while ( 0 != p_string[len] ) len++;

	// done
	return len;
}

int strcmp ( const char *const p_a, const char *const p_b, size_t len )
{

	// initialized data
	int result = 0;

	// compare `len` characters
	for (size_t i = 0; i < len; i++)
	{
		
		// initialized data
		char a = p_a[i];
		char b = p_b[i];

		// step
		if ( 0 == (b - a) ) continue;

		// store the result
		result = (b > a) ? -1 : 1;

		// done
		break;
	}
	
	// done
	return result;
}

char *strcpy ( char *restrict p_destination, const char *restrict p_source, size_t size )
{

	// initialized data
	void *p_result = NULL;
	char *p_dest = (char *)p_destination;
	char *p_src  = (char *)p_source;

	// copy memory
	for (size_t i = 0; i < size; i++)

		// copy a byte
		*p_dest = *p_src,

		// step
		p_dest++, p_src++;
	
	// done
	return p_result;
}

char *strdup ( const char *p_string, size_t size )
{

	// initialized data
	char *p_result = alloc(size);

	// copy the string
	strcpy(p_result, p_string, size);

	// done
	return p_result;
}

void *memcpy ( void *restrict p_destination, const void *restrict p_source, size_t size )
{

	// initialized data
	void *p_result = NULL;
	char *p_dest = (char *)p_destination;
	char *p_src  = (char *)p_source;

	// copy memory
	for (size_t i = 0; i < size; i++)

		// copy a byte
		*p_dest = *p_src,

		// step
		p_dest++, p_src++;
	
	// done
	return p_result;
}
