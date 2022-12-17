;Boda Norbert, bnim2219, 511
;L4 2.feladat
;Készítsünk el egy olyan IOSTR.ASM / INC modult, amely a következő eljárásokat tartalmazza:
;ReadStr(EDI vagy ESI, ECX max. hossz):()   – C-s (bináris 0-ban végződő) stringbeolvasó eljárás, <Enter>-ig olvas
;WriteStr(ESI):()                           – stringkiíró eljárás
;ReadLnStr(EDI vagy ESI, ECX):()            – mint a ReadStr() csak újsorba is lép
;WriteLnStr(ESI):()                         – mint a WriteStr() csak újsorba is lép
;NewLine():()                               – újsor elejére lépteti a kurzort

%include 'mio.inc'

global ReadStr, WriteStr, ReadLnStr, WriteLnStr, NewLine

section .text
ReadStr: ;beolvassa az esi cimmel kezdodo cimet, aminek ecx hossza lesz
    pusha
    mov     edx, ecx ;elmenti a max hosszat
    xor     ecx, ecx
    .olvas:
        xor     eax, eax
        call    mio_readchar
        
        cmp     eax, 13 ;enter utan felepiti a stringet
        je      .string_felepitese

        cmp     eax, 8  ;kiszed egy karaktert a verembol backspace eseten
        je      .backspace

        push    eax ;a beolvasott karaktereket a verembe teszi
        inc     cl
        call    mio_writechar
        jmp     .olvas

        .backspace:
            cmp     cl, 0
            je      .olvas
            call    mio_writechar
            mov     eax, 32
            call    mio_writechar
            mov     eax, 8
            call    mio_writechar
            pop     eax
            dec     cl
            jmp     .olvas

    .string_felepitese:
        cmp     ecx, 0
        je      .vege
        mov     edi, 4
        imul    edi, ecx
        sub     edi, 4
        xor     ebx, ebx
        cmp     ecx, edx ;megnezi ha tobb vagy kevesebb karaktert olvasott be, mint a max hossz
        jl      .kevesebb
        je      .felepites
        jg      .tobb

        .tobb: ;ha tobbet olvasott be, akkor csak annyit rak be a stringbe, amennyi a max hossz
            xchg    ecx, edx
            jmp     .felepites
        .kevesebb: ;ha kevesebbet olvasott be, akkor elmenti azt a szamot a max hossz helyett
            mov     edx, ecx

        .felepites: ;a verembol a karaktereket atteszi a stringbe
            mov     eax, [esp + edi]
            mov     [esi + ebx], eax
            sub     edi, 4
            inc     ebx
            loop    .felepites

    mov     [esi + ebx], byte 0
    mov     ecx, edx
    .verem_kiuritese:
        pop     eax
        loop    .verem_kiuritese

    .vege:
        popa
        ret

WriteStr: ;kiirja az esi cimmel kezdodo stringet
    pusha
    xor     ecx, ecx
    .kiir:
        cmp     [esi + ecx], byte 0 ;string veget a NULL karakter jelzi
        je      .vege

        mov     eax, [esi + ecx]
        call    mio_writechar
        inc     ecx
        jmp     .kiir

    .vege:
        popa
        ret

ReadLnStr: ;beolvassa az esi cimmel kezdodo cimet, aminek ecx hossza lesz, majd kiir egy uj sort
    pusha
    mov     edx, ecx
    xor     ecx, ecx
    .olvas:
        xor     eax, eax
        call    mio_readchar
        
        cmp     eax, 13 ;enter utan felepiti a stringet
        je      .string_felepitese

        cmp     eax, 8  ;kiszed egy karaktert a verembol backspace eseten
        je      .backspace

        push    eax ;a beolvasott karaktereket a verembe teszi
        inc     cl
        call    mio_writechar
        jmp     .olvas

        .backspace:
            cmp     cl, 0
            je      .olvas
            call    mio_writechar
            mov     eax, 32
            call    mio_writechar
            mov     eax, 8
            call    mio_writechar
            pop     eax
            dec     cl
            jmp     .olvas

    .string_felepitese:
        cmp     ecx, 0
        je      .vege
        mov     edi, 4
        imul    edi, ecx
        sub     edi, 4
        xor     ebx, ebx
        cmp     ecx, edx ;megnezi ha tobb vagy kevesebb karaktert olvasott be, mint a max hossz
        jl      .kevesebb
        je      .felepites
        jg      .tobb

        .tobb: ;ha tobbet olvasott be, akkor csak annyit rak be a stringbe, amennyi a max hossz
            xchg    ecx, edx
            jmp     .felepites
        .kevesebb: ;ha kevesebbet olvasott be, akkor elmenti azt a szamot a max hossz helyett
            mov     edx, ecx

        .felepites: ;a verembol a karaktereket atteszi a stringbe
            mov     eax, [esp + edi]
            mov     [esi + ebx], eax
            sub     edi, 4
            inc     ebx
            loop    .felepites

    mov     [esi + ebx], byte 0
    mov     ecx, edx
    .verem_kiuritese:
        pop     eax
        loop    .verem_kiuritese

    .vege:
        mov     eax, 13
        call    mio_writechar
        mov     eax, 10
        call    mio_writechar
        popa
        ret

WriteLnStr: ;kiirja az esi cimmel kezdodo stringet es uj sorba lep
    pusha
    xor     ecx, ecx
    xor     edi, edi
    .kiir:
        cmp     [esi + ecx], byte 0 ;string veget a NULL karakter jelzi
        je      .vege

        mov     eax, [esi + ecx]
        call    mio_writechar
        inc     ecx
        jmp     .kiir

    .vege:
        mov     eax, 13
        call    mio_writechar
        mov     eax, 10
        call    mio_writechar
        popa
        ret

NewLine: ;kiir egy ures sort
    pusha
    mov     eax, 13
    call    mio_writechar
    mov     eax, 10
    call    mio_writechar
    popa
    ret

