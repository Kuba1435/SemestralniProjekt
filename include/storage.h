/*
 * storage.h
 * Ukladani a nacitani dat do textoveho souboru (format viz docs/ARCHITEKTURA.md).
 */
#ifndef STORAGE_H
#define STORAGE_H

#include "festival.h"

#define SOUBOR_DATA "festival.txt"

/* Ulozi vsechna data, pri uspechu nastavi f->zmeneno = 0 */
Vysledek storage_uloz(Festival *f, const char *soubor);

/* Nacte data. Soubor neexistuje -> CHYBA_SOUBOR.
 * Poskozeny radek se preskoci, vypise se varovani a nacita se dal.
 * Zaznamy se vkladaji pres interpret_pridej / vystoupeni_pridej,
 * takze se kontroluji stejne jako vstup od uzivatele. */
Vysledek storage_nacti(Festival *f, const char *soubor);

#endif
