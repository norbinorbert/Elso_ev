;Boda Norbert, bnim2219, 511
;L4b, 4.feladat
;megfelelő üzenet kiíratása után beolvasunk egy stringet;
;kiírjuk a hosszát;
;kiírjuk a tömörített formáját;
;kiírjuk a tömörített formáját kisbetűkre alakítva;
;megfelelő üzenet kiíratása után beolvasunk egy második stringet;
;kiírjuk a hosszát;
;kiírjuk a tömörített formáját;
;kiírjuk a tömörített formáját nagybetűkre alakítva;
;létrehozunk a memóriában egy új stringet: az első string nagybetűs verziójához hozzáfűzzük a második string kisbetűs verzióját;
;kiírjuk a létrehozott stringet;
;kiírjuk a létrehozott string hosszát;
;befejezzük a programot.

%include 'strings.inc'
%include 'iostr.inc'
%include 'ionum.inc'

global main

section .text
main:
    mov     esi, str_olvas1
    call    WriteStr ;kiir egy megfelelo uzenetet mielott beolvas egy stringet
    mov     esi, beolvasott_string1 ;a megfelelo cimet adja meg, hogy hova keruljon a string
    mov     ecx, 256 ;max hossz megadasa
    call    ReadLnStr ;string beolvasasa a megfelelo cimre, aminek maximalisan ecx hossza lehet

    call    StrLen ;string hosszanak lekerese
    call    WriteInt ;string hosszanak kiirasa
    
    mov     edi, tomoritett1 ;cim megadasa, ahova tomoriteni szeretnenk a stringet
    call    StrCompact ;esi cimen levo string tomoritese edi cimre
    mov     esi, edi
    mov     ecx, eax
    call    WriteLnStr ;tomoritett string kiirasa

    call    StrLower ;tomoritett string kisbetusse alakitasa
    call    WriteLnStr ;kisbetus tomoritett string kiirasa

    mov     esi, str_olvas2
    call    WriteStr ;masodik beolvasas elotti uzenet
    mov     esi, beolvasott_string2 ;masodik beolvasas elotti levo elokeszuletek
    mov     ecx, 256
    call    ReadLnStr ;masodik string beolvasasa

    call    StrLen ;string hosszanak lekerese
    call    WriteInt ;string hosszanak kiirasa
    
    mov     edi, tomoritett2 ;cim megadasa, ahova tomoriteni szeretnenk a stringet
    call    StrCompact ;esi cimen levo string tomoritese edi cimre
    mov     esi, edi
    call    StrLen ;tomoritett string hosszanak lekerese
    mov     ecx, eax
    call    WriteLnStr ;tomoritett string kiirasa

    call    StrUpper ;tomoritett string nagybetusse alakitasa
    call    WriteLnStr ;nagybetus tomoritett string kiirasa

    mov     edi, osszefuzott_string ;ket stringet erre a cimre akarjuk osszefuzni
    mov     esi, beolvasott_string1
    call    StrUpper ;eloszor nagybetusse alakitjuk az elso stringet
    call    StrCat ;hozzaadjuk az elso stringet az eredmenyhez
    mov     esi, beolvasott_string2
    call    StrLower ;masodik string kisbetusse alakitasa
    call    StrCat ;masodik string hozzaadasa az eredmenyhez

    mov     esi, edi
    call    WriteLnStr ;az osszefuzott string kiirasa

    call    StrLen ;az osszefuzott string hosszanak lekerese
    mov     ecx, eax
    call    WriteInt ;az osszefuzott string hosszanak kiirasa
    ret

section .data
    str_olvas1 db 'Kerem az elso stringet: ', 0
    str_olvas2 db 'Kerem a masodik stringet: ', 0

section .bss
    beolvasott_string1 resb 256
    tomoritett1 resb 256
    beolvasott_string2 resb 256
    tomoritett2 resb 256
    osszefuzott_string resb 256