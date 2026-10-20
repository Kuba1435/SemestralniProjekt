/*
 * program.c - sceny a vystoupeni
 * Vlastnik: Filip
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "program.h"
#include "interpret.h"
#include "input.h"

Vysledek scena_pridej(Festival *f, const char *nazev)
{
    /* TODO:
     * 1. !text_je_platny / prilis dlouhy           -> CHYBA_VSTUP
     * 2. f->pocet_scen == MAX_SCEN                  -> CHYBA_VSTUP
     * 3. stejny_text s existujici scenou           -> CHYBA_DUPLICITA
     * 4. strcpy do f->sceny[f->pocet_scen++]
     */
    return OK;
}

/* Pomocna: prekryvaji se dva casove useky? (navazujici = neprekryvaji) */
static int prekryv(int zac1, int kon1, int zac2, int kon2)
{
    return zac1 < kon2 && zac2 < kon1;
}

Vysledek vystoupeni_pridej(Festival *f, int id, int id_interpreta, int den,
                           int zacatek, int konec, int scena)
{
    /* TODO:
     * 1. interpret_najdi_id(f, id_interpreta) == -1  -> CHYBA_NENALEZENO
     * 2. scena mimo 0..pocet_scen-1                  -> CHYBA_VSTUP
     * 3. den mimo 1..pocet_dni                       -> CHYBA_CAS
     * 4. zacatek < 0, konec > 1440, zacatek >= konec -> CHYBA_CAS
     * 5. pro kazde existujici vystoupeni ve stejny den s prekryv(...):
     *       stejna scena                -> CHYBA_KOLIZE
     *       stejny interpret            -> CHYBA_INTERPRET_HRAJE
     * 6. id > 0 a uz existuje            -> CHYBA_DUPLICITA
     * 7. realloc kdyz plne (jako u interpretu), pridat na konec
     * 8. id == 0 -> dalsi_id_vystoupeni; jinak posunout dalsi_id
     */
    (void)prekryv;  /* TODO: smazat, az se prekryv pouzije */
    return OK;
}

/* Pomocna pro qsort: nejdriv den, pak zacatek */
static int porovnej_vystoupeni(const void *a, const void *b)
{
    const Vystoupeni *x = a;
    const Vystoupeni *y = b;
    if (x->den != y->den) return x->den - y->den;
    return x->zacatek - y->zacatek;
}

void program_serad(Festival *f)
{
    qsort(f->vystoupeni, f->pocet_vystoupeni, sizeof(Vystoupeni), porovnej_vystoupeni);
}

/* Pomocna: vypise jeden radek "Den 1  20:00-21:30  Hlavni   Kabat" */
static void vypis_vystoupeni(Festival *f, Vystoupeni *v)
{
    /* TODO: najit interpreta pres interpret_najdi_id, cas pres vypis_cas() */
}

int program_vypis(Festival *f)
{
    /* TODO: program_serad, pak vypis_vystoupeni pro vsechna; return pocet */
    (void)vypis_vystoupeni;  /* TODO: smazat */
    return 0;
}

int program_vypis_interpreta(Festival *f, int id_interpreta)
{
    /* TODO: program_serad, vypsat jen ta s danym id_interpreta; return pocet */
    return 0;
}

void menu_program(Festival *f)
{
    /* TODO: smycka podmenu:
     * 1) Pridat vystoupeni
     *      - nacti_text nazev interpreta -> interpret_najdi_nazev (-1 = nenalezen)
     *      - nacti_cislo den 1..pocet_dni
     *      - nacti_cas zacatek, nacti_cas konec
     *      - vypsat sceny s cisly 1..pocet_scen, nacti_cislo -> scena = volba - 1
     *      - vystoupeni_pridej(f, 0, ...), vysledek vypsat
     * 2) Vypsat program               -> 0 = "Program je prazdny."
     * 3) Vystoupeni interpreta        -> podle nazvu, pak program_vypis_interpreta
     * 0) Zpet
     * Po uspesnem pridani: f->zmeneno = 1
     */
}
