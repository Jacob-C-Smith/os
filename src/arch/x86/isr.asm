extern _isr_handlers 
extern terminal_printf 

section .text

%macro isr_fault 2
global isr_fault_%1
isr_fault_%1:
    pushad
    mov ebx, _isr_handlers
    mov eax, %2
    shl eax, 2
    add eax, ebx
    cld
    call [eax]
    cli
    hlt
%endmacro

isr_fault divide_by_zero, 0

global isr_fault_default
isr_fault_default:
    pushad
    push isr_fault_format
    call terminal_printf
    cli
    hlt

section .data
isr_fault_format: db "ERROR!", 10, "EDI=0x%x ESI=0x%x EBP=0x%x ESP=0x%x", 10, "EBX=0x%x EDX=0x%x ECX=0x%x EAX=0x%x", 10, "EIP=0x%x CS=0x%x EFLAGS=0x%x", 10, 0