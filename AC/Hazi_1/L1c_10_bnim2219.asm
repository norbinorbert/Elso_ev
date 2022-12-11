;Boda Norbert, bnim2219, 511
;L1c_10
;Írassuk ki a kiértékelendő kifejezést, olvassuk be az a, b, c, d értékeket az io_readint függvény segítségével, 
;majd írassuk ki a beolvasott értékeket és az eredményt egymás alá (előjeles egész számként).

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

;ertekek kiirasa
    mov     eax, str_a
    call    io_writestr
    mov     eax, [a]
    call    io_writeint
    call    io_writeln
    
    mov     eax, str_b
    call    io_writestr
    mov     eax, [b]
    call    io_writeint
    call    io_writeln
    
    mov     eax, str_c
    call    io_writestr
    mov     eax, [c]
    call    io_writeint
    call    io_writeln
    
    mov     eax, str_d
    call    io_writestr
    mov     eax, [d]
    call    io_writeint
    call    io_writeln

;mivel d mod 3-nak 3 kulonbozo eredmenye lehet ezert harom esetet kell venni
    mov     eax, [d]
    mov     ebx, 3
    cdq
    idiv    ebx
    cmp     edx, 1
    jl      .elso_eset
    je      .masodik_eset
    jg      .harmadk_eset

.elso_eset: ;(12 * a) + (b div 2) + 3 kiszamitasa
    mov     ebx, [a]
    imul    ebx, 12

    mov     eax, [b]
    mov     ecx, 2
    cdq
    idiv    ecx

    add     eax, ebx

    add     eax, 3

    mov     [eredmeny], eax
    jmp     .kiiras_elso_eset

.masodik_eset: ;(3 * ((c mod 4) - b)) - 1 kiszamitasa
    mov     eax, [c]
    mov     ebx, 4
    cdq
    idiv    ebx

    mov     ebx, [b]
    sub     edx, ebx

    imul    edx, 3

    sub     edx, 1

    mov     [eredmeny], edx
    jmp     .kiiras_masodik_eset

.harmadk_eset: ;(2 * (a - c)) + (b div 4) kiszamitasa
    mov     ebx, [a]
    mov     eax, [c]
    sub     ebx, eax

    imul    ebx, 2

    mov     eax, [b]
    mov     ecx, 4
    cdq
    idiv    ecx

    add     ebx, eax
    
    mov     [eredmeny], ebx
    jmp     .kiiras_harmadik_eset


;eredmeny kiirasa az elso esetben
.kiiras_elso_eset:
    mov     eax, str_elso_eset
    call    io_writestr
    mov     eax, [eredmeny]
    call    io_writeint
    ret

;eredmeny kiirasa a masodik esetben
.kiiras_masodik_eset:
    mov     eax, str_masodik_eset
    call    io_writestr
    mov     eax, [eredmeny]
    call    io_writeint
    ret

;eredmeny kiirasa a harmadik esetben
.kiiras_harmadik_eset:
    mov     eax, str_harmadik_eset
    call    io_writestr
    mov     eax, [eredmeny]
    call    io_writeint
    ret

section .data
    str_a db 'a = ', 0
    str_b db 'b = ', 0
    str_c db 'c = ', 0
    str_d db 'd = ', 0
    str_elso_eset db '(12 * a) + (b div 2) + 3 = ', 0
    str_masodik_eset db '(3 * ((c mod 4) - b)) - 1 = ', 0
    str_harmadik_eset db '(2 * (a - c)) + (b div 4) = ', 0

section .bss
    a resd 1
    b resd 1
    c resd 1
    d resd 1
    eredmeny resd 1