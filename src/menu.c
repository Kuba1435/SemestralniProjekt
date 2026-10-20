/*
 * menu.c - hlavni nabidka a zalozeni festivalu
 * Vlastnik: Filip
 */
#include <stdio.h>
#include "menu.h"
#include "input.h"
#include "interpret.h"
#include "program.h"
#include "vstupenky.h"
#include "storage.h"

void menu_zalozeni_festivalu(Festival *f)
{
    /* TODO:
     * 1. nacti_text nazev festivalu -> f->nazev
     * 2. nacti_cislo pocet dni 1..MAX_DNI -> f->pocet_dni
     * 3. nacti_cislo pocet scen 1..MAX_SCEN, pak pro kazdou nacti_text
     *    + scena_pridej (pri CHYBA_DUPLICITA vypsat a zeptat se znovu)
     * 4. nacti_cislo kapacita -> vstupenky_nastav_kapacitu
     * 5. f->zmeneno = 1
     * nacti_* vrati 0 -> return
     */
}

void menu_hlavni(Festival *f)
{
    /* TODO: smycka:
     * printf("\n=== %s ===\n", f->nazev);
     * 1) Interpreti        -> menu_interpreti(f)
     * 2) Program           -> menu_program(f)
     * 3) Vstupenky         -> menu_vstupenky(f)
     * 4) Ulozit data       -> storage_uloz(f, SOUBOR_DATA), vypsat vysledek
     * 0) Konec             -> return (na ulozeni se zepta main)
     * nacti_cislo vrati 0 -> return
     */
}
