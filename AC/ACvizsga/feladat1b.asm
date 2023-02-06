%include 'ionum.inc'
%include 'iostr.inc'

global main

section .text
main:
    mov     esi, Astr
    call    WriteStr
    call    ReadHex
    mov     [A], eax

    mov     esi, Bstr
    call    WriteStr
    call    ReadHex
    mov     [B], eax

    mov     esi, Cstr
    call    WriteStr
    call    ReadHex
    mov     [C], eax

    mov     esi, Astr2
    call    WriteStr
    mov     eax, [A]
    call    WriteBin

    mov     esi, Bstr2
    call    WriteStr
    mov     eax, [B]
    call    WriteBin

    mov     esi, Cstr2
    call    WriteStr
    mov     eax, [C]
    call    WriteBin
    
    mov     eax, [A]
    mov     ebx, [B]
    xor     eax, ebx
    mov     ecx, [C]
    and     ecx, eax
    mov     [C], ecx

    mov     edi, 31
    xor     esi, esi
    .kezdet:
        shl     esi, 1

        mov     eax, [A]
        mov     ecx, edi
        shr     eax, cl
        shl     eax, 28
        shr     eax, 28

        mov     ebx, [B]
        mov     ecx, 31
        sub     ecx, edi
        shr     ebx, cl
        shl     ebx, 28
        shr     ebx, 28

        add     eax, ebx
        mov     ecx, 31
        sub     ecx, eax

        mov     ebx, [C]
        shr     ebx, cl
        shl     ebx, 31
        shr     ebx, 31
        
        or      esi, ebx
    
    .vege:
        dec     edi
        cmp     edi, 0
        jge     .kezdet

    mov     eax, esi
    mov     esi, Dstr
    call    WriteStr
    call    WriteBin
    ret

section .data
    Astr db 'Kerem az A hexadecimalis szamot: ', 0
    Bstr db 'Kerem a B hexadecimalis szamot: ', 0
    Cstr db 'Kerem a C hexadecimalis szamot: ', 0
    Astr2 db 'Az A szam binarisan: ', 0
    Bstr2 db 'A B szam binarisan: ', 0
    Cstr2 db 'A C szam binarisan: ', 0
    Dstr db 'A D szam: ', 0

section .bss
    A resd 1
    B resd 1
    C resd 1