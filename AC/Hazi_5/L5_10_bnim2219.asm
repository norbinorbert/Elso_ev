;Boda Norbert, bnim2219, 511
;L5_10
;Készítsünk el egy-egy olyan eljárást, amely 32 bites, egyszeres pontosságú lebegőpontos értéket olvas be és ír ki, hagyományos és exponenciális formában egyaránt.
;A számokat legalább 4 (hagyományos formában) illetve 6 (exponenciális formában) tizedes pontossággal írjuk ki.
;A főprogramban mindenki a sorszámának megfelelő kifejezést kell kódolja az 1. laborfeladathoz hasonlóan. 
;Minden kifejezésnek 4 paramétere van, a, b, c és d. Az a-t és c-t hagyományos, a b-t és d-t exponenciális formában olvassuk be 
;(ezt kell közölni a beolvasásokat megelőző üzenetben is). A végeredményt írjuk ki hagyományos és exponenciális formában is.
;10. E(a,b,c,d) = max(min(a * 1.1, 1), 0) - b + sqrt(c / d)

%include 'mio.inc'

global main

section .text
main:
    mov     eax, A_beolvas
    call    mio_writestr
    call    ReadFloat ;A szam beolvasasa
    movss   [A], xmm0

    mov     eax, B_beolvas ;B szam beolvasasa
    call    mio_writestr
    call    ReadFloat
    movss   [B], xmm0
 
    mov     eax, C_beolvas ;C szam beolvasasa
    call    mio_writestr
    call    ReadFloat
    movss   [C], xmm0

    mov     eax, D_beolvas ;D szam beolvasasa
    call    mio_writestr
    call    ReadFloat
    movss   [D], xmm0

    call    mio_writeln
    mov     eax, keplet ;keplet kiirasa
    call    mio_writestr
    call    mio_writeln

    movss   xmm0, [A]
    movss   xmm1, [ee]
    movss   xmm2, [egy]
    xorps   xmm3, xmm3
    
    ;max(min(a * 1.1, 1), 0) kiszamolasa
    mulss   xmm0, xmm1
    minss   xmm0, xmm2
    maxss   xmm0, xmm3

    ;xmm0 - b kiszamolasa
    movss   xmm1, [B]
    subss   xmm0, xmm1

    ;xmm0 + sqrt(c / d) kiszamolasa
    xorps   xmm5, xmm5
    xorps   xmm6, xmm6
    movss   xmm5, [C]
    movss   xmm6, [D]
    divss   xmm5, xmm6
    sqrtss  xmm5, xmm5
    addss   xmm0, xmm5

    call    mio_writeln
    mov     eax, eredmeny_hagyomanyos ;eredmeny kiirasa hagyomanyos alakban
    call    mio_writestr
    call    WriteFLoatTraditional

    mov     eax, eredmeny_exponencialis ;eredmeny kiirasa exponencialis alakban
    call    mio_writestr
    call    WriteFLoatExponential

    ret

ReadFloat: ;valos szam beolvasasa es xmm0-ban valo tarolasa
    pusha
    movd    eax, xmm1
    push    eax
    movd    eax, xmm2
    push    eax
    movd    eax, xmm3
    push    eax
    movd    eax, xmm4
    push    eax
    movd    eax, xmm5
    push    eax
    movd    eax, xmm6
    push    eax
    movd    eax, xmm7
    push    eax
    
    mov     [elojel], byte 0
    mov     [tizedes_vesszo], byte 0

    xorps   xmm0, xmm0
    xorps   xmm1, xmm1
    xorps   xmm2, xmm2
    xorps   xmm3, xmm3
    xorps   xmm4, xmm4
    xorps   xmm5, xmm5
    xorps   xmm6, xmm6
    xorps   xmm7, xmm7
    movss   xmm1, [tiz]
    movss   xmm2, [ne]

    .olvas:
        xor     eax, eax
        call    mio_readchar
        cmp     al, 13 ;enter a beolvasas veget jelenti
        je      .majdnem_vege
        cmp     eax, 43 ;+ karaktert figyelmen kivul hagyja
        je      .olvas
        cmp     al, 45 ;negativ szam kezelese
        je      .minusz
        cmp     al, 46 ;tizedes pont ellenorzese
        je      .tizedes_vesszo
        cmp     al, 69 ;exponencialis alak kezelese
        je      .exponencialis_olvas
        cmp     al, 101 ;exponencialis alak kezelese
        je      .exponencialis_olvas

        cmp     [tizedes_vesszo], byte 1
        je      .tizedes_resz

        ;egesz resz felepitese
        mulss       xmm0, xmm1
        call        mio_writechar
        sub         eax, 48
        cvtsi2ss    xmm3, eax
        addss       xmm0, xmm3
        jmp         .olvas

        .tizedes_resz: ;tizedes vesszo utani resz felepitese
            call        mio_writechar
            sub         eax, 48
            cvtsi2ss    xmm3, eax
            mulss       xmm3, xmm2
            divss       xmm2, xmm1
            addss       xmm0, xmm3
            jmp         .olvas

        .minusz: ;ha negativ a szam akkor azt megjegyzi egy valtozo segitsegevel
            call    mio_writechar
            mov     [elojel], byte 1
            jmp     .olvas

        .tizedes_vesszo: ;ha beolvassuk a tizedes pontot akkor ezt megjegyzi
            call    mio_writechar
            mov     [tizedes_vesszo], byte 1
            jmp     .olvas

        .exponencialis_olvas: ;ha beolvas egy "e" vagy "E" karaktert akkor exponencialis alaku szamot epit fel
            call    mio_writechar
            call    ReadInt
            mov     ecx, eax
            cmp     eax, 0
            jl      .osztasok
            jg      .szorzasok
            je      .majdnem_vege

            .szorzasok: ;pozitiv exponens eseten szorzasokat kell vegezni
                mulss   xmm0, xmm1
                loop    .szorzasok
                jmp     .majdnem_vege

            .osztasok: ;negativ exponens eseten osztasokat kell vegezni
                neg     eax
                mov     ecx, eax
                .osztasok_loop:
                    divss   xmm0, xmm1
                    loop    .osztasok_loop
                jmp     .majdnem_vege

    .majdnem_vege:
        cmp     [elojel], byte 1 ;ha az elojel be van allitva, akkor negalja a szamot, hogy negativ legyen
        jne     .vege
        movss   xmm1, [me]
        mulss   xmm0, xmm1

        .vege:
            call    mio_writeln
            pop     eax
            movd    xmm7, eax
            pop     eax
            movd    xmm6, eax
            pop     eax
            movd    xmm5, eax
            pop     eax
            movd    xmm4, eax
            pop     eax
            movd    xmm3, eax
            pop     eax
            movd    xmm2, eax
            pop     eax
            movd    xmm1, eax
            popa
            ret

WriteFLoatTraditional: ;kiirja az xmm0-ban tarolt valos szamot hagyomanyos alakban
    pusha
    movd    eax, xmm0
    push    eax
    movd    eax, xmm1
    push    eax
    movd    eax, xmm2
    push    eax
    movd    eax, xmm3
    push    eax
    movd    eax, xmm4
    push    eax
    movd    eax, xmm5
    push    eax
    movd    eax, xmm6
    push    eax
    movd    eax, xmm7
    push    eax

    xorps   xmm2, xmm2
    movss   xmm2, [tiz]
    xorps   xmm3, xmm3
    movss   xmm3, [me]

    ;egesz resz kiirasa
    cvttss2si   eax, xmm0
    cmp         eax, 0
    jne         .kiir_decimal
    xorps       xmm7, xmm7
    comiss      xmm0, xmm7
    ja          .kiir_decimal
    mov         ebx, eax
    mov         eax, 45
    call        mio_writechar
    mov         eax, ebx

    .kiir_decimal:
        call        WriteInt

    ;tizedes pont kiirasa
    mov     eax, 46
    call    mio_writechar

    ;tizedes resz kiirasa
    roundss     xmm1, xmm0, 3
    subss       xmm0, xmm1
    mov         ecx, 4
    .szorzas:
        mulss   xmm0, xmm2
        loop    .szorzas

    xorps       xmm7, xmm7
    comiss      xmm0, xmm7
    ja          .tizedes_kiir
    mulss       xmm0, xmm3

    .tizedes_kiir: ;attol fuggoen, hogy milyen nagysagrendu lesz az eax miutan a tizedeseket atvisszuk a vesszon, kiir nullakat, hogy 4 tizedes pontossag legyen meg
        cvttss2si   eax, xmm0
        cmp     eax, 10
        jge     .ketto_nullas
        mov     ecx, 3
        .kiir_harom_nullas:
            mov     eax, 48
            call    mio_writechar
            loop    .kiir_harom_nullas
            jmp     .tizedes_szamok

        .ketto_nullas:
            cmp     eax, 100
            jge     .egy_nullas
            mov     ecx, 2
            .kiir_ketto_nullas:
                mov     eax, 48
                call    mio_writechar
                loop    .kiir_ketto_nullas
                jmp     .tizedes_szamok
        
        .egy_nullas:
            cmp     eax, 1000
            jge     .tizedes_szamok
            mov     eax, 48
            call    mio_writechar
        
        .tizedes_szamok:
            cvttss2si   eax, xmm0
            call        WriteInt

    .vege:
        call    mio_writeln
        pop     eax
        movd    xmm7, eax
        pop     eax
        movd    xmm6, eax
        pop     eax
        movd    xmm5, eax
        pop     eax
        movd    xmm4, eax
        pop     eax
        movd    xmm3, eax
        pop     eax
        movd    xmm2, eax
        pop     eax
        movd    xmm1, eax
        pop     eax
        movd    xmm0, eax
        popa
        ret

WriteFLoatExponential: ;kiirja az xmm0-ban tarolt valos szamot exponencialis alakban
    pusha
    movd    eax, xmm0
    push    eax
    movd    eax, xmm1
    push    eax
    movd    eax, xmm2
    push    eax
    movd    eax, xmm3
    push    eax
    movd    eax, xmm4
    push    eax
    movd    eax, xmm5
    push    eax
    movd    eax, xmm6
    push    eax
    movd    eax, xmm7
    push    eax

    xorps   xmm2, xmm2
    movss   xmm2, [tiz]
    xorps   xmm3, xmm3
    movss   xmm3, [me]
    xorps   xmm6, xmm6
    movss   xmm6, [mtiz]
    xorps   xmm7, xmm7
    movss   xmm7, [egy]

    xorps   xmm5, xmm5
    comiss  xmm0, xmm5 ;mivel exponencialis alakban az egesz resz (0 es 10) vagy (-10 es 0) kozott kell legyen, ezert mashogy kell eljarni negativ es pozitiv szam eseten
    ja      .pozitiv_hasonlitas
    jb      .negativ_hasonlitas

    .negativ_hasonlitas:
        xor     ebx, ebx
        comiss  xmm0, xmm6
        jb      .osztasok_negativ
        comiss  xmm0, xmm3
        ja      .szorzasok_negativ
        jmp     .kiiras

    .pozitiv_hasonlitas:
        xor     ebx, ebx
        comiss  xmm0, xmm2
        ja      .osztasok_pozitiv
        comiss  xmm0, xmm7
        jb      .szorzasok_pozitiv
        jmp     .kiiras

    .osztasok_pozitiv:
        inc     ebx
        divss   xmm0, xmm2
        comiss  xmm0, xmm2
        ja      .osztasok_pozitiv
        jmp     .kiiras

    .szorzasok_pozitiv:
        dec     ebx
        mulss   xmm0, xmm2
        comiss  xmm0, xmm7
        jb      .szorzasok_pozitiv
        jmp     .kiiras

    .osztasok_negativ:
        inc     ebx
        divss   xmm0, xmm2
        comiss  xmm0, xmm6
        jb      .osztasok_negativ
        jmp     .kiiras

    .szorzasok_negativ:
        dec     ebx
        mulss   xmm0, xmm2
        comiss  xmm0, xmm3
        ja      .szorzasok_negativ
        jmp     .kiiras

    .kiiras:
        ;egesz resz kiirasa
        cvttss2si   eax, xmm0
        call        WriteInt

        ;tizedes pont kiirasa
        mov     eax, 46
        call    mio_writechar

        ;tizedes resz kiirasa
        roundss     xmm1, xmm0, 3
        subss       xmm0, xmm1
        mov         ecx, 6
        .szorzas:
            mulss   xmm0, xmm2
            loop    .szorzas

        xorps       xmm7, xmm7
        comiss      xmm0, xmm7
        ja          .tizedes_kiir
        mulss       xmm0, xmm3

        .tizedes_kiir: ;attol fuggoen, hogy milyen nagysagrendu lesz az eax miutan a tizedeseket atvisszuk a vesszon, kiir nullakat, hogy 6 tizedes pontossag legyen meg
            cvttss2si   eax, xmm0
            cmp     eax, 10
            jge     .negy_nullas
            mov     ecx, 5
            .kiir_ot_nullas:
                    mov     eax, 48
                    call    mio_writechar
                    loop    .kiir_harom_nullas
                    jmp     .tizedes_szamok

            .negy_nullas:
                cmp     eax, 100
                jge     .harom_nullas
                mov     ecx, 4
                .kiir_negy_nullas:
                    mov     eax, 48
                    call    mio_writechar
                    loop    .kiir_harom_nullas
                    jmp     .tizedes_szamok

            .harom_nullas:
                cmp     eax, 1000
                jge     .ketto_nullas
                mov     ecx, 3
                .kiir_harom_nullas:
                    mov     eax, 48
                    call    mio_writechar
                    loop    .kiir_harom_nullas
                    jmp     .tizedes_szamok

            .ketto_nullas:
                cmp     eax, 10000
                jge     .egy_nullas
                mov     ecx, 2
                .kiir_ketto_nullas:
                    mov     eax, 48
                    call    mio_writechar
                    loop    .kiir_ketto_nullas
                    jmp     .tizedes_szamok
            
            .egy_nullas:
                cmp     eax, 100000
                jge     .tizedes_szamok
                mov     eax, 48
                call    mio_writechar
            
            .tizedes_szamok:
                cvttss2si   eax, xmm0
                call        WriteInt

        ;exponens kiirasa
        mov     eax, 101
        call    mio_writechar
        mov     eax, ebx
        call    WriteInt

    .vege:
        call    mio_writeln
        pop     eax
        movd    xmm7, eax
        pop     eax
        movd    xmm6, eax
        pop     eax
        movd    xmm5, eax
        pop     eax
        movd    xmm4, eax
        pop     eax
        movd    xmm3, eax
        pop     eax
        movd    xmm2, eax
        pop     eax
        movd    xmm1, eax
        pop     eax
        movd    xmm0, eax
        popa
        ret

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
        cmp     eax, 43 ;+ karaktert figyelmen kivul hagyja
        je      .olvas

        push    eax ;a beolvasott karaktereket a verembe teszi
        inc     cl
        call    mio_writechar
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

            cmp     edi, 1 ;ha az edi=1, akkor a felepites soran kivonasokat vegez, mert a szam negativ kell legyen
            je      .negativ

            .pozitiv: ;ha a karakter szam akkor hozzaadja az eredmenyhez
            imul    ebx, 10
            sub     eax, 48
            add     ebx, eax

            loop    .felepites
            jmp     .vege

            .negativ: ;ha a karakter szam akkor kivonja az eredmenybol
            imul    ebx, 10
            sub     eax, 48
            sub     ebx, eax
            
            loop    .felepites
            jmp     .vege


    .vege: ;kilepes a fuggvenybol
        xor     ecx, ecx
        mov     cl, dh
        .verem_uritese:
            pop     eax
            loop    .verem_uritese

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

    popa
    ret

section .data
    mtiz dd -10.0
    me dd -1.0
    ne dd 0.1
    egy dd 1.0
    ee dd 1.1
    tiz dd 10.0
    A_beolvas dd "Kerem az A szamot hagyomanyos alakban: ", 0
    B_beolvas dd "Kerem a B szamot exponencialis alakban: ", 0
    C_beolvas dd "Kerem a C szamot hagyomanyos alakban: ", 0
    D_beolvas dd "Kerem a D szamot exponencialis alakban: ", 0
    keplet dd "Kifejezes keplete: E(a,b,c,d) = max(min(a * 1.1, 1), 0) - b + sqrt(c / d)"
    eredmeny_hagyomanyos dd "A kifejezes eredmenye hagyomanyos alakban: E(a, b, c, d) = ", 0
    eredmeny_exponencialis dd "A kifejezes eredmenye exponencialis alakban: E(a, b, c, d) = ", 0

section .bss
    A resd 1
    B resd 1
    C resd 1
    D resd 1
    elojel resd 1
    tizedes_vesszo resd 1
    eredmeny resd 1