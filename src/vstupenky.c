/*
 * vstupenky.c - kapacita a prodej vstupenek
 * Vlastnik: Bojdan
 */
#include <stdio.h>
#include "vstupenky.h"
#include "input.h"

Vysledek vstupenky_nastav_kapacitu(Festival *f, int kapacita)
{
    /* TODO:
     * kapacita < 0           -> CHYBA_VSTUP
     * kapacita < f->prodano  -> CHYBA_KAPACITA
     * jinak f->kapacita = kapacita, OK
     */
    return OK;
}

Vysledek vstupenky_prodej(Festival *f, int pocet)
{
    /* TODO:
     * pocet <= 0                      -> CHYBA_VSTUP
     * pocet > vstupenky_zbyva(f)      -> CHYBA_KAPACITA
     * jinak f->prodano += pocet, OK
     */
    return OK;
}

int vstupenky_zbyva(Festival *f)
{
    return f->kapacita - f->prodano;
}

void vstupenky_vypis_stav(Festival *f)
{
    /* TODO: vypsat Kapacita / Prodano / Zbyva */
}

void menu_vstupenky(Festival *f)
{
    /* TODO: smycka podmenu:
     * 1) Nastavit kapacitu   -> nacti_cislo(..., 0, 1000000, ...)
     * 2) Prodat vstupenky    -> nacti_cislo(..., -1000000, 1000000, ...)
     *                           (zaporne cislo pustit dal, odmitne ho vstupenky_prodej)
     * 3) Stav obsazenosti    -> vstupenky_vypis_stav
     * 0) Zpet
     * Po uspesne zmene: f->zmeneno = 1
     */
}
