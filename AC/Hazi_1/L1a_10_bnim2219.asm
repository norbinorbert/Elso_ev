;Boda Norbert, bnim2219, 511
;L1a_10
;a, b, c, d, e, f, g előjeles egész számok, az io_readint függvénnyel olvassuk be őket ebben a sorrendben.
;Az eredményt az io_writeint eljárás segítségével írjuk ki.
;10. ((a + c) div (a - 6)) - ((b + 7) div (a - 4)) - ((d - 5) div e) + ((f - c + (e * g)) div 4)

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
    
    mov     eax, str_e
    call    io_writestr
    call    io_readint
    mov     [e], eax   
    
    mov     eax, str_f
    call    io_writestr
    call    io_readint
    mov     [f], eax
    
    mov     eax, str_g
    call    io_writestr
    call    io_readint
    mov     [g], eax
   
    ;((a + c) div (a - 6)) kiszamitasa es hozzaadasa a vegeredmenyhez
    mov     eax, [a]
    mov     ebx, [c]
    add     eax, ebx
    mov     ecx, eax

    mov     eax, [a]
    sub     eax, 6
    mov     ebx, eax

    mov     eax, ecx
    cdq
    idiv    ebx
    mov     [vegeredmeny], eax

    ;((b + 7) div (a - 4)) kiszamitasa es kivonasa az vegeredmenybol
    mov     eax, [b]
    add     eax, 7

    mov     ebx, [a]
    sub     ebx, 4

    cdq
    idiv    ebx

    mov     ebx, [vegeredmeny]
    sub     ebx, eax
    mov     [vegeredmeny], ebx

    ;((d - 5) div e) kiszamitasa es kivonasa az vegeredmenybol
    mov     eax, [d]
    sub     eax, 5

    mov     ebx, [e]
    cdq
    idiv    ebx

    mov     ebx, [vegeredmeny]
    sub     ebx, eax
    mov     [vegeredmeny], ebx

    ;((f - c + (e * g)) div 4) kiszamitasa es hozzaadasa a vegeredmenyhez
    mov     eax, [e]
    mov     ebx, [g]
    imul    eax, ebx

    mov     ecx, [f]
    add     eax, ecx

    mov     ecx, [c]
    sub     eax, ecx

    mov     ebx, 4
    cdq
    idiv    ebx
    
    mov     ebx, [vegeredmeny]
    add     eax, ebx
    mov     [vegeredmeny], eax

    ;eredmeny kiirasa
    mov     eax, str_eredmeny
    call    io_writestr
    mov     eax, [vegeredmeny]
    call    io_writeint

    ret

section .data
    str_a db 'a = ', 0
    str_b db 'b = ', 0
    str_c db 'c = ', 0
    str_d db 'd = ', 0
    str_e db 'e = ', 0
    str_f db 'f = ', 0
    str_g db 'g = ', 0
    str_eredmeny db '((a + c) div (a - 6)) - ((b + 7) div (a - 4)) - ((d - 5) div e) + ((f - c + (e * g)) div 4) = ', 0

section .bss
    a resd 1
    b resd 1
    c resd 1
    d resd 1
    e resd 1
    f resd 1
    g resd 1
    vegeredmeny resd 1