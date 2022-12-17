;Boda Norbert, bnim2219, 511
;L4 3.feladat
;Készítsük el a következő stringkezelő eljárásokat és helyezzük el őket egy STRINGS.ASM / INC nevű modulba.
;StrLen(ESI):(EAX)            – EAX-ben visszatéríiti az ESI által jelölt string hosszát, kivéve a bináris 0-t
;StrCat(EDI, ESI):()          – összefűzi az ESI és EDI által jelölt stringeket (azaz az ESI által jelöltet az EDI után másolja)
;StrUpper(ESI):()             – nagybetűssé konvertálja az ESI stringet
;StrLower(ESI):()             – kisbetűssé konvertálja az ESI stringet
;StrCompact(ESI, EDI):()      – EDI-be másolja át az ESI stringet, kivéve a szóköz, tabulátor (9), kocsivissza (13) és soremelés (10) karaktereket

%include 'mio.inc'

global StrLen, StrCat, StrUpper, StrLower, StrCompact

section .text
StrLen: ;EAX-ben visszatéríiti az ESI által jelölt string hosszát, kivéve a bináris 0-t
    push    ebx
    push    ecx
    push    edx
    push    edi
    push    esi

    xor     ebx, ebx
    xor     eax, eax

    .szamolas:
        cmp     [esi + ebx], byte 0
        je      .vege
        inc     eax
        inc     ebx
        jmp     .szamolas

    .vege:
        pop     esi
        pop     edi
        pop     edx
        pop     ecx
        pop     ebx
        ret

StrCat: ;összefűzi az ESI és EDI által jelölt stringeket (azaz az ESI által jelöltet az EDI után másolja)
    pusha
    xchg    esi, edi
    call    StrLen
    xchg    esi, edi
    xor     ebx, ebx
    .osszefuz:
        cmp     [esi + ebx], byte 0
        je      .vege

        mov     ecx, [esi + ebx]
        mov     [edi + eax], ecx
        inc     eax
        inc     ebx
        jmp     .osszefuz

    .vege:
        mov [edi + eax], byte 0
        popa
        ret

StrUpper: ;nagybetűssé konvertálja az ESI stringet
    pusha
    xor     eax, eax
    dec     eax

    .konvertal:
        inc     eax
        cmp     [esi + eax], byte 0
        je      .vege

        cmp     [esi + eax], byte 97
        jl      .konvertal

        cmp     [esi + eax], byte 122
        jg      .konvertal

        mov     ecx, [esi + eax]
        sub     ecx, 32
        mov     [esi + eax], ecx
        jmp     .konvertal

    .vege:
        popa
        ret

StrLower: ;kisbetűssé konvertálja az ESI stringet
    pusha
    xor     eax, eax
    dec     eax

    .konvertal:
        inc     eax
        cmp     [esi + eax], byte 0
        je      .vege

        cmp     [esi + eax], byte 65
        jl      .konvertal

        cmp     [esi + eax], byte 90
        jg      .konvertal

        mov     ecx, [esi + eax]
        add     ecx, 32
        mov     [esi + eax], ecx
        jmp     .konvertal

    .vege:
        popa
        ret

StrCompact: ;EDI-be másolja át az ESI stringet, kivéve a szóköz, tabulátor (9), kocsivissza (13) és soremelés (10) karaktereket
    pusha
    xor     eax, eax
    xor     edx, edx
    dec     eax

    .masol:
        inc     eax
        cmp     [esi + eax], byte 0
        je      .vege

        cmp     [esi + eax], byte 9
        je      .masol

        cmp     [esi + eax], byte 10
        je      .masol

        cmp     [esi + eax], byte 13
        je      .masol

        cmp     [esi + eax], byte 32
        je      .masol

        mov     ecx, [esi + eax]
        mov     [edi + edx], ecx
        inc     edx
        jmp     .masol

    .vege:
        popa
        ret