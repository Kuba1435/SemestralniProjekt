/*
 * program.c - sceny a vystoupeni
 * Vlastnik: Filip (HOTOVO)
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "program.h"
#include "interpret.h"
#include "input.h"

Vysledek scena_pridej(Festival *f, const char *nazev)
{
    if (!text_je_platny(nazev) || strlen(nazev) >= MAX_TEXT) {
        return CHYBA_VSTUP;
    }
    if (f->pocet_scen >= MAX_SCEN) {
        return CHYBA_VSTUP;
    }
    for (int i = 0; i < f->pocet_scen; i++) {
        if (stejny_text(f->sceny[i], nazev)) {
            return CHYBA_DUPLICITA;
        }
    }
    
    strcpy(f->sceny[f->pocet_scen], nazev);
    f->pocet_scen++;
    return OK;
}

/* Pomocna: prekryvaji se dva casove useky? (navazujici = neprekryvaji) */
static int prekryv(int zac1, int kon1, int zac2, int kon2)
{
    return zac1 < kon2 && zac2 < kon1;
}

Vysledek vystoupeni_pridej(Festival *f, int id, int id_interpreta, int den,
                           int zacatek, int konec, int scena)
{
    if (interpret_najdi_id(f, id_interpreta) == -1) return CHYBA_NENALEZENO;
    if (scena < 0 || scena >= f->pocet_scen) return CHYBA_VSTUP;
    
    /* Pokud mate ve strukture pocet_dni, overi se, jinak hlida aspon kladny den */
    if (den < 1 || (f->pocet_dni > 0 && den > f->pocet_dni)) return CHYBA_CAS;
    if (zacatek < 0 || konec > 1440 || zacatek >= konec) return CHYBA_CAS;

    for (int i = 0; i < f->pocet_vystoupeni; i++) {
        Vystoupeni *v = &f->vystoupeni[i];
        if (v->den == den && prekryv(zacatek, konec, v->zacatek, v->konec)) {
            if (v->scena == scena) return CHYBA_KOLIZE;
            if (v->id_interpreta == id_interpreta) return CHYBA_INTERPRET_HRAJE;
        }
    }

    if (id > 0) {
        for (int i = 0; i < f->pocet_vystoupeni; i++) {
            if (f->vystoupeni[i].id == id) return CHYBA_DUPLICITA;
        }
    }

    if (f->pocet_vystoupeni >= f->alokovano_vystoupeni) {
        int nova_kapacita = (f->alokovano_vystoupeni == 0) ? 10 : f->alokovano_vystoupeni * 2;
        Vystoupeni *nove_pole = (Vystoupeni *)realloc(f->vystoupeni, nova_kapacita * sizeof(Vystoupeni));
        if (nove_pole == NULL) return CHYBA_PAMET;
        
        f->vystoupeni = nove_pole;
        f->alokovano_vystoupeni = nova_kapacita;
    }

    if (id == 0) id = f->dalsi_id_vystoupeni;

    Vystoupeni *novy = &f->vystoupeni[f->pocet_vystoupeni];
    novy->id = id;
    novy->id_interpreta = id_interpreta;
    novy->den = den;
    novy->zacatek = zacatek;
    novy->konec = konec;
    novy->scena = scena;

    f->pocet_vystoupeni++;

    if (id >= f->dalsi_id_vystoupeni) {
        f->dalsi_id_vystoupeni = id + 1;
    }

    return OK;
}

/* Pomocna pro qsort: nejdriv den, pak zacatek */
static int porovnej_vystoupeni(const void *a, const void *b)
{
    const Vystoupeni *x = (const Vystoupeni *)a;
    const Vystoupeni *y = (const Vystoupeni *)b;
    if (x->den != y->den) return x->den - y->den;
    return x->zacatek - y->zacatek;
}

void program_serad(Festival *f)
{
    qsort(f->vystoupeni, f->pocet_vystoupeni, sizeof(Vystoupeni), porovnej_vystoupeni);
}

/* Pomocna: vypise jeden radek "Den 1  20:00-21:30  Hlavni   Kabat" */
static void vypis_vystoupeni(Festival *f, Vystoupeni *v)
{
    int idx_int = interpret_najdi_id(f, v->id_interpreta);
    const char *nazev_interpreta = (idx_int != -1) ? f->interpreti[idx_int].nazev : "Neznamy";
    
    printf("Den %d  ", v->den);
    vypis_cas(v->zacatek);
    printf("-");
    vypis_cas(v->konec);
    printf("  %-15s %s\n", f->sceny[v->scena], nazev_interpreta);
}

int program_vypis(Festival *f)
{
    if (f->pocet_vystoupeni == 0) return 0;
    
    program_serad(f);
    
    printf("\n%5s  %11s  %-15s %s\n", "Den", "Cas", "Scena", "Interpret");
    printf("----------------------------------------------------------\n");
    for (int i = 0; i < f->pocet_vystoupeni; i++) {
        vypis_vystoupeni(f, &f->vystoupeni[i]);
    }
    return f->pocet_vystoupeni;
}

int program_vypis_interpreta(Festival *f, int id_interpreta)
{
    int pocet = 0;
    program_serad(f);
    
    for (int i = 0; i < f->pocet_vystoupeni; i++) {
        if (f->vystoupeni[i].id_interpreta == id_interpreta) {
            if (pocet == 0) {
                printf("\n%5s  %11s  %-15s %s\n", "Den", "Cas", "Scena", "Interpret");
                printf("----------------------------------------------------------\n");
            }
            vypis_vystoupeni(f, &f->vystoupeni[i]);
            pocet++;
        }
    }
    return pocet;
}

void menu_program(Festival *f)
{
    int volba, den, zacatek, konec, volba_sceny;
    char text_buf[MAX_TEXT];
    Vysledek v;

    while (1) {
        printf("\n--- Sprava programu ---\n");
        printf("1) Pridat scenu\n");
        printf("2) Pridat vystoupeni\n");
        printf("3) Vypsat program\n");
        printf("4) Vystoupeni konkretniho interpreta\n");
        printf("0) Zpet\n");

        if (!nacti_cislo("Vyberte akci: ", 0, 4, &volba)) return;

        if (volba == 0) {
            return;
        } else if (volba == 1) {
            if (!nacti_text("Zadejte nazev nove sceny: ", text_buf, MAX_TEXT)) return;
            v = scena_pridej(f, text_buf);
            if (v == OK) {
                printf("Scena uspesne pridana.\n");
                f->zmeneno = 1;
            } else {
                printf("Chyba: %s\n", vysledek_text(v));
            }
        } else if (volba == 2) {
            if (f->pocet_interpretu == 0) {
                printf("Chyba: Zatim neexistuje zadny interpret. Nejdriv nejakeho pridejte.\n");
                continue;
            }
            if (f->pocet_scen == 0) {
                printf("Chyba: Zatim neexistuje zadna scena. Nejdriv vytvorte scenu (volba 1).\n");
                continue;
            }

            if (!nacti_text("Zadejte nazev interpreta: ", text_buf, MAX_TEXT)) return;
            int idx_int = interpret_najdi_nazev(f, text_buf);
            if (idx_int == -1) {
                printf("Chyba: Interpret '%s' nebyl nalezen.\n", text_buf);
                continue;
            }
            int id_interpreta = f->interpreti[idx_int].id;

            int max_den = (f->pocet_dni > 0) ? f->pocet_dni : 365;
            if (!nacti_cislo("Zadejte den vystoupeni: ", 1, max_den, &den)) return;
            if (!nacti_cas("Zadejte cas zacatku (HH:MM): ", &zacatek)) return;
            if (!nacti_cas("Zadejte cas konce (HH:MM): ", &konec)) return;

            printf("Dostupne sceny:\n");
            for (int i = 0; i < f->pocet_scen; i++) {
                printf("  %d) %s\n", i + 1, f->sceny[i]);
            }
            if (!nacti_cislo("Vyberte cislo sceny: ", 1, f->pocet_scen, &volba_sceny)) return;
            int scena_idx = volba_sceny - 1;

            v = vystoupeni_pridej(f, 0, id_interpreta, den, zacatek, konec, scena_idx);
            if (v == OK) {
                printf("Vystoupeni uspesne pridano.\n");
                f->zmeneno = 1;
            } else {
                printf("Chyba: %s\n", vysledek_text(v));
            }
        } else if (volba == 3) {
            if (program_vypis(f) == 0) {
                printf("Program je zatim prazdny.\n");
            }
        } else if (volba == 4) {
            if (!nacti_text("Zadejte nazev hledaneho interpreta: ", text_buf, MAX_TEXT)) return;
            int idx_int = interpret_najdi_nazev(f, text_buf);
            if (idx_int == -1) {
                printf("Interpret nebyl nalezen.\n");
            } else {
                if (program_vypis_interpreta(f, f->interpreti[idx_int].id) == 0) {
                    printf("Tento interpret zatim nema zadne planovane vystoupeni.\n");
                }
            }
        }
    }
}