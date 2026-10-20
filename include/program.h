/*
 * program.h
 * Sceny a vystoupeni (program festivalu).
 */
#ifndef PROGRAM_H
#define PROGRAM_H

#include "festival.h"

/* Prida scenu na konec pole f->sceny (kontroluje duplicitu a MAX_SCEN) */
Vysledek scena_pridej(Festival *f, const char *nazev);

/* Prida vystoupeni. id = 0 -> nove cislo automaticky, id > 0 -> ze souboru.
 * Kontroluje: interpret existuje, den 1..pocet_dni, scena existuje,
 * zacatek < konec <= 1440, scena neni v tu dobu obsazena (CHYBA_KOLIZE),
 * interpret v tu dobu nehraje na jine scene (CHYBA_INTERPRET_HRAJE). */
Vysledek vystoupeni_pridej(Festival *f, int id, int id_interpreta, int den,
                           int zacatek, int konec, int scena);

/* Seradi vystoupeni podle dne a casu zacatku (qsort) */
void program_serad(Festival *f);

/* Vypisy - vraci pocet vypsanych vystoupeni */
int program_vypis(Festival *f);                             /* serazeny cely program */
int program_vypis_interpreta(Festival *f, int id_interpreta);

/* Podmenu "Program festivalu" */
void menu_program(Festival *f);

#endif
