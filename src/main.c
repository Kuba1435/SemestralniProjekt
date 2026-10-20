/*
 * main.c - spusteni a ukonceni programu (HOTOVO)
 * Vlastnik: Jakub
 */
#include <stdio.h>
#include "festival.h"
#include "input.h"
#include "menu.h"
#include "storage.h"

int main(void)
{
    Festival f;
    int ulozit;
    Vysledek v;

    festival_init(&f);

    if (storage_nacti(&f, SOUBOR_DATA) != OK) {
        printf("Ulozena data nenalezena. Zakladame novy festival.\n");
        festival_uvolni(&f);            /* zahodit pripadna napul nactena data */
        menu_zalozeni_festivalu(&f);
    }

    menu_hlavni(&f);

    if (f.zmeneno) {
        if (nacti_ano_ne("Mate neulozene zmeny. Ulozit? (a/n): ", &ulozit) && ulozit) {
            v = storage_uloz(&f, SOUBOR_DATA);
            if (v == OK) printf("Data ulozena.\n");
            else         printf("Chyba: %s\n", vysledek_text(v));
        }
    }

    festival_uvolni(&f);
    printf("Konec programu.\n");
    return 0;
}
