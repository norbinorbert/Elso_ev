;Boda Norbert, bnim2219, 511
;L1b_10
;Írassuk ki a kiértékelendő kifejezést, olvassuk be az a, b, c, d értékeket az io_readint függvény segítségével, 
;majd írassuk ki a beolvasott értékeket és az eredményt egymás alá bináris formában az io_writebin függvény segítségével.
;10. (d AND(NOT a)) OR((b AND c) XOR(NOT b))

%include 'io.inc'

global main

section .text
main:
    ;szamok beolvasasa
    mov     eax, str_a
    call    io_writestr
    call    io_readint
    mov     [a], eax

    mov     eax, str_b
    call    io_writestr
    call    io_readint
    mov     [b], eax
    
    mov     eax, str_c
    call    io_writestr
    call    io_readint
    mov     [c], eax
    
    mov     eax, str_d
    call    io_writestr
    call    io_readint
    mov     [d], eax
    
    ;(d AND(NOT a)) lementese eax-be
    mov     eax, [d]

    mov     ebx, [a]
    not     ebx
    
    and     eax, ebx

    ;((b AND c) XOR(NOT b)) lementese ecx-be
    mov     ecx, [b]
    mov     edx, [c]
    and     ecx, edx

    mov     edx, [b]
    not     edx

    xor     ecx, edx

    ;vegeredmeny kiszamitasa ket reszeredmenybol
    or eax, ecx
    mov [eredmeny], eax

    ;ertekek es eredmeny kiirasa binaris formaban
    mov     eax, str_a
    call    io_writestr
    mov     eax, [a]
    call    io_writebin
    call    io_writeln
    
    mov     eax, str_b
    call    io_writestr
    mov     eax, [b]
    call    io_writebin
    call    io_writeln
    
    mov     eax, str_c
    call    io_writestr
    mov     eax, [c]
    call    io_writebin
    call    io_writeln
    
    mov     eax, str_d
    call    io_writestr
    mov     eax, [d]
    call    io_writebin
    call    io_writeln
    
    mov     eax, str_eredmeny
    call    io_writestr
    mov     eax, [eredmeny]
    call    io_writebin
    call    io_writeln
    ret

section .data
    str_a db 'a = ', 0
    str_b db 'b = ', 0
    str_c db 'c = ', 0
    str_d db 'd = ', 0
    str_eredmeny db '(d AND(NOT a)) OR((b AND c) XOR(NOT b)) = ', 0

section .bss
    a resd 1
    b resd 1
    c resd 1
    d resd 1
    eredmeny resd 1