;Boda Norbert, bnim2219, 511
;L2
;Írjunk meg egy-egy ASM alprogramot 32 bites, előjeles egész, illetve 32 bites, pozitív hexa számok beolvasására és kiírására.
; Készítsünk főprogramot, amely ezt a négy függvényt alkalmazza:
;   -beolvas egy számot decimális egészként,
;   -kiíratja decimális (előjeles egész) alakban,
;   -kiíratja hexadecimális (a szám komplementerkódbeli ábrázolása) alakban,
;   -beolvas egy másik számot hexadecimális egészként (ezt egy egész komplementerkódbeli ábrázolásának tekintjük),
;   -kiíratja decimális (előjeles egész) alakban,
;   -kiíratja hexadecimális alakban,
;   -a két számot összeadja,
;   -az eredményt kiíratja decimális (előjeles egész) alakban,
;   -az eredményt kiíratja hexadecimális alakban.

%include 'mio.inc'

global main

section .text
main:
    ;decimalis egesz beolvasasa
    call    beolvas_dec

    ;kiiras decimalis formaban
    mov     eax, str_dec_szam
    call    mio_writestr
    mov     eax, [szam_dec]
    call    kiir_dec
    call    mio_writeln
    
    ;kiiras hexadecimalis formaban
    mov     eax, str_hex_szam
    call    mio_writestr
    mov     eax, [szam_dec]
    call    kiir_hex
    call    mio_writeln

    ;hexadecimalis egesz beolvasasa
    call    beolvas_hex
    
    ;kiiras decimalis formaban
    mov     eax, str_dec_szam
    call    mio_writestr
    mov     eax, [szam_hex]
    call    kiir_dec
    call    mio_writeln

    ;kiiras hexadecimalis formaban
    mov     eax, str_hex_szam
    call    mio_writestr
    mov     eax, [szam_hex]
    call    kiir_hex
    call    mio_writeln

    ;ket szam osszeadasa
    mov     eax, [szam_dec]
    mov     ebx, [szam_hex]
    add     eax, ebx
    mov     [osszeg], eax
    call    mio_writeln

    ;osszeg kiirasa decimalis formaban
    mov     eax, str_osszeg_dec
    call    mio_writestr
    mov     eax, [osszeg]
    call    kiir_dec
    call    mio_writeln

    ;osszeg kiirasa hexadecimalis formaban
    mov     eax, str_osszeg_hex
    call    mio_writestr
    mov     eax, [osszeg]
    call    kiir_hex
    call    mio_writeln

    ret


beolvas_dec: ;decimalis szamok beolvasasa
    xor     ebx, ebx
    xor     ecx, ecx
    mov     eax, str_beolvas_dec
    call    mio_writeln
    call    mio_writestr

    .olvas:
        xor     eax, eax
        call    mio_readchar
        ;ellenorzes, ha az elso karakter "-"
        cmp     eax, 45
        jne     .szam_olvasasa
        call    mio_writechar
        inc     ecx
        ;szam beolvasasa ha az elobb "-" volt a bemenet
        xor     eax, eax
        call    mio_readchar

        .szam_olvasasa:
            cmp     eax, 13
            je      .vege

            ;ervenytelen karakterek kezelese
            cmp     eax, 48
            jl      .hiba
            cmp     eax, 57
            jg      .hiba

            imul    ebx, 10
            call    mio_writechar
            sub     eax, 48

            cmp     ecx, 1
            je      .negativ

        .pozitiv: ;pozitiv szam eseten osszeadasokat vegez
            add     ebx, eax
            xor     eax, eax
            call    mio_readchar
            jmp     .szam_olvasasa

        .negativ: ;negativ szam eseten kivonasokat vegez
            sub     ebx, eax
            xor     eax, eax
            call    mio_readchar
            jmp     .szam_olvasasa

    .hiba: ;hibauzenet kiirasa, illetve szamjegyek ujra olvasasa ha hiba tortent
        mov     eax, hibauzenet
        call    mio_writeln
        call    mio_writestr
        call    beolvas_dec
        ret

    .vege: ;kilepes a fuggvenybol
        call    mio_writeln
        mov     [szam_dec], ebx
        ret


beolvas_hex: ;hex szamok beolvasasa
    mov     ebx, 0
    mov     eax, str_beolvas_hex
    call    mio_writeln
    call    mio_writestr

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
        mov     [szam_hex], ebx
        ret


kiir_dec: ;szam kiirasa decimalis formaban
    cmp     eax, 0
    jge      .kiiras_elokeszulet

    ;"-" kiirasa negativ szam eseten, majd eax atalakitasa pozitiv szamba, hogy a maradekos osztas konnyebb legyen
    mov     [temp], eax
    mov     eax, 45
    call    mio_writechar
    mov     eax, [temp]
    neg     eax

    .kiiras_elokeszulet:
        mov     ebx, 10
        xor     ecx, ecx

    .elment_maradek: ;addig osztja a szamot 10-el amig 0 marad, illetve elmenti a maradekot
        cdq
        idiv    ebx
        push    edx
        inc     ecx
        cmp     eax, 0
        jne     .elment_maradek

    .kiir_szam: ;kiirja karakterenkent a szamot
        pop     eax
        add     eax, 48
        call    mio_writechar
        loop    .kiir_szam

    ret

kiir_hex: ;szam kiirasa hexadecimalis formaban
    cmp     eax, 0
    jge     .kiiras_elokeszulet

    ;szam atalakitasa komplementerkodbeli abrazolasra ha negativ
    mov     edx, 0xFFFFFFFF
    neg     eax
    sub     edx, eax
    add     edx, 1
    mov     eax, edx

    .kiiras_elokeszulet:
        mov     ebx, 0x10
        mov     ecx, 8

    .elment_maradek: ;8-szor osztja a szamot 0x10-el, mert 8 karaktert kell majd kiirni, illetve elmenti a maradekot
        xor     edx, edx
        div     ebx
        push    edx
        loop     .elment_maradek

    ;"0x" kiirasa 
    mov     eax, str_elotag
    call    mio_writestr

    mov     ecx, 8
    .kiir_szam: ;kiirja karakterenkent a szamot
        pop     eax
        cmp     eax, 10
        jl      .szamok
        jge     .hex

        .szamok:
            add     eax, 48
            call    mio_writechar
            loop    .kiir_szam
            ret

        .hex:
            add     eax, 55
            call    mio_writechar
            loop    .kiir_szam
            ret

section .data
    str_beolvas_dec db 'Kerem a decimalis szam szamjegyeit: ', 0
    str_beolvas_hex db 'Kerem a hexadecimalis szam szamjegyeit: ', 0
    str_dec_szam db 'Decimalis alakban a szam = ', 0
    str_hex_szam db 'Hexadecimalis alakban a szam = ', 0
    str_osszeg_dec db 'A ket szam osszege decimalis alakban = ', 0
    str_osszeg_hex db 'A ket szam osszege hexadecimalis alakban = ', 0
    hibauzenet db 'Hiba: Kerem adjon uj bemenetet! ', 0
    str_elotag db '0x'

section .bss
    szam_dec resd 1
    szam_hex resd 1
    osszeg resd 1
    temp resd 1