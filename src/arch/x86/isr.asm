extern _isr_handlers 

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
