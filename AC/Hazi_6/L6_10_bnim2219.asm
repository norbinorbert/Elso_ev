;Boda Norbert, bnim2219, 511
;L6_10
;Olvassunk be két azonos hosszúságú lebegőpontos értékekből álló tömböt. Olvassuk be a tömbök hosszát, majd a tömbök elemeit, minden elemet új sorból. 
;A tömbök minden elemére páronként végezzük el az alább megadott műveleteket, tároljuk el az eredményeket egy másik tömbben, végül pedig írjuk ki azt. 
;A feladat lényege, hogy ne skaláris utasításokat használjuk, hanem vektorosokat. Csak 4-el osztható hosszúságú tömböket kell elfogadjon a program.
;A számokat az IO-ban található függvényekkel kell beolvasni és kiírni.
;10. E(a,b) = sqrt(max(a + b / 2, 4)) + a^2 - b^3

%include 'io.inc'

global main

section .text
main:
    mov     eax, hossz
    call    io_writestr
    xor     eax, eax
    call    io_readint
    mov     esi, eax
    mov     ebx, 4
    mov     ecx, esi
    xor     edx, edx
    div     ebx
    cmp     edx, 0
    je     .olvas 

    mov     eax, hiba
    call    io_writestr

    ret ;ha a beolvasott hossz nem oszthato 4-el akkor leall a program

    .olvas:
        mov     eax, A_elemei
        call    io_writestr
        mov     eax, esi
        xor     ebx, ebx
        .elso_tomb: ;elso tomb feltoltese
            xorps   xmm0, xmm0
            call    io_readflt
            movss   [A + ebx], xmm0
            add     ebx, 4
            loop    .elso_tomb
        
        xor     ebx, ebx
        mov     ecx, esi
        mov     eax, B_elemei
        call    io_writestr
        .masodik_tomb: ;masodik tomb feltoltese
            xorps   xmm0, xmm0
            call    io_readflt
            movss   [B + ebx], xmm0
            add     ebx, 4
            loop    .masodik_tomb

    mov     eax, esi
    mov     ebx, 4
    xor     edx, edx
    div     ebx
    mov     ecx, eax
    xor     ebx, ebx
    .muveletek:
        movups  xmm0, [A + ebx] ;xmm0 = A
        movups  xmm1, [B + ebx] ;xmm1 = B

        movups  xmm3, xmm1      ;xmm3 = B
        movups  xmm4, [ketto]   ;xmm4 = 2, 2, 2, 2
        divps   xmm3, xmm4      ;xmm3 = B / 2
        addps   xmm3, xmm0      ;xmm3 = A + B / 2
        movups  xmm4, [negy]    ;xmm4 = 4, 4, 4, 4
        
        maxps   xmm3, xmm4      ;xmm3 = max(a + b/2, 4)
        sqrtps  xmm3, xmm3      ;xmm3 = sqrt(xmm3)

        movups  xmm5, xmm0      ;xmm5 = A
        mulps   xmm5, xmm0      ;xmm5 = A^2

        movups  xmm6, xmm1      ;xmm6 = B
        mulps   xmm6, xmm1      ;xmm6 = B^2
        mulps   xmm6, xmm1      ;xmm6 = B^3

        addps   xmm3, xmm5
        subps   xmm3, xmm6      ;muvelet eredmenye xmm3-ban lesz tarolva

        movups  [C + ebx], xmm3 ;eredmeny tomb felepitese
        add     ebx, 16
        
        loop    .muveletek

    mov     ecx, esi
    xor     ebx, ebx
    .kiir: ;eredmeny tomb kiirasa
        xorps   xmm0, xmm0
        movss   xmm0, [C + ebx]
        call    io_writeflt
        call    io_writeln
        add     ebx, 4
        loop    .kiir

    ret

section .data
    ketto dd 2.0, 2.0, 2.0, 2.0
    negy  dd 4.0, 4.0, 4.0, 4.0
    hossz db 'Kerem a tombok hosszat: ', 0
    hiba db 'Hiba! A tomb hossza nem oszthato 4-el, a program leall', 0
    A_elemei db 'Kerem az elso tomb elemeit: ', 0
    B_elemei db 'Kerem a masodik tomb elemeit: ', 0

section .bss
    A resd 256
    B resd 256
    C resd 256