;Boda Norbert, bnim2219, 511
;L4a, 4.feladat
;beolvas egy előjeles 32 bites egész számot 10-es számrendszerben;
;kiírja a beolvasott értéket 10-es számrendszerben előjeles egészként, komplementer kódbeli ábrázolását 16-os és kettes számrendszerben;
;beolvas egy 32 bites hexa számot;
;kiírja a beolvasott értéket 10-es számrendszerben előjeles egészként, komplementer kódbeli ábrázolását 16-os és kettes számrendszerben;
;beolvas egy 32 bites bináris számot;
;kiírja a beolvasott értéket 10-es számrendszerben előjeles egészként, komplementer kódbeli ábrázolását 16-os és kettes számrendszerben;
;kiírja a három beolvasott érték összegét 10-es számrendszerben előjeles egészként, komplementer kódbeli ábrázolását 16-os és kettes számrendszerben;
;ez előző lépéseket elvégzi 64 bites értékekre is.

%include 'ionum.inc'
%include 'iostr.inc'

global main

section .text
main:
    .olvasas1: ;beolvas egy 32 bites decimalis alaku szamot
        mov     esi, beolvas_dec
        call    WriteStr
        call    ReadInt
        jnc     .kiiras1 ;ha nincs hiba akkor kiirja a szamot
        mov     esi, hibauzenet
        call    WriteLnStr ;hiba eseten kiir egy hibauzenetet es uj sorba lep
        jmp     .olvasas1 ;ha hiba tortent akkor ujra keri a szamot

    .kiiras1: ;kiirja a beolvasott 32 bites szamot
        mov     esi, kiir_dec
        call    WriteStr
        call    WriteInt ;kiirja a szamot decimalis alakban
        
        mov     esi, kiir_hex
        call    WriteStr
        call    WriteHex ;kiirja a szamot hexadecimalis alakban

        mov     esi, kiir_bin
        call    WriteStr
        call    WriteBin ;kiirja a szamot binaris alakban

    mov     ebx, eax ;elmenti a beolvasott szamot az ebx regiszterbe

    .olvasas2: ;beolvas egy 32 bites hexadecimalis alaku szamot
        call    NewLine
        mov     esi, beolvas_hex
        call    WriteStr
        call    ReadHex
        jnc     .kiiras2 ;ha nincs hiba akkor kiirja a szamot
        mov     esi, hibauzenet
        call    WriteLnStr ;hiba eseten kiir egy hibauzenetet es uj sorba lep
        jmp     .olvasas2 ;ha hiba tortent akkor ujra keri a szamot

    .kiiras2: ;kiirja a beolvasott 32 bites szamot
        mov     esi, kiir_dec
        call    WriteStr
        call    WriteInt ;kiirja a szamot decimalis alakban
        
        mov     esi, kiir_hex
        call    WriteStr
        call    WriteHex ;kiirja a szamot hexadecimalis alakban

        mov     esi, kiir_bin
        call    WriteStr
        call    WriteBin ;kiirja a szamot binaris alakban
    
    mov     ecx, eax ;elmenti a beolvasott szamot az ecx regiszterbe

    .olvasas3: ;beolvas egy 32 bites binaris alaku szamot
        call    NewLine
        mov     esi, beolvas_bin
        call    WriteStr
        call    ReadBin
        jnc     .kiiras3 ;ha nincs hiba akkor kiirja a szamot
        mov     esi, hibauzenet
        call    WriteLnStr ;hiba eseten kiir egy hibauzenetet es uj sorba lep
        jmp     .olvasas3 ;ha hiba tortent akkor ujra keri a szamot

    .kiiras3: ;kiirja a beolvasott 32 bites szamot
        mov     esi, kiir_dec
        call    WriteStr
        call    WriteInt ;kiirja a szamot decimalis alakban
        
        mov     esi, kiir_hex
        call    WriteStr
        call    WriteHex ;kiirja a szamot hexadecimalis alakban

        mov     esi, kiir_bin
        call    WriteStr
        call    WriteBin ;kiirja a szamot binaris alakban

    ;osszeadja a 3 darab 32 bites szamot es eax-ben tarolja
    add     eax, ebx
    add     eax, ecx

    call    NewLine
    mov     esi, kiir_osszeg_dec
    call    WriteStr
    call    WriteInt ;kiirja az osszeget decimalis alakban
    
    mov     esi, kiir_osszeg_hex
    call    WriteStr
    call    WriteHex ;kiirja az osszeget hexadecimalis alakban

    mov     esi, kiir_osszeg_bin
    call    WriteStr
    call    WriteBin ;kiirja az osszeget binaris alakban

    .olvasas4: ;beolvas egy 64 bites decimalis alaku szamot
        call    NewLine
        mov     esi, beolvas_dec64
        call    WriteStr
        call    ReadInt64
        jnc     .kiiras4 ;ha nincs hiba akkor kiirja a szamot
        mov     esi, hibauzenet
        call    WriteLnStr ;hiba eseten kiir egy hibauzenetet es uj sorba lep
        jmp     .olvasas4 ;ha hiba tortent akkor ujra keri a szamot

    .kiiras4: ;kiirja a beolvasott 64 bites szamot
        mov     esi, kiir_dec
        call    WriteStr
        call    WriteInt64 ;kiirja a szamot decimalis alakban
        
        mov     esi, kiir_hex
        call    WriteStr
        call    WriteHex64 ;kiirja a szamot hexadecimalis alakban

        mov     esi, kiir_bin
        call    WriteStr
        call    WriteBin64 ;kiirja a szamot binaris alakban

    mov     ebx, edx ;a 64 bites szamok osszege az ebx:ecx-ben lesz tarolva
    mov     ecx, eax

    .olvasas5: ;beolvas egy 64 bites hexadecimalis alaku szamot
        call    NewLine
        mov     esi, beolvas_hex64
        call    WriteStr
        call    ReadHex64
        jnc     .kiiras5 ;ha nincs hiba akkor kiirja a szamot
        mov     esi, hibauzenet
        call    WriteLnStr ;hiba eseten kiir egy hibauzenetet es uj sorba lep
        jmp     .olvasas5 ;ha hiba tortent akkor ujra keri a szamot

    .kiiras5: ;kiirja a beolvasott 64 bites szamot
        mov     esi, kiir_dec
        call    WriteStr
        call    WriteInt64 ;kiirja a szamot decimalis alakban
        
        mov     esi, kiir_hex
        call    WriteStr
        call    WriteHex64 ;kiirja a szamot hexadecimalis alakban

        mov     esi, kiir_bin
        call    WriteStr
        call    WriteBin64 ;kiirja a szamot binaris alakban
    
    add     ecx, eax ;a 64 bites szamok osszege az ebx:ecx-ben lesz tarolva
    adc     ebx, edx

    .olvasas6: ;beolvas egy 64 bites binaris alaku szamot
        call    NewLine
        mov     esi, beolvas_bin64
        call    WriteStr
        call    ReadBin64
        jnc     .kiiras6 ;ha nincs hiba akkor kiirja a szamot
        mov     esi, hibauzenet
        call    WriteLnStr ;hiba eseten kiir egy hibauzenetet es uj sorba lep
        jmp     .olvasas6 ;ha hiba tortent akkor ujra keri a szamot

    .kiiras6: ;kiirja a beolvasott 64 bites szamot
        mov     esi, kiir_dec
        call    WriteStr
        call    WriteInt64 ;kiirja a szamot decimalis alakban
        
        mov     esi, kiir_hex
        call    WriteStr
        call    WriteHex64 ;kiirja a szamot hexadecimalis alakban

        mov     esi, kiir_bin
        call    WriteStr
        call    WriteBin64 ;kiirja a szamot binaris alakban

    add     eax, ecx ;a 64 bites szamok osszege az ebx:ecx-ben lesz tarolva
    adc     edx, ebx

    call    NewLine
    mov     esi, kiir_osszeg_dec
    call    WriteStr
    call    WriteInt64 ;kiirja az osszeget decimalis alakban
    
    mov     esi, kiir_osszeg_hex
    call    WriteStr
    call    WriteHex64 ;kiirja az osszeget hexadecimalis alakban

    mov     esi, kiir_osszeg_bin
    call    WriteStr
    call    WriteBin64 ;kiirja az osszeget binaris alakban

    ret

section .data
    hibauzenet db 'Hiba', 0
    beolvas_dec db 'Kerek egy decimalis alaku, 32 bites szamot: ', 0
    beolvas_bin db 'Kerek egy binaris alaku, 32 bites szamot: ', 0
    beolvas_hex db 'Kerek egy hexadecimalis alaku, 32 bites szamot: ', 0
    beolvas_dec64 db 'Kerek egy decimalis alaku, 64 bites szamot: ', 0
    beolvas_bin64 db 'Kerek egy binaris alaku, 64 bites szamot: ', 0
    beolvas_hex64 db 'Kerek egy hexadecimalis alaku, 64 bites szamot: ', 0
    kiir_dec db 'Decimalis alakban a beolvasott szam: ', 0
    kiir_bin db 'Binaris alakban a beolvasott szam: ', 0
    kiir_hex db 'Hexadecimalis alakban a beolvasott szam: ', 0
    kiir_osszeg_dec db 'Decimalis alakban a 3 beolvasott szam osszege: ', 0
    kiir_osszeg_bin db 'Binaris alakban a 3 beolvasott szam osszege: ', 0
    kiir_osszeg_hex db 'Hexadecimalis alakban a 3 beolvasott szam osszege: ', 0