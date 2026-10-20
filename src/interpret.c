/*
 * interpret.c - sprava interpretu
 * Vlastnik: Filip
 * Vzor menu a realloc viz docs/ARCHITEKTURA.md, kapitola Kucharka.
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "interpret.h"
#include "input.h"

Vysledek interpret_pridej(Festival *f, int id, const char *nazev,
                          const char *zanr, const char *zeme)
{
    /* TODO:
     * 1. text_je_platny(nazev/zanr/zeme), strlen < MAX_TEXT, jinak CHYBA_VSTUP
     * 2. interpret_najdi_nazev(f, nazev) != -1        -> CHYBA_DUPLICITA
     * 3. id > 0 && interpret_najdi_id(f, id) != -1    -> CHYBA_DUPLICITA
     * 4. pole plne -> realloc (vzor v Kucharce), selhani -> CHYBA_PAMET
     * 5. id == 0 -> id = f->dalsi_id_interpreta
     * 6. naplnit novy Interpret (strcpy), pridat na konec, pocet_interpretu++
     * 7. if (id >= f->dalsi_id_interpreta) f->dalsi_id_interpreta = id + 1;
     */
    return OK;
}

int interpret_najdi_id(Festival *f, int id)
{
    /* TODO: projit pole, vratit index i, kde interpreti[i].id == id; jinak -1 */
    return -1;
}

int interpret_najdi_nazev(Festival *f, const char *nazev)
{
    /* TODO: jako najdi_id, porovnani pres stejny_text() */
    return -1;
}

/* Pomocna: jeden radek tabulky */
static void vypis_interpreta(Interpret *i)
{
    printf("%4d  %-30s %-15s %s\n", i->id, i->nazev, i->zanr, i->zeme);
}

int interpret_vypis_vse(Festival *f)
{
    /* TODO: hlavicka tabulky + vypis_interpreta pro kazdeho; return pocet */
    return 0;
}

int interpret_vypis_zanr(Festival *f, const char *zanr)
{
    /* TODO: vypsat jen ty, kde stejny_text(zanr); return pocet vypsanych */
    return 0;
}

void menu_interpreti(Festival *f)
{
    /* TODO: smycka podmenu:
     * 1) Pridat interpreta     -> nacti_text x3, interpret_pridej(f, 0, ...)
     * 2) Vypsat vsechny        -> 0 vypsanych = "Zadni interpreti."
     * 3) Hledat podle nazvu    -> interpret_najdi_nazev, -1 = "Interpret nebyl nalezen."
     * 4) Hledat podle zanru    -> interpret_vypis_zanr, 0 = "Nic nenalezeno."
     * 0) Zpet
     * Po uspesnem pridani: f->zmeneno = 1
     * nacti_* vrati 0 -> return
     */
}
