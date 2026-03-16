/** !
 * interrupt service routine interface
 * 
 * @file src/arch/x86/isr.h
 * 
 * @author Jacob Smith
 */

// header guard
#pragma once

// standard library
#include <types.h>
#include <stdlib.h>

// os
#include <os/interfaces.h>
#include <os/terminal.h>

// arch
#include <arch/x86/idt.h>

// enumeration definitions
enum isr_type_e
{
    ISR_DIVIDE_ERROR,
    ISR_DEBUG,
    ISR_NMI,
    ISR_BREAKPOINT,
    ISR_OVERFLOW,
    ISR_BOUND_RANGE_EXCEEDED,
    ISR_INVALID_OPCODE,
    ISR_DEVICE_NOT_AVAILABLE,
    ISR_DOUBLE_FAULT,
    ISR_COPROCESSOR_SEGMENT_OVERRUN,
    ISR_INVALID_TSS,
    ISR_SEGMENT_NOT_PRESENT,
    ISR_STACK_SEGMENT_FAULT,
    ISR_GENERAL_PROTECTION_FAULT,
    ISR_PAGE_FAULT,
    ISR_RESERVED,
    ISR_FPU_ERROR,
    ISR_ALIGNMENT_CHECK,
    ISR_MACHINE_CHECK,
    ISR_SIMD_FLOATING_POINT_EXCEPTION,
    ISR_VIRTUALIZATION_EXCEPTION,
    ISR_SECURITY_EXCEPTION,
};

// forward declarations
int isr_initialize ( void );
fn_isr isr_default;
fn_isr isr_fault_divide_by_zero;
fn_isr isr_divide_error;
fn_isr isr_80h;
fn_isr isr_fault_default;