[BITS 16]
[ORG 0x7c00]

jmp start

start:
    xor ax, ax ; ax = 0

    mov ds, ax ; ds = 0
    mov ss, ax ; ss = 0

    mov sp, 0x9c00 ; ~8,192 stack

    ; say hi
    mov si, msg 
    call print

    ; load stage 2
    mov ah, 0x42
    mov dl, 0x80
    mov si, dap
    int 0x13

    ; jump to stage 2
    jmp 0x500

    ; explode
    cli
    hlt

; si <- pointer to message
print:
    lodsb       ; al = [si], si++
    or al, al   ; set zf IF al == 0
    jz .end     ; done
    mov ah, 0xe 
    int 0x10
    jmp print
    .end:
        ret

dap:
    db 0x10   ; size
    db 0x00   ; pad
    dw 0x10   ; 16 sectors
    dd 0x0500 ; at 0x500
    dq 0x1    ; starting at sector 1

msg: db "Hi mom", 0

times 510-($-$$) db 0 
    db 0x55
    db 0xAA