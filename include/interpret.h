/*
 * interpret.h
 * Sprava interpretu.
 */
#ifndef INTERPRET_H
#define INTERPRET_H

#include "festival.h"

/* Prida interpreta. id = 0 -> nove cislo se prideli automaticky
 * (pouziva menu), id > 0 -> pouzije se zadane (pouziva nacitani ze souboru).
 * Kontroluje prazdne texty a duplicitni nazev. */
Vysledek interpret_pridej(Festival *f, int id, const char *nazev,
                          const char *zanr, const char *zeme);

/* Hledani - vraci index v poli f->interpreti, nebo -1 kdyz neexistuje */
int interpret_najdi_id(Festival *f, int id);
int interpret_najdi_nazev(Festival *f, const char *nazev);

/* Vypisy - vraci pocet vypsanych interpretu (0 = nic nenalezeno) */
int interpret_vypis_vse(Festival *f);
int interpret_vypis_zanr(Festival *f, const char *zanr);

/* Podmenu "Sprava interpretu" */
void menu_interpreti(Festival *f);

#endif
