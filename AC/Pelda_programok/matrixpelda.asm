%include 'io.inc'

global main

section .text
main:
    call     io_readint
    mov     [n], eax
    imul    eax, [n]
    mov     [n2], eax

    mov     ecx, 0
    .beolvas:
        mov     eax, ecx
        cdq
        idiv    dword [n]   ;eax = i (sor), edx = j (oszlop)
        call    io_writeint
        mov     eax, vesszo
        call    io_writestr
        mov     eax, edx
        call    io_writeint
        mov     eax, egyenlo
        call    io_writestr

        call    io_readflt
        movss   [A + 4 * ecx], xmm0

        inc     ecx
        cmp     ecx, [n2]
        jne     .beolvas

    mov     ecx, 0
    .transzponal:
        movss   xmm0, [A + 4 * ecx]
        mov     eax, ecx    
        cdq
        idiv    dword [n]   ;eax = i (sor), edx = j (oszlop)

        imul    edx, [n]
        add     edx, eax    ;edx = (j,i) elem indexe a tombben

        movss   [B + 4 * edx], xmm0

        inc     ecx
        cmp     ecx, [n2]
        jne     .transzponal

    mov     ecx, 0
    .kiir:
        mov     eax, ecx
        cdq
        idiv    dword [n]   ;eax = i (sor), edx = j (oszlop)
        call    io_writeint
        mov     eax, vesszo
        call    io_writestr
        mov     eax, edx
        call    io_writeint
        mov     eax, egyenlo
        call    io_writestr

        movss   xmm0, [B + 4 * ecx]
        call    io_writeflt
        call    io_writeln

        inc     ecx
        cmp     ecx, [n2]
        jne     .kiir

    ret

section .data
    vesszo db ', ', 0
    egyenlo db ' = ', 0

section .bss
    A resd 256 ;beolvasott matrix
    B resd 256 ;transzponalt matrix
    n resd 1 ;matrix merete
    n2 resd 2 ;n^2