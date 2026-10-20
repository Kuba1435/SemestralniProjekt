/*
 * menu.h
 * Hlavni nabidka programu.
 */
#ifndef MENU_H
#define MENU_H

#include "festival.h"

/* Pri prvnim spusteni (neni ulozeny soubor): nazev, pocet dni, sceny, kapacita */
void menu_zalozeni_festivalu(Festival *f);

/* Hlavni nabidka - opakuje se, dokud uzivatel nezvoli Konec */
void menu_hlavni(Festival *f);

#endif
