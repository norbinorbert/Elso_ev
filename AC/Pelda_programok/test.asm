%include 'io.inc'

global main

section .text
main:
    mov     eax, str_feladat
    call    io_writestr
    call    io_writeln

    ;a beolvasasa
    mov     eax, str_a
    call    io_writestr
    call    io_readint
    mov     [a], eax

    ;b beolvasasa
    mov     eax, str_b
    call    io_writestr
    call    io_readint
    mov     [b], eax  

    ;c beolvasasa
    mov     eax, str_c
    call    io_writestr
    call    io_readint
    mov     [c], eax  

    mov     eax, [a]    ;eax = a
    mov     ebx, [b]    ;ebx = b
    imul    eax, ebx    ;eax = a * b
    add     eax, 12     ;eax = a * b + 12
    mov     ebx, [c]    ;ebx = c
    cdq                 ;convert double to quad, edx = 0 vagy FFFF (eax elojeletol fuggoen)
    idiv    ebx         ;eax = (a * b + 12) / c

    mov ebx, eax
    mov eax, str_eredmeny
    call io_writestr
    mov eax, ebx
    call io_writeint
    call io_writeln

    ret

section .data
    str_feladat db "E(a,b,c)=(a*b+12)/c", 0 ;string veget jelzi a 0
    str_eredmeny db "E(a,b,c)=(a*b+12)/c=", 0
    str_a db 'a=', 0
    str_b db 'b=', 0
    str_c db 'c=', 0

section .bss
    a resd 1  ;res = helyfoglalas, resd - 32 bit, 1 darab 32 bites erteket vehet fel
    b resd 1
    c resd 1


    ;B. feladata utasitasok
    ;and eax, ebx
    ;or  eax, ebx
    ;xor eax, ebx
    ;not eax