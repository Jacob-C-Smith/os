/** !
 * Interfaces used throughout the os
 * 
 * @file src/os/interfaces.h
 * 
 * @author Jacob Smith
 */

// header guard
#pragma once

// type definitions
/// reflection
typedef int (fn_pack)   ( void *p_buffer, const void *const  p_value );
typedef int (fn_unpack) ( void *p_value , void              *p_buffer );

/// interrupt service routine
typedef void (fn_isr) ( void );
