;Boda Norbert, bnim2219, 511
;L4, 1. feladat
;Készítsünk el egy olyan saját IONUM.ASM / INC modult, amely a következő eljárásokat tartalmazza, a megadott pontos paraméterezéssel
;ReadInt():(EAX)            – 32 bites előjeles egész beolvasása
;WriteInt(EAX):()           – 32 bites előjeles egész kiírása
;ReadInt64():(EDX:EAX)      – 64 bites előjeles egész beolvasása
;WriteInt64(EDX:EAX):()     – 64 bites előjeles egész kiírása
;ReadBin():(EAX)            – 32 bites bináris pozitív egész beolvasása
;WriteBin(EAX):()           – 32 bites bináris pozitív egész kiírása
;ReadBin64():(EDX:EAX)      – 64 bites bináris pozitív egész beolvasása
;WriteBin64(EDX:EAX):()     – 64 bites bináris pozitív egész kiírása
;ReadHex():(EAX)            – 32 bites pozitív hexa beolvasása
;WriteHex(EAX):()           – 32 bites pozitív hexa kiírása
;ReadHex64():(EDX:EAX)      – 64 bites pozitív hexa beolvasása
;WriteHex64(EDX:EAX):()     – 64 bites pozitív hexa kiírása

%include 'mio.inc'
%include 'iostr.inc'

global ReadInt, WriteInt, ReadBin, WriteBin, ReadHex, WriteHex
global ReadInt64, WriteInt64, ReadBin64, WriteBin64, ReadHex64, WriteHex64

section .text
ReadInt: ;decimalis szam beolvasasa
    push    ebx
    push    ecx
    push    edx
    push    edi
    push    esi

    xor     edx, edx
    xor     ecx, ecx
    xor     ebx, ebx
    xor     edi, edi

    .olvas:
        xor     eax, eax
        call    mio_readchar
        
        cmp     eax, 13 ;enter utan felepiti a szamot
        je      .szam_felepitese

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

    .szam_felepitese:
        mov     esi, 4
        imul    esi, ecx
        sub     esi, 4
        mov     dh, [esp + esi]
        cmp     dh, 45 ;ellenorzi, ha az elso karakter "-" volt
        jne     .felepites_elokeszulet_1
        mov     edi, 1 ;ha "-" volt, akkor edi=1
        cmp     esi, 0 
        je      .felepites_elokeszulet_1 ;ha "-" az egyetlen karakter akkor elkezdi felepiteni a szamot
        sub     esi, 4 
        jmp     .felepites_elokeszulet_2 ;ha "-" karakteren kivul volt mas is beolvasva akkor onnan kezdi a szam felepiteset

        .felepites_elokeszulet_1:
            mov     dh, cl
            jmp     .felepites

        .felepites_elokeszulet_2:
            mov     dh, cl
            dec     cl

        .felepites:
            mov     al, [esp + esi]
            sub     esi, 4
            ;hibas karakterek ellenorzese
            cmp     eax, 48
            jl      .hiba
            cmp     eax, 57
            jg      .hiba

            cmp     edi, 1 ;ha az edi=1, akkor a felepites soran kivonasokat vegez, mert a szam negativ kell legyen
            je      .negativ

            .pozitiv: ;ha a karakter szam akkor hozzaadja az eredmenyhez
            imul    ebx, 10
            jo      .hiba ;tulcsordulas ellenorzese
            sub     eax, 48
            add     ebx, eax
            jo      .hiba ;tulcsordulas ellenorzese

            loop    .felepites
            jmp     .vege

            .negativ: ;ha a karakter szam akkor kivonja az eredmenybol
            imul    ebx, 10
            jo      .hiba ;tulcsordulas ellenorzese
            sub     eax, 48
            sub     ebx, eax
            jo      .hiba ;tulcsordulas ellenorzese
            
            loop    .felepites
            jmp     .vege

        .hiba: ;hiba eseten dl 1 lesz
            xor     dl, dl
            inc     dl
            loop    .felepites

    .vege: ;kilepes a fuggvenybol
        xor     ecx, ecx
        mov     cl, dh
        .verem_uritese:
            pop     eax
            loop    .verem_uritese

        mov     eax, 10
        call    mio_writechar
        cmp     dl, 1 ;ha dl=1 akkor hiba tortent
        jne      .vege_hiba_nelkul

        mov     eax, 0
        stc ;CF beallitasa, ezzel van a hiba jelezve a foprogramnak
        pop     esi
        pop     edi
        pop     edx
        pop     ecx
        pop     ebx
        ret

        .vege_hiba_nelkul:
            clc ;CF uritese, ha veletlen beallitva maradt
            mov     eax, ebx
            pop     esi
            pop     edi
            pop     edx
            pop     ecx
            pop     ebx
            ret

WriteInt: ;szam kiirasa decimalis formaban
    pusha
    cmp     eax, 0
    jge     .kiiras_elokeszulet

    ;"-" kiirasa negativ szam eseten, majd eax atalakitasa pozitiv szamba, hogy a maradekos osztas konnyebb legyen
    mov     ebx, eax
    mov     eax, 45
    call    mio_writechar
    mov     eax, ebx
    neg     eax

    .kiiras_elokeszulet:
        mov     ebx, 10
        xor     ecx, ecx

    .elment_maradek: ;addig osztja a szamot 10-el amig 0 marad, illetve elmenti a maradekot
        xor     edx, edx
        div     ebx
        push    edx
        inc     ecx
        cmp     eax, 0
        jne     .elment_maradek

    .kiir_szam: ;kiirja karakterenkent a szamot
        pop     eax
        add     eax, 48
        call    mio_writechar
        loop    .kiir_szam

    mov     al, 10  ;ures sor kiirasa
    call    mio_writechar
    popa
    ret

ReadInt64: ;64 bites decimalis szam beolvasasa
    push    ebx
    push    ecx
    push    edi
    push    esi
    clc
    mov     [hiba], byte 0

    ;karakterek beolvasasa az esi cimre
    mov     esi, beolvas_64
    mov     ecx, 256
    call    ReadStr

    xor     ebx, ebx
    mov     [temp], ebx
    mov     ebx, 10
    xor     eax, eax
    xor     edx, edx
    xor     edi, edi
    cmp     [esi + edi], byte 45
    jne     .szam_felepitese
    inc     edi

    .szam_felepitese:
        ;mivel egy stringkent volt beolvasva a szam, ezert a NULL karakter jelzi a string veget
        cmp     [esi + edi], byte 0
        je      .vege
        ;hibas karakterek kezelese
        cmp     [esi + edi], byte 48
        jl      .hiba
        cmp     [esi + edi], byte 57
        jg      .hiba

        ;megfelelo muveletek elvegzese a szam felepitesehez
        xor     edx, edx
        mov     ebx, 10
        mul     ebx
        mov     ecx, edx
        mov     edx, [temp]
        imul    edx, 10
        jo      .hiba
        add     edx, ecx
        jo      .hiba
        mov     [temp], edx

        xor     ebx, ebx
        mov     bl, [esi + edi]
        sub     ebx, byte 48
        add     eax, ebx
        jnc     .felepites_folytatasa
        add     edx, 1
        jo      .hiba
        mov     [temp], edx
        sub     eax, 0x80000000

        .felepites_folytatasa:
            inc     edi
            jmp     .szam_felepitese

    .hiba: ;hiba eseten [hiba] 1 lesz
            mov     [hiba], byte 1
            jmp     .vege

    .vege: ;kilepes a fuggvenybol
        call    NewLine
        mov     edx, [temp]
        cmp     [esi], byte 45
        jne     .pozitiv
        not     edx
        not     eax
        add     eax, 1
        adc     edx, 0

        .pozitiv:
            cmp     [hiba], byte 1 ;ha [hiba]=1 akkor hiba tortent
            jne      .vege_hiba_nelkul

        stc ;CF beallitasa, ezzel van a hiba jelezve a foprogramnak
        pop     esi
        pop     edi
        pop     ecx
        pop     ebx
        ret

        .vege_hiba_nelkul:
            clc ;CF uritese, ha veletlen beallitva maradt
            pop     esi
            pop     edi
            pop     ecx
            pop     ebx
            ret

WriteInt64: ;64 bites szam kiirasa decimalis formaban
    pusha
    cmp     edx, 0
    jge     .kiiras_elokeszulet

    ;"-" kiirasa negativ szam eseten, majd edx:eax atalakitasa pozitiv szamba, hogy a maradekos osztas konnyebb legyen
    mov     ebx, eax
    mov     eax, 45
    call    mio_writechar
    mov     eax, ebx
    not     edx
    not     eax
    add     eax, 1
    adc     edx, 0

    .kiiras_elokeszulet:
        mov     ebx, 10
        xor     ecx, ecx

    .elment_maradek: ;addig osztja a szamot 10-el amig 0 marad, illetve elmenti a maradekot
        mov     esi, edx
        mov     edi, eax
        mov     eax, edx
        xor     edx, edx
        idiv    ebx
        mov     esi, eax
        mov     eax, edi
        div     ebx
        push    edx
        mov     edx, esi
        inc     ecx

        cmp     edx, 0
        jne     .elment_maradek
        cmp     eax, 0
        jne     .elment_maradek

    .kiir_szam: ;kiirja karakterenkent a szamot
        pop     eax
        add     eax, 48
        call    mio_writechar
        loop    .kiir_szam

    mov     al, 10  ;ures sor kiirasa
    call    mio_writechar
    popa
    ret

ReadBin: ;binaris szam beolvasasa
    push    ebx
    push    ecx
    push    edx
    push    edi
    push    esi

    xor     edx, edx
    xor     ecx, ecx
    xor     ebx, ebx
    xor     edi, edi

    .olvas:
        xor     eax, eax
        call    mio_readchar
        
        cmp     eax, 13 ;enter utan felepiti a szamot
        je      .szam_felepitese

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

    .szam_felepitese:
        mov     esi, 4
        imul    esi, ecx
        sub     esi, 4

        xor     eax, eax
        mov     dh, cl

        .felepites:
            mov     al, [esp + esi]
            sub     esi, 4
            ;hibas karakterek ellenorzese
            cmp     eax, 48
            jl      .hiba
            cmp     eax, 49
            jg      .hiba

            ;ha a karakter 0 vagy 1 akkor hozzaadja az eredmenyhez
            shl     ebx, 1
            jc      .hiba ;tulcsordulas ellenorzese
            sub     eax, 48
            or      ebx, eax

        loop    .felepites
        jmp     .vege

        .hiba: ;hiba eseten dl 1 lesz
            xor     dl, dl
            inc     dl
            loop    .felepites

    .vege: ;kilepes a fuggvenybol
        xor     ecx, ecx
        mov     cl, dh
        .verem_uritese:
            pop     eax
            loop    .verem_uritese

        mov     eax, 10
        call    mio_writechar
        cmp     dl, 1 ;ha dl=1 akkor hiba tortent
        jne      .vege_hiba_nelkul

        mov     eax, 0
        stc ;CF beallitasa, ezzel van a hiba jelezve a foprogramnak
        pop     esi
        pop     edi
        pop     edx
        pop     ecx
        pop     ebx
        ret

        .vege_hiba_nelkul:
            clc ;CF uritese, ha veletlen beallitva maradt
            mov     eax, ebx
            pop     esi
            pop     edi
            pop     edx
            pop     ecx
            pop     ebx
            ret
WriteBin: ;szam kiirasa binaris formaban
    pusha
    mov     ecx, 32     ;32 szamjegy miatt a ciklus 32-szer fog ismetlodni
    .szamjegyekre_bontas:   ;lementi a verembe a szam utolso bitjet es shifteli jobbra a szamot
        mov     ebx, eax
        mov     edx, 1
        and     ebx, edx
        push    ebx
        shr     eax, 1
        loop    .szamjegyekre_bontas

    mov     ecx, 32
    .kiir:  ;kiveszi a vermbol a szamjegyeket es kiirja oket
        pop     eax
        add     eax, 48
        call    mio_writechar
        loop    .kiir

    mov     al, 10 ;ures sor kiirasa
    call    mio_writechar
    popa
    ret

ReadBin64: ;64 bites binaris szam beolvasasa
    push    ebx
    push    ecx
    push    edi
    push    esi

    xor     edx, edx
    xor     ecx, ecx
    xor     ebx, ebx
    xor     edi, edi

    .olvas:
        xor     eax, eax
        call    mio_readchar
        
        cmp     eax, 13 ;enter utan felepiti a szamot
        je      .szam_felepitese

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

    .szam_felepitese:
        mov     esi, 4
        imul    esi, ecx
        sub     esi, 4

        xor     edi, edi
        xor     eax, eax
        mov     dh, cl

        .felepites:
            mov     al, [esp + esi]
            sub     esi, 4
            ;hibas karakterek ellenorzese
            cmp     eax, 48
            jl      .hiba
            cmp     eax, 49
            jg      .hiba

            ;ha a karakter 0 vagy 1 akkor hozzaadja az eredmenyhez
            shl     edi, 1
            jc      .hiba ;tulcsordulas ellenorzese
            shl     ebx, 1
            adc     edi, 0
            sub     eax, 48
            or      ebx, eax

        loop    .felepites
        jmp     .vege

        .hiba: ;hiba eseten dl 1 lesz
            xor     dl, dl
            inc     dl
            loop    .felepites

    .vege: ;kilepes a fuggvenybol
        xor     ecx, ecx
        mov     cl, dh
        .verem_uritese:
            pop     eax
            loop    .verem_uritese

        mov     eax, 10
        call    mio_writechar
        cmp     dl, 1 ;ha dl=1 akkor hiba tortent
        jne      .vege_hiba_nelkul

        mov     eax, 0
        stc ;CF beallitasa, ezzel van a hiba jelezve a foprogramnak
        pop     esi
        pop     edi
        pop     ecx
        pop     ebx
        ret

        .vege_hiba_nelkul:
            clc ;CF uritese, ha veletlen beallitva maradt
            mov     eax, ebx
            mov     edx, edi
            pop     esi
            pop     edi
            pop     ecx
            pop     ebx
            ret
WriteBin64: ;64 bites szam kiirasa binaris formaban
    pusha
    mov     esi, edx
    mov     ecx, 32     ;32 szamjegy miatt a ciklus 32-szer fog ismetlodni
    .szamjegyekre_bontas:   ;lementi a verembe a szam utolso bitjet es shifteli jobbra a szamot
        mov     ebx, eax
        mov     edx, 1
        and     ebx, edx
        push    ebx
        shr     eax, 1
        loop    .szamjegyekre_bontas

    mov     eax, esi
    mov     ecx, 32
    .szamjegyekre_bontas2:
        mov     ebx, eax
        mov     edx, 1
        and     ebx, edx
        push    ebx
        shr     eax, 1
        loop    .szamjegyekre_bontas2

    mov     ecx, 64
    .kiir:  ;kiveszi a vermbol a szamjegyeket es kiirja oket
        pop     eax
        add     eax, 48
        call    mio_writechar
        loop    .kiir

    mov     al, 10 ;ures sor kiirasa
    call    mio_writechar
    popa
    ret

ReadHex: ;hexadecimalis szam beolvasasa
    push    ebx
    push    ecx
    push    edx
    push    edi
    push    esi

    xor     edx, edx
    xor     ecx, ecx
    xor     ebx, ebx
    xor     edi, edi

    .olvas:
        xor     eax, eax
        call    mio_readchar
        
        cmp     eax, 13 ;enter utan felepiti a szamot
        je      .szam_felepitese

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

    .szam_felepitese:
        mov     esi, 4
        imul    esi, ecx
        sub     esi, 4
        xor     eax, eax
        mov     dh, cl

        .felepites:
            mov     al, [esp + esi]
            sub     esi, 4
            .szamok: ;megnezi ha a jelenlegi karakter szam, vagy szamnal nagyobb ASCII kodot tartalmaz
                cmp     eax, 48
                jl      .hiba
                cmp     eax, 57
                jg      .nagybetuk

                sub     eax, 48
                jmp     .hozzaad

            .nagybetuk:;megnezi ha a jelenlegi karakter nagybetu vagy nagybetunel nagyobb ASCII kodot tartalmaz
                cmp     eax, 65
                jl      .hiba
                cmp     eax, 70
                jg      .kisbetuk
                
                sub     eax, 55
                jmp     .hozzaad

            .kisbetuk: ;megnezi ha a jelenlegi karakter kisbetu
                cmp     eax, 97
                jl      .hiba
                cmp     eax, 102
                jg      .hiba

                sub     eax, 87
                jmp     .hozzaad

            .hozzaad:;ha a karakter ervenyes akkor hozzaadja az eredmenyhez
                mov     edi, ecx
                mov     ecx, 4
                .shift:
                    shl     ebx, 1
                    jc      .hibas_shift
                    loop    .shift
                
                mov     ecx, edi
                or      ebx, eax

            loop    .felepites
            jmp     .vege

        .hibas_shift:
            mov     ecx, edi
            xor     dl, dl
            inc     dl
            loop    .felepites

        .hiba: ;hiba eseten dl 1 lesz
            xor     dl, dl
            inc     dl
            loop    .felepites

    .vege: ;kilepes a fuggvenybol
        xor     ecx, ecx
        mov     cl, dh
        .verem_uritese:
            pop     eax
            loop    .verem_uritese

        mov     eax, 10
        call    mio_writechar
        cmp     dl, 1 ;ha dl=1 akkor hiba tortent
        jne      .vege_hiba_nelkul

        mov     eax, 0
        stc ;CF beallitasa, ezzel van a hiba jelezve a foprogramnak
        pop     esi
        pop     edi
        pop     edx
        pop     ecx
        pop     ebx
        ret

        .vege_hiba_nelkul:
            clc ;CF uritese, ha veletlen beallitva maradt
            mov     eax, ebx
            pop     esi
            pop     edi
            pop     edx
            pop     ecx
            pop     ebx
            ret

WriteHex: ;szam kiirasa hexadecimalis formaban
    pusha
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

            mov     al, 10 ;ures sor kiirasa
            call    mio_writechar
            popa
            ret

        .hex:
            add     eax, 55
            call    mio_writechar
            loop    .kiir_szam

            mov     al, 10 ;ures sor kiirasa
            call    mio_writechar
            popa
            ret

ReadHex64: ;64 bites hexadecimalis szam beolvasasa
    push    ebx
    push    ecx
    push    edi
    push    esi

    xor     edx, edx
    xor     ecx, ecx
    xor     ebx, ebx
    xor     edi, edi

    .olvas:
        xor     eax, eax
        call    mio_readchar
        
        cmp     eax, 13 ;enter utan felepiti a szamot
        je      .szam_felepitese

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

    .szam_felepitese:
        mov     esi, 4
        imul    esi, ecx
        sub     esi, 4
        xor     eax, eax
        mov     dh, cl
        xor     edi, edi
        
        .felepites:
            mov     al, [esp + esi]
            sub     esi, 4
            .szamok: ;megnezi ha a jelenlegi karakter szam, vagy szamnal nagyobb ASCII kodot tartalmaz
                cmp     eax, 48
                jl      .hiba
                cmp     eax, 57
                jg      .nagybetuk

                sub     eax, 48
                jmp     .hozzaad

            .nagybetuk:;megnezi ha a jelenlegi karakter nagybetu vagy nagybetunel nagyobb ASCII kodot tartalmaz
                cmp     eax, 65
                jl      .hiba
                cmp     eax, 70
                jg      .kisbetuk
                
                sub     eax, 55
                jmp     .hozzaad

            .kisbetuk: ;megnezi ha a jelenlegi karakter kisbetu
                cmp     eax, 97
                jl      .hiba
                cmp     eax, 102
                jg      .hiba

                sub     eax, 87
                jmp     .hozzaad

            .hozzaad:;ha a karakter ervenyes akkor hozzaadja az eredmenyhez
                mov     [temp], ecx
                mov     ecx, 4
                .shift:
                    shl     edi, 1
                    jc      .hibas_shift
                    shl     ebx, 1
                    adc     edi, 0
                    loop    .shift
                
                mov     ecx, [temp]
                or      ebx, eax

            loop    .felepites
            jmp     .vege

        .hibas_shift:
            mov     ecx, [temp]
            xor     dl, dl
            inc     dl
            loop    .felepites

        .hiba: ;hiba eseten dl 1 lesz
            xor     dl, dl
            inc     dl
            loop    .felepites

    .vege: ;kilepes a fuggvenybol
        xor     ecx, ecx
        mov     cl, dh
        .verem_uritese:
            pop     eax
            loop    .verem_uritese

        mov     eax, 10
        call    mio_writechar
        cmp     dl, 1 ;ha dl=1 akkor hiba tortent
        jne      .vege_hiba_nelkul

        mov     eax, 0
        stc ;CF beallitasa, ezzel van a hiba jelezve a foprogramnak
        pop     esi
        pop     edi
        pop     ecx
        pop     ebx
        ret

        .vege_hiba_nelkul:
            clc ;CF uritese, ha veletlen beallitva maradt
            mov     eax, ebx
            mov     edx, edi
            pop     esi
            pop     edi
            pop     ecx
            pop     ebx
            ret

WriteHex64: ;64 bites szam kiirasa hexadecimalis formaban
    pusha
    
    .kiiras_elokeszulet:
        mov     esi, edx
        mov     ebx, 0x10
        mov     ecx, 8

    .elment_maradek: ;8-szor osztja a szamot 0x10-el, mert 8 karaktert kell majd kiirni, illetve elmenti a maradekot
        xor     edx, edx
        div     ebx
        push    edx
        loop     .elment_maradek

    mov     eax, esi
    mov     ecx, 8
     .elment_maradek2: ;8-szor osztja a szamot 0x10-el, mert 8 karaktert kell majd kiirni, illetve elmenti a maradekot
        xor     edx, edx
        div     ebx
        push    edx
        loop     .elment_maradek2

    mov     ecx, 16
    .kiir_szam: ;kiirja karakterenkent a szamot
        pop     eax
        cmp     eax, 10
        jl      .szamok
        jge     .hex

        .szamok:
            add     eax, 48
            call    mio_writechar
            loop    .kiir_szam

            mov     al, 10 ;ures sor kiirasa
            call    mio_writechar
            popa
            ret

        .hex:
            add     eax, 55
            call    mio_writechar
            loop    .kiir_szam

            mov     al, 10 ;ures sor kiirasa
            call    mio_writechar
            popa
            ret


section .bss
    beolvas_64 resb 256
    temp resd 1
    hiba resd 1
