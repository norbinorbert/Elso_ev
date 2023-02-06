%include 'ionum.inc'
%include 'iostr.inc'

global main

section .text
main:
    mov     esi, Astr
    call    WriteStr
    call    ReadInt
    mov     [A], eax

    mov     esi, Bstr
    call    WriteStr
    call    ReadInt
    mov     [B], eax

    mov     esi, Cstr
    call    WriteStr
    call    ReadInt
    mov     [C], eax

    mov     esi, Dstr
    call    WriteStr
    call    ReadInt
    mov     [D], eax
    
    mov     esi, Estr
    call    WriteStr
    call    ReadInt
    mov     [E], eax
    
    mov     esi, Fstr
    call    WriteStr
    call    ReadInt
    mov     [F], eax
    
    mov     esi, Gstr
    call    WriteStr
    call    ReadInt
    mov     [G], eax

    mov     eax, [G]
    mov     ebx, 6
    cdq
    idiv    ebx
    add     edx, [A] ;G mod 6 + A

    mov     ecx, [E]
    imul    ecx, ecx
    sub     ecx, [C] ;E^2 - C

    cmp     edx, ecx
    jg      .elso_nagyobb
    jle      .masodik_nagyobb

    .elso_nagyobb:
        mov     ecx, edx

    .masodik_nagyobb:
        mov     ebx, 2
        mov     eax, ecx
        cdq
        idiv    ebx ;max() div 2

    mov     ebx, [B]
    mov     ecx, 2
    imul    ebx, ecx ;2 * B

    mov     edx, [D]
    sub     edx, 4 ;D - 4

    sub     eax, ebx
    sub     eax, edx
    mov     ebx, 5
    cdq
    idiv    ebx ;(max div 2 - - ) div 5

    mov     ecx, [C]
    imul    ecx, ecx
    sub     eax, ecx  ;-C^2

    mov     ecx, eax
    mov     eax, [F]
    mov     ebx, 3
    cdq
    idiv    ebx
    add     ecx, edx

    mov     esi, uzenet
    call    WriteStr
    mov     eax, ecx
    call    WriteInt

    ret

section .data
    Astr db 'A = ', 0
    Bstr db 'B = ', 0
    Cstr db 'C = ', 0
    Dstr db 'D = ', 0
    Estr db 'E = ', 0
    Fstr db 'F = ', 0
    Gstr db 'G = ', 0
    uzenet db '((max(G mod 6 + A, E^2-C) div 2 - 2 * B - (D - 4)) div 5 - C^2) + F mod 3 = '

section .bss
    A resd 1
    B resd 1
    C resd 1
    D resd 1
    E resd 1
    F resd 1
    G resd 1