/*
 * vstupenky.h
 * Kapacita festivalu a prodej vstupenek.
 */
#ifndef VSTUPENKY_H
#define VSTUPENKY_H

#include "festival.h"

/* Kapacita musi byt >= 0 a nesmi byt mensi nez uz prodane vstupenky */
Vysledek vstupenky_nastav_kapacitu(Festival *f, int kapacita);

/* Pocet musi byt > 0 a nesmi prekrocit zbyvajici mista */
Vysledek vstupenky_prodej(Festival *f, int pocet);

int  vstupenky_zbyva(Festival *f);
void vstupenky_vypis_stav(Festival *f);     /* kapacita, prodano, zbyva */

/* Podmenu "Vstupenky" */
void menu_vstupenky(Festival *f);

#endif
