section .text

global out_byte
out_byte:
    mov al, [esp+4]
    mov dx, [esp+8]
    out dx, al
    ret

global out_word
out_word:
    mov ax, [esp+4]
    mov dx, [esp+8]
    out dx, ax
    ret

global out_dword
out_dword:
    mov eax, [esp+4]
    mov dx, [esp+8]
    out dx, eax
    ret

global in_byte
in_byte:
    mov dx, [esp+4]
    in al, dx
    ret

global in_word
in_word:
    mov dx, [esp+4]
    in ax, dx
    ret

global in_dword
in_dword:
    mov dx, [esp+4]
    in eax, dx
    ret