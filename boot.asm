[BITS 16]
[ORG 0x7c00]

jmp start

start:
    xor ax, ax

    mov ds, ax
    mov ss, ax

    mov sp, 0x9c00

    mov si, msg
    call print

    hlt

; si <- pointer to message
print:
    lodsb
    or al, al 
    jz .end
    mov ah, 0xe
    int 0x10
    jmp print
    .end:
        ret

msg: db "Hi mom", 0

times 510-($-$$) db 0 
    db 0x55
    db 0xAA