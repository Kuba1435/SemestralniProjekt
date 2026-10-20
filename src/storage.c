/*
 * storage.c - ukladani a nacitani dat
 * Vlastnik: Bojdan
 * Format souboru viz docs/ARCHITEKTURA.md, kapitola 5.
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "storage.h"
#include "interpret.h"
#include "program.h"
#include "vstupenky.h"

Vysledek storage_uloz(Festival *f, const char *soubor)
{
    /* TODO:
     * 1. fopen(soubor, "w"), NULL -> CHYBA_SOUBOR
     * 2. v tomto poradi fprintf:
     *      FESTIVAL;nazev;pocet_dni
     *      VSTUPENKY;kapacita;prodano
     *      SCENA;nazev                           (kazda scena)
     *      INTERPRET;id;nazev;zanr;zeme          (kazdy interpret)
     *      VYSTOUPENI;id;id_interpreta;den;zacatek;konec;scena
     * 3. fclose, f->zmeneno = 0
     */
    return OK;
}

Vysledek storage_nacti(Festival *f, const char *soubor)
{
    /* TODO:
     * 1. fopen(soubor, "r"), NULL -> CHYBA_SOUBOR
     * 2. cist po radcich (fgets), odstranit '\n', rozdelit podle ';'
     * 3. podle prvniho slova:
     *      FESTIVAL   -> nazev, pocet_dni (1..MAX_DNI)
     *      VSTUPENKY  -> nastavit kapacitu a prodano (0 <= prodano <= kapacita)
     *      SCENA      -> scena_pridej
     *      INTERPRET  -> interpret_pridej(f, id, ...)
     *      VYSTOUPENI -> vystoupeni_pridej(f, id, ...)
     *    spatny pocet poli / necislo / funkce nevrati OK
     *      -> printf("Varovani: radek %d je poskozeny, preskakuji.\n"), pokracovat
     * 4. chybel platny radek FESTIVAL -> CHYBA_SOUBOR
     * 5. fclose, f->zmeneno = 0
     */
    return CHYBA_SOUBOR;
}
