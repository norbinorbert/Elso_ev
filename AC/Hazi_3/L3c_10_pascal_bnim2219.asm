;Boda Norbert, bnim2219, 511
;L3c_10_pascal
;Készítsünk két assembly programot (NASM), amelyek beolvassák a szükséges karakterláncokat, 
;kiírják a felhasznált szabályt (mint üzenetet) és a beolvasott karakterláncokat külön sorokba, 
;majd előállítják és végül kiírják a művelet eredményét, ami szintén egy karakterlánc. Az eredményt nem szabad több részletben kiírni, 
;az egyetlen karakterlánc kell legyen, amit elő kell állítani kiírás előtt!
;Az egyik program PASCAL specifikus karakterláncokat (azaz string-eket, ahol a 0. karakter a hosszat jelöli) kell alkalmazzon.

%include 'mio.inc'

global main

section .text
main:
    mov     eax, str_a_olvas ;elso karakterlanc beolvasasa
    call    mio_writestr
    mov     edx, a
    call    beolvas_pascal

    mov     eax, str_b_olvas ;masodik karakterlanc beolvasasa
    call    mio_writestr
    mov     edx, b
    call    beolvas_pascal

    call    mio_writeln
    mov     eax, szabaly ;szabaly kiirasa
    call    mio_writestr
    call    mio_writeln
    call    mio_writeln

    mov     eax, str_a ;elso karakterlanc kiirasa
    call    mio_writestr
    mov     edx, a
    call    kiir_pascal

    mov     eax, str_b ;masodik karakterlanc kiirasa
    call    mio_writestr
    mov     edx, b
    call    kiir_pascal

    xor     ecx, ecx
    mov     edx, a
    mov     cl, [edx]
    mov     al, [edx + ecx] ;al-be kerul az "a" string utolso karaktere
    mov     edx, b
    mov     cl, [edx]
    mov     bl, [edx + ecx] ;bl-be kerul a "b" string utolso karaktere

    mov     edx, a
    mov     esi, 1
    mov     ecx, c
    mov     edi, 1
    .osszehasonlit_a: ;A[utolsó] < A[i]
        cmp     [edx + esi], al
        jg      .osszehasonlit_b
        jle     .kovetkezo

    .osszehasonlit_b: ;A[i] < B[utolsó]
        cmp     [edx + esi], bl
        jl      .hozzaad
        jge     .kovetkezo

    .hozzaad: ;helyes karakter hozzaadasa "c" stringhez
        mov     ah, [edx + esi]
        mov     [ecx + edi], ah
        inc     edi

    .kovetkezo: ;kovetkezo karakter vizsgalasa
        inc     esi
        mov     ah, [edx + esi]
        cmp     ah, 0
        jne     .osszehasonlit_a

    mov     edx, b
    mov     esi, 1

    .c_felepitese_abc_sorrend:
        mov     ah, [edx + esi]
        cmp     ah, 0
        je      .vege ;ha az elso karakter NULL, akkor a string vegere ertunk
        inc     esi
        mov     al, [edx + esi]
        inc     esi
        cmp     al, 0
        je      .utolso_karakter ;ha a masodik karakter NULL, akkor csak az elsot kell hozzaadni a c-hez
        cmp     ah, al
        jle     .abc_sorrend
        jg      .abc_sorrend2

    .abc_sorrend: ;ha abc sorrendben van az al, ah, akkor hozzatesszi a c-hez
        mov     [ecx + edi], ah
        inc     edi
        mov     [ecx + edi], al
        inc     edi
        jmp     .c_felepitese_forditott_sorrend

    .abc_sorrend2: ;ha nincs abc sorrendben az al es ah akkor forditva teszi hozza a c-hez
        mov     [ecx + edi], al
        inc     edi
        mov     [ecx + edi], ah
        inc     edi
        jmp     .c_felepitese_forditott_sorrend

    .c_felepitese_forditott_sorrend:
        mov     ah, [edx + esi]
        cmp     ah, 0
        je      .vege ;ha az elso karakter NULL, akkor a string vegere ertunk
        inc     esi
        mov     al, [edx + esi]
        inc     esi
        cmp     al, 0
        je      .utolso_karakter ;ha a masodik karakter NULL, akkor csak az elsot kell hozzaadni a c-hez
        cmp     ah, al
        jg      .forditott_sorrend
        jle     .forditott_sorrend2

    .forditott_sorrend: ;ha abc sorrendben van az al, ah, akkor forditva teszi hozza a c-hez
        mov     [ecx + edi], ah
        inc     edi
        mov     [ecx + edi], al
        inc     edi
        jmp     .c_felepitese_abc_sorrend

    .forditott_sorrend2: ;ha nincs abc sorrendben az al es ah akkor hozzatesszi a c-hez
        mov     [ecx + edi], al
        inc     edi
        mov     [ecx + edi], ah
        inc     edi
        jmp     .c_felepitese_abc_sorrend

    .utolso_karakter: ;ha a masodik karakter NULL es az elso nem, akkor az elsot hozzaadja a c-hez
        mov     [ecx + edi], ah
        inc     edi
        mov     al, 0
        mov     [ecx + edi], al

    .vege: ;beteszi a string elejere a hosszat es kiirja a c stringet
        mov     edx, c
        mov     eax, edi
        dec     eax
        mov     [edx + 0], al
        mov     eax, str_eredmeny
        call    mio_writestr
        call    kiir_pascal

    ret

beolvas_pascal:  ;beolvas egy pascal tipusu karakterlancot
    xor     eax, eax
    xor     ebx, ebx
    inc     ebx
    .olvas: ;karaktereket sorra teszi be a karakterlancba
        call    mio_readchar
        cmp     al, 13
        je      .vege
        cmp     al, 8
        je      .backspace

        call    mio_writechar
        mov     [edx+ebx], al ;beteszi a beolvasott karaktert a karakterlancba
        inc     ebx
        jmp     .olvas

    .backspace: ;backspace eseten kitorli a jelenlegi karaktert
        cmp     ebx, 1
        je      .olvas ;ha meg nincs karakter beolvasva akkor nem csinal semmit

        call    mio_writechar ;kiirja a backspacet
        mov     al, 32
        call    mio_writechar ;kiir egy spacet
        dec     ebx
        mov     al, 0
        mov     [edx+ebx], al ;lecsereli a jelenlegi karaktert egy NULL karakterre
        mov     al, 8
        call    mio_writechar ;kiirja a backspacet
        jmp     .olvas

    .vege: ;string elejere berakja, hogy hany karakterbol all es kiir egy uj sort
        dec     ebx
        mov     [edx+0], bl
        mov     al, 10
        call    mio_writechar
        ret

kiir_pascal: ;kiir egy pascal tipusu karakterlancot
    xor     eax, eax
    xor     ebx, ebx
    xor     ecx, ecx
    inc     ebx
    mov     cl, [edx + 0]
    .kiir:  ;karakterenkent kiirja a stringet
        mov     al, [edx+ebx]
        inc     ebx
        call    mio_writechar
        loop    .kiir

    .vege: ;kiir egy uj sort
        mov     al, 10
        call    mio_writechar
        ret

section .data
    str_a_olvas dd 'Adja meg az elso karakterlancot: ', 0
    str_a dd 'Az elso karakterlanc: ', 0
    str_b_olvas dd 'Adja meg a masodik karakterlancot: ', 0
    str_b dd 'A masodik karakterlanc: ', 0
    str_eredmeny dd 'Eredmeny karakterlanc: ', 0
    szabaly dd 'Szabaly: [azok a karakterek A-bol, amelyek ASCII kod szerint az A utolso es a B utolso karaktere kozt vannak (azaz, amelyekre A[utolso] < A[i] < B[utolso]) (pl. A="abmnxd", B="prst" =>"mn")] + [karakterparokra osztjuk a B-t, az elso parban a ket karaktert abc sorrendbe tesszuk (ASCII kod szerint), a masodikban forditott abc sorrendbe, majd ujra abc sorrendbe, ... Ha az utolso karakternek nincs párja, akkor marad ahogy volt (pl. baxycdu => abyxcdu)]. A es B csak betuket tartalmaz, mas karaktereket nem kell lekezelni.', 0

section .bss
    a resb 256
    b resb 256
    c resb 256