#include <os/terminal.h>

size_t terminal_row;
size_t terminal_column;
u8 terminal_color;
u16* terminal_buffer = (u16 *)VGA_MEMORY;

char _hexadecimal_lut[16] = "0123456789abcdef";

void terminal_initialize(void) 
{
	terminal_row = 0;
	terminal_column = 0;
	terminal_color = vga_entry_color(VGA_COLOR_LIGHT_GREY, VGA_COLOR_BLACK);
	
	for (size_t y = 0; y < VGA_HEIGHT; y++) {
		for (size_t x = 0; x < VGA_WIDTH; x++) {
			const size_t index = y * VGA_WIDTH + x;
			terminal_buffer[index] = vga_entry(' ', terminal_color);
		}
	}
}

void terminal_setcolor(u8 color) 
{
	terminal_color = color;
}

void terminal_putentryat(char c, u8 color, size_t x, size_t y) 
{
	const size_t index = y * VGA_WIDTH + x;
	terminal_buffer[index] = vga_entry(c, color);
}

void terminal_putchar(char c) 
{
	if ( c == '\n' ) 
	{
		terminal_column = 0, terminal_row++;
		return;
	}
	if ( c == '\r' ) 
	{
		terminal_column = 0;
		return;
	}

	terminal_putentryat(c, terminal_color, terminal_column, terminal_row);
	if (++terminal_column == VGA_WIDTH) {
		terminal_column = 0;
		if (++terminal_row == VGA_HEIGHT)
			terminal_row = 0;
	}
}

void terminal_write(const char* data, size_t size) 
{
	for (size_t i = 0; i < size; i++)
		terminal_putchar(data[i]);
}

void terminal_writestring(const char* data) 
{
	terminal_write(data, strlen(data));
}

int terminal_printf ( const char *restrict format, ... )
{
    
    // initialized data
    va_list list;
    size_t read = 0, written = 0;

    // construct the variadic list
    va_start(list, format);
    
    parse_format_specifier:

    // iterate through the format string
    while ( format[read] )
    {

        // parse format characters
        if ( format[read] == '%' )
        {

            // increment the index
            read++;

            continue_parsing_format_specifier:

            // strategy
            switch ( format[read] )
            {

				// string 
                case 's': 

                    // increment the read index
                    read++;

                    // write the string
                    goto write_str;

				// character
				case 'c': 

                    // increment the read index
                    read++;

                    // write the character
                    goto write_char;

				// hexadecimal
				case 'x':

					// increment the read index
					read++;

					// write the hexidecimal
					goto write_hexadecimal;

				// default
                default:

                    // done
                    break;

				/*
                // length
                case '1': case '2': case '3': case '4': case '5': case '6': case '7': case '8': case '9':

                    // parse the quantity of values
                    goto parse_len;

                    // continue reading format specifiers
                    done_reading_format_specifier_length: goto continue_parsing_format_specifier;
                
                // float
                case 'f':

                    // increment the read index
                    read++;

                    // 32-bit value
                    if ( format[read] == '3' && format[read + 1] == '2') goto write_f32;

                    // 64-bit value
                    else if ( format[read] == '6' && format[read + 1] == '4') goto write_f64;
                    
                    // default
                    else return 0;

                    // done
                    break;

                // integer
                case 'i':

                    // increment the read index
                    read++;

                    // 8-bit value
                    if ( format[read] == '8' ) goto write_8;
                    
                    // 16-bit value
                    else if ( format[read] == '1' && format[read + 1] == '6' ) goto write_16;
                    
                    // 32-bit value
                    else if ( format[read] == '3' && format[read + 1] == '2' ) goto write_32;

                    // 64-bit value
                    else if ( format[read] == '6' && format[read + 1] == '4' )  goto write_64;

                    // default
                    else
                        return 0;

                    // done
                    break;
*/
                
            }
        }
        
		// write the character
		terminal_putchar(format[read]);

        // increment the index
        read++;
	}

    // done with variadic list
    va_end(list);

    // success
    return written;

	/*
    // This branch parses the quantity of values in a format specifier
    parse_len:
    {

        // store the length of the format specifier
        format_specifier_length = atoi(&format[read]);

        // update the read index
        while (isdigit(format[++read]));

        // done
        goto done_reading_format_specifier_length;
    }

    // This branch writes bytes 
    write_8:
    {

        // iterate through each variadic argument
        for (size_t i = 0; i < format_specifier_length; i++)
        {

            // initialized data
            char c = va_arg(list, int);

            // store the value
            *((char *)p_buffer) = c;
            
            // update the buffer and written byte counter
            p_buffer += sizeof(char), written += sizeof(char);
        }

        // reset the format specifier length
        format_specifier_length = 1;
        
        // update the read index
        read++;

        // continue
        goto parse_format_specifier;
    }

    // This branch writes shorts 
    write_16:
    {

        // iterate through each variadic argument
        for (size_t i = 0; i < format_specifier_length; i++)
        {

            // initialized data
            short s = va_arg(list, int);

            // store the value
            *((short *)p_buffer) = s;
            
            // update the buffer and written byte counter
            p_buffer += sizeof(short), written += sizeof(short);
        }

        // reset the format specifier length
        format_specifier_length = 1;

        // update the read index
        read += 2;

        // continue
        goto parse_format_specifier;
    }
    
    // This branch writes ints 
    write_32:
    {

        // iterate through each variadic argument
        for (size_t i = 0; i < format_specifier_length; i++)
        {

            // initialized data
            int l = va_arg(list, int);

            // store the value
            *((int *)p_buffer) = l;
            
            // update the buffer and written byte counter
            p_buffer += sizeof(int), written += sizeof(int);
        }

        // reset the format specifier length
        format_specifier_length = 1;

        // update the read index
        read += 2;

        // continue
        goto parse_format_specifier;
    }

    // This branch writes longs 
    write_64:
    {

        // iterate through each variadic argument
        for (size_t i = 0; i < format_specifier_length; i++)
        {

            // initialized data
            long l = va_arg(list, long);

            // store the value
            *((long *)p_buffer) = l;
            
            // update the buffer and written byte counter
            p_buffer += sizeof(long), written += sizeof(long);
        }

        // reset the format specifier length
        format_specifier_length = 1;

        // update the read index
        read += 2;

        // continue
        goto parse_format_specifier;
    }

    // This branch writes f32s 
    write_f32:
    {

        // iterate through each variadic argument
        for (size_t i = 0; i < format_specifier_length; i++)
        {

            // initialized data
            float f = va_arg(list, double);

            // store the value
            *((float *)p_buffer) = f;
            
            // update the buffer and written byte counter
            p_buffer += sizeof(float), written += sizeof(float);
        }

        // reset the format specifier length
        format_specifier_length = 1;

        // update the read index
        read += 2;

        // continue
        goto parse_format_specifier;
    }
    
    // This branch writes f64s
    write_f64:
    {

        // iterate through each variadic argument
        for (size_t i = 0; i < format_specifier_length; i++)
        {

            // initialized data
            double d = va_arg(list, double);

            // store the value
            *((double *)p_buffer) = d;
            
            // update the buffer and written byte counter
            p_buffer += sizeof(double), written += sizeof(double);
        }

        // reset the format specifier length
        format_specifier_length = 1;
        
        // update the read index
        read += 2;

        // continue
        goto parse_format_specifier;
    }
	*/

    // this branch writes strings 
    write_str:
    {

		// initialized data
		const char *s = va_arg(list, char *);
		size_t len = strlen(s);

		// write the value
		terminal_writestring(s);
		
		// update the buffer and written byte counter
		written += len;

        // continue
        goto parse_format_specifier;
    }
	
	// this branch writes characters 
    write_char:
    {

		// initialized data
		char c = va_arg(list, int);

		// write the value
		terminal_putchar(c);
		
		// update the buffer and written byte counter
		written++;

        // continue
        goto parse_format_specifier;
    }

	// this branch writes hexadecimal values
	write_hexadecimal:
	{

		// initialized data
		unsigned int x = va_arg(list, unsigned int);
		int i = 7;
		char _buf[8+1] = { 0 };

		// edge case
		if ( 0 == x ) 
		{
			terminal_putchar('0'), written++;
			goto parse_format_specifier;
		}

		// hexadecimal to ascii
		while ( x )
		{

			// store the n'th hexadecimal character
			_buf[i] = _hexadecimal_lut[x & 0xf];

			// step
			x >>= 4, i--;
		}
		
		// print the hexadecimal string
		terminal_writestring(&_buf[i+1]);
		
		// update the buffer and written byte counter
		written += 8-i;
		
        // continue
        goto parse_format_specifier;
	}
}