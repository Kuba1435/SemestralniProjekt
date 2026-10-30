/*
 * vstupenky.c - kapacita a prodej vstupenek
 * Vlastnik: Filip (HOTOVO)
 */
#include <stdio.h>
#include "vstupenky.h"
#include "input.h"

Vysledek vstupenky_nastav_kapacitu(Festival *f, int kapacita)
{
    if (kapacita < 0) {
        return CHYBA_VSTUP;
    }
    if (kapacita < f->prodano) {
        return CHYBA_KAPACITA;
    }
    
    f->kapacita = kapacita;
    return OK;
}

Vysledek vstupenky_prodej(Festival *f, int pocet)
{
    if (pocet <= 0) {
        return CHYBA_VSTUP;
    }
    if (pocet > vstupenky_zbyva(f)) {
        return CHYBA_KAPACITA;
    }
    
    f->prodano += pocet;
    return OK;
}

int vstupenky_zbyva(Festival *f)
{
    return f->kapacita - f->prodano;
}

void vstupenky_vypis_stav(Festival *f)
{
    printf("\n--- Stav obsazenosti ---\n");
    printf("Kapacita festivalu: %d\n", f->kapacita);
    printf("Prodano vstupenek:  %d\n", f->prodano);
    printf("Zbyva mist:         %d\n", vstupenky_zbyva(f));
    printf("------------------------\n");
}

void menu_vstupenky(Festival *f)
{
    int volba;
    int hodnota;
    Vysledek v;

    while (1) {
        printf("\n--- Sprava vstupenek ---\n");
        printf("1) Nastavit kapacitu\n");
        printf("2) Prodat vstupenky\n");
        printf("3) Stav obsazenosti\n");
        printf("0) Zpet\n");

        if (!nacti_cislo("Vyberte akci: ", 0, 3, &volba)) return;

        if (volba == 0) {
            return;
        } else if (volba == 1) {
            if (!nacti_cislo("Zadejte novou kapacitu: ", 0, 1000000, &hodnota)) return;
            v = vstupenky_nastav_kapacitu(f, hodnota);
            if (v == OK) {
                printf("Kapacita byla uspesne nastavena.\n");
                f->zmeneno = 1;
            } else {
                printf("Chyba: %s\n", vysledek_text(v));
            }
        } else if (volba == 2) {
            /* Pustime i zaporne cislo, aby se otestovala vnitrni kontrola ve vstupenky_prodej */
            if (!nacti_cislo("Zadejte pocet prodanych vstupenek: ", -1000000, 1000000, &hodnota)) return;
            v = vstupenky_prodej(f, hodnota);
            if (v == OK) {
                printf("Vstupenky byly uspesne prodany.\n");
                f->zmeneno = 1;
            } else {
                printf("Chyba: %s\n", vysledek_text(v));
            }
        } else if (volba == 3) {
            vstupenky_vypis_stav(f);
        }
    }
}