;Boda Norbert, bnim2219, 511

%include 'mio.inc'

global main

section .text
main:
    ;a, b, c beolvasasa
    mov     eax, str_a
    call    mio_writestr
    call    beolvas_hex
    mov     [a], ebx

    mov     eax, str_b
    call    mio_writestr
    call    beolvas_hex
    mov     [b], ebx

    mov     eax, str_c
    call    mio_writestr
    call    beolvas_hex
    mov     [c], ebx 

    ;szabaly kiirasa
    mov     eax, str_szabaly
    call    mio_writestr
    call    mio_writeln

    ;a, b, c kiirasa binaris formaban
    mov     eax, str_a
    call    mio_writestr
    mov     eax, [a]
    call    kiir_bin
    
    mov     eax, str_b
    call    mio_writestr
    mov     eax, [b]
    call    kiir_bin

    mov     eax, str_c
    call    mio_writestr
    mov     eax, [c]
    call    kiir_bin
    
    ;a szam az edx-ben lesz felepitve
    xor     edx, edx
    OR      edx, 0xC0000000 ;elso 2 bit 1-re allitasa

    ;A[12:12] OR C[26:26] hozzaadasa az eredmenyhez
    mov     eax, [a]
    mov     ecx, [c]
    shr     eax, 12
    shr     ecx, 26
    OR      eax, ecx
    shl     eax, 31
    shr     eax, 2
    OR      edx, eax

    ;A[31:25] XOR B[24:18] hozzaadasa az eredmenyhez
    mov     eax, [a]
    mov     ebx, [b]
    shr     eax, 25
    shr     ebx, 18
    xor     eax, ebx
    shl     eax, 25
    shr     eax, 3
    OR      edx, eax

    ;C[7:7] hozzaadasa az eredmenyhez
    mov     ecx, [c]
    shr     ecx, 7
    shl     ecx, 31
    shr     ecx, 10
    OR      edx, ecx

    ;B[31:30] AND 11 hozzaadasa az eredmenyhez
    mov     ebx, [b]
    shr     ebx, 30
    and     ebx, 11
    shl     ebx, 19
    OR      edx, ebx

    ;A[24:6] hozzaadasa az eredmenyhez
    mov     eax, [a]
    shl     eax, 7
    shr     eax, 13
    OR      edx, eax

    ;eredmeny kiirasa
    mov     eax, edx
    call    kiir_bin_space_nelkul

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

kiir_bin: ;szam kiirasa binaris formaban, negyesevel csoportositva a biteket
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

kiir_bin_space_nelkul: ;szam kiirasa binaris formaban, spacek nelkul
    mov     ecx, 32     ;32 szamjegy miatt a ciklus 32-szer fog ismetlodni
    .szamjegyekre_bontas:   ;lementi a verembe a szam utolso bitjet es shifteli jobbra a szamot
        mov     ebx, eax
        mov     edx, 1
        and     ebx, edx
        push    ebx
        shr     eax, 1
        loop    .szamjegyekre_bontas

    mov     ecx, 32
    .kiir:
        pop     eax
        add     eax, 48
        call    mio_writechar
        loop    .kiir

    call    mio_writeln
    ret

section .data
    str_a dd 'A = ', 0
    str_b dd 'B = ', 0
    str_c dd 'C = ', 0
    str_eredmeny dd 'Eredmeny: ', 0
    hibauzenet db 'Hiba: Kerem adjon uj bemenetet! ', 0
    str_szabaly dd '11, A[12:12] OR C[26:26], A[31:25] XOR B[24:18], C[7:7], B[31:30] AND 11, A[24:6]'

section .bss
    a resd 1
    b resd 1
    c resd 1
    temp resd 1