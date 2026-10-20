/*
 * festival.c - zakladni funkce nad strukturou Festival (HOTOVO)
 * Vlastnik: Jakub
 */
#include <stdlib.h>
#include <string.h>
#include "festival.h"

void festival_init(Festival *f)
{
    memset(f, 0, sizeof(Festival));     /* vsechno na 0 / NULL */
    f->dalsi_id_interpreta = 1;
    f->dalsi_id_vystoupeni = 1;
}

void festival_uvolni(Festival *f)
{
    free(f->interpreti);
    free(f->vystoupeni);
    festival_init(f);
}

const char *vysledek_text(Vysledek v)
{
    switch (v) {
        case OK:                    return "V poradku.";
        case CHYBA_VSTUP:           return "Neplatny udaj.";
        case CHYBA_DUPLICITA:       return "Zaznam se stejnym nazvem uz existuje.";
        case CHYBA_NENALEZENO:      return "Zaznam nebyl nalezen.";
        case CHYBA_CAS:             return "Chybny den nebo cas (konec musi byt po zacatku).";
        case CHYBA_KOLIZE:          return "Scena je v tuto dobu obsazena.";
        case CHYBA_INTERPRET_HRAJE: return "Interpret v tuto dobu uz vystupuje.";
        case CHYBA_KAPACITA:        return "Prekrocena kapacita festivalu.";
        case CHYBA_PAMET:           return "Nedostatek pameti.";
        case CHYBA_SOUBOR:          return "Chyba pri praci se souborem.";
    }
    return "Neznama chyba.";
}
