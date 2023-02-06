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

    mov     edi, [E]
    mov     esi, [C]
    imul    edi, esi
    sub     edi, 3 ;e*c-3

    mov     eax, [D]
    add     eax, [G]
    mov     ebx, 5
    cdq
    idiv    ebx
    sub     edi, edx    ;- (d+g) mod 5

    mov     eax, [F]
    mov     ebx, 2
    imul    eax, ebx
    add     eax, [A]

    mov     ebx, [B]
    add     ebx, [F]

    cmp     eax, ebx
    jge     .masodik
    jl      .elso

    .masodik:
        mov     eax, ebx ;minimum

    .elso:
    sub     edi, eax    ;-minimum
    mov     eax, edi
    mov     ebx, [D]
    sub     ebx, 2
    cdq
    idiv    ebx

    mov     ecx, [E]
    add     ecx, [C]
    imul    edx, ecx ; * (e + C)

    mov     eax, edx

    mov     esi, eredmeny
    call    WriteStr
    call    WriteInt

    ret

section .data
    Astr db 'Kerem az A szamot: ', 0
    Bstr db 'Kerem a B szamot: ', 0
    Cstr db 'Kerem a C szamot: ', 0
    Dstr db 'Kerem a D szamot: ', 0
    Estr db 'Kerem az E szamot: ', 0
    Fstr db 'Kerem az F szamot: ', 0
    Gstr db 'Kerem a G szamot: ', 0
    eredmeny db 'Eredmeny: ', 0
section .bss
    A resd 1
    B resd 1
    C resd 1
    D resd 1
    E resd 1
    F resd 1
    G resd 1
    