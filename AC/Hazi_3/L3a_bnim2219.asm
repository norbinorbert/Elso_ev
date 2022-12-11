;Boda Norbert, bnim2219, 511
;L3a
;Írjunk assembly eljárást, amely egy 32 bites, előjel nélküli egész számot ír ki a képernyőre bináris formában,
;kötelezően mindig 32 bináris számjegy formájában. A kiírás során csoportosítsuk négyesével a biteket. 
;Készítsünk el egy, a függvényeket alkalmazó rövid példaprogramot is, 
;amely az előző laborfeladatban szereplő hexadecimális pozitív egészet olvasó eljárást használva beolvas két számot, 
;majd kiírja a beolvasott két számot és az összegüket is binárisan.

%include 'mio.inc'

global main

section .text
main:
    mov     eax, str_beolvas_elso
    call    mio_writestr
    call    beolvas_hex     ;elso szam beolvasasa
    mov    [szam1], ebx     ;a beolvasott szamot az ebx-be menti

    mov     eax, str_beolvas_masodik
    call    mio_writestr
    call    beolvas_hex     ;masodik szam beolvasasa
    mov     [szam2], ebx
    
    mov     eax, str_szam1
    call    mio_writestr
    mov     eax, [szam1]
    call    kiir_bin    ;elso szam kiirasa binaris formaban
    
    mov     eax, str_szam2
    call    mio_writestr
    mov     eax, [szam2]
    call    kiir_bin    ;masodik szam kiirasa binaris formaban

    mov     eax, str_osszeg
    call    mio_writestr
    mov     eax, [szam1]
    mov     ebx, [szam2]
    add     eax, ebx    ;osszeg kiszamitasa
    call    kiir_bin    ;osszeg kiirasa binaris formaban

    ret

beolvas_hex: ;hex szamok beolvasasa
    mov     ebx, 0

    .olvas:
        xor     eax, eax
        call    mio_readchar
        cmp     eax, 13
        je      .vege

        cmp     eax, 48
        jl      .hiba
        cmp     eax, 57
        jg      .nagybetuk

        .szamok: ;0-9 lekezelese
            imul    ebx, 0x10
            call    mio_writechar
            sub     eax, 48
            add     ebx, eax
            jmp     .olvas

        .nagybetuk: ;A-F lekezelese
            cmp     eax, 65
            jl      .hiba
            cmp     eax, 70
            jg      .kisbetuk

            imul    ebx, 0x10
            call    mio_writechar
            sub     eax, 55
            add     ebx, eax
            jmp     .olvas

        .kisbetuk: ;a-f lekezelese
            cmp     eax, 97
            jl      .hiba
            cmp     eax, 102
            jg      .hiba

            imul    ebx, 0x10
            call    mio_writechar
            sub     eax, 87
            add     ebx, eax
            jmp     .olvas

    .hiba: ;hibauzenet kiirasa, illetve szamjegyek ujra olvasasa ha hiba tortent
        mov     eax, hibauzenet
        call    mio_writeln
        call    mio_writestr
        call    beolvas_hex
        ret

    .vege: ;kilepes a fuggvenybol
        call    mio_writeln
        ret

kiir_bin: ;szam kiirasa binaris formaban
    mov     ecx, 32     ;32 szamjegy miatt a ciklus 32-szer fog ismetlodni
    .szamjegyekre_bontas:   ;lementi a verembe a szam utolso bitjet es shifteli jobbra a szamot
        mov     ebx, eax
        mov     edx, 1
        and     ebx, edx
        push    ebx
        shr     eax, 1
        loop    .szamjegyekre_bontas

    mov     ecx, 8  ;8-szor 4 szamjegyet kell kiirni
    .kiir:
        mov     [temp], ecx
        mov     ecx, 4  
        .kiir_negy_szamjegy:
            pop     eax
            add     eax, 48
            call    mio_writechar
            loop    .kiir_negy_szamjegy

        mov     eax, 32
        call    mio_writechar   ;minden negyedik szam utan kiir egy spacet
        mov     ecx, [temp]
        loop    .kiir

    call    mio_writeln
    ret

section .data
    hibauzenet db 'Hiba: Kerem adjon uj bemenetet! ', 0
    str_beolvas_elso dd 'Kerem az elso szam szamjegyeit: ', 0
    str_beolvas_masodik dd 'Kerem a masodik szam szamjegyeit: ', 0
    str_szam1 dd 'Az elso szam binaris formaban: ', 0
    str_szam2 dd 'A masodik szam binaris formaban: ', 0
    str_osszeg dd 'Az osszeg binaris formaban: ', 0
    
section .bss
    szam1 resd 1
    szam2 resd 1
    temp resd 1