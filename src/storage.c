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
#include "input.h"

#define MAX_LINE 1024
#define MAX_POLI 10

/* Pomocna: bezpecne rozdeleni radku podle znaku ';'.
 * Vraci pocet nalezenych poli, nebo -1 pokud je poli vice nez max_poli.
 * Jednotlive podretezce jsou zakonceny '\0' primo v bufferu radek. */
static int rozdel_radek(char *radek, char *pole[], int max_poli)
{
    int pocet = 0;
    char *start = radek;
    char *p = radek;

    while (*p != '\0') {
        if (*p == ';') {
            *p = '\0';
            if (pocet < max_poli) {
                pole[pocet++] = start;
            } else {
                return -1;
            }
            start = p + 1;
        }
        p++;
    }

    if (pocet < max_poli) {
        pole[pocet++] = start;
    } else {
        return -1;
    }

    return pocet;
}

/* Pomocna: nacte cele cislo z textu. Vraci 1 pri uspechu, 0 pri chybe. */
static int parsuj_int(const char *str, int *vysledek)
{
    if (str == NULL || *str == '\0') {
        return 0;
    }
    char *end;
    long val = strtol(str, &end, 10);
    if (end == str || *end != '\0') {
        return 0;
    }
    *vysledek = (int)val;
    return 1;
}

Vysledek storage_uloz(Festival *f, const char *soubor)
{
    if (f == NULL || soubor == NULL) {
        return CHYBA_SOUBOR;
    }

    FILE *fp = fopen(soubor, "w");
    if (fp == NULL) {
        return CHYBA_SOUBOR;
    }

    /* 1. Zakladni informace o festivalu */
    if (fprintf(fp, "FESTIVAL;%s;%d\n", f->nazev, f->pocet_dni) < 0) {
        fclose(fp);
        return CHYBA_SOUBOR;
    }

    /* 2. Vstupenky */
    if (fprintf(fp, "VSTUPENKY;%d;%d\n", f->kapacita, f->prodano) < 0) {
        fclose(fp);
        return CHYBA_SOUBOR;
    }

    /* 3. Sceny */
    for (int i = 0; i < f->pocet_scen; i++) {
        if (fprintf(fp, "SCENA;%s\n", f->sceny[i]) < 0) {
            fclose(fp);
            return CHYBA_SOUBOR;
        }
    }

    /* 4. Interpreti */
    for (int i = 0; i < f->pocet_interpretu; i++) {
        Interpret *it = &f->interpreti[i];
        if (fprintf(fp, "INTERPRET;%d;%s;%s;%s\n", it->id, it->nazev, it->zanr, it->zeme) < 0) {
            fclose(fp);
            return CHYBA_SOUBOR;
        }
    }

    /* 5. Vystoupeni */
    for (int i = 0; i < f->pocet_vystoupeni; i++) {
        Vystoupeni *v = &f->vystoupeni[i];
        if (fprintf(fp, "VYSTOUPENI;%d;%d;%d;%d;%d;%d\n",
                    v->id, v->id_interpreta, v->den, v->zacatek, v->konec, v->scena) < 0) {
            fclose(fp);
            return CHYBA_SOUBOR;
        }
    }

    if (fclose(fp) != 0) {
        return CHYBA_SOUBOR;
    }

    f->zmeneno = 0;
    return OK;
}

Vysledek storage_nacti(Festival *f, const char *soubor)
{
    if (f == NULL || soubor == NULL) {
        return CHYBA_SOUBOR;
    }

    FILE *fp = fopen(soubor, "r");
    if (fp == NULL) {
        return CHYBA_SOUBOR;
    }

    festival_uvolni(f);

    char buf[MAX_LINE];
    char *pole[MAX_POLI];
    int cislo_radku = 0;
    int festival_nacten = 0;

    while (fgets(buf, sizeof(buf), fp) != NULL) {
        cislo_radku++;
        size_t len = strlen(buf);

        /* Kontrola prilis dlouheho radku bez znaku '\n' */
        if (len == sizeof(buf) - 1 && buf[len - 1] != '\n') {
            int c;
            while ((c = fgetc(fp)) != '\n' && c != EOF);
            printf("Varovani: radek %d je poskozeny, preskakuji.\n", cislo_radku);
            continue;
        }

        /* Odstraneni konce radku */
        while (len > 0 && (buf[len - 1] == '\n' || buf[len - 1] == '\r')) {
            buf[--len] = '\0';
        }

        /* Prazdny radek preskocit */
        if (len == 0) {
            continue;
        }

        int pocet_poli = rozdel_radek(buf, pole, MAX_POLI);
        if (pocet_poli <= 0) {
            printf("Varovani: radek %d je poskozeny, preskakuji.\n", cislo_radku);
            continue;
        }

        if (strcmp(pole[0], "FESTIVAL") == 0) {
            int dni;
            if (!festival_nacten && pocet_poli == 3 &&
                text_je_platny(pole[1]) && strlen(pole[1]) < MAX_TEXT &&
                parsuj_int(pole[2], &dni) && dni >= 1 && dni <= MAX_DNI) {
                strncpy(f->nazev, pole[1], MAX_TEXT - 1);
                f->nazev[MAX_TEXT - 1] = '\0';
                f->pocet_dni = dni;
                festival_nacten = 1;
            } else {
                printf("Varovani: radek %d je poskozeny, preskakuji.\n", cislo_radku);
            }
        } else if (strcmp(pole[0], "VSTUPENKY") == 0) {
            int kap, prod;
            if (pocet_poli == 3 &&
                parsuj_int(pole[1], &kap) && kap >= 0 &&
                parsuj_int(pole[2], &prod) && prod >= 0 && prod <= kap) {
                f->kapacita = kap;
                f->prodano = prod;
            } else {
                printf("Varovani: radek %d je poskozeny, preskakuji.\n", cislo_radku);
            }
        } else if (strcmp(pole[0], "SCENA") == 0) {
            if (pocet_poli == 2 && scena_pridej(f, pole[1]) == OK) {
                /* Scena uspesne pridana */
            } else {
                printf("Varovani: radek %d je poskozeny, preskakuji.\n", cislo_radku);
            }
        } else if (strcmp(pole[0], "INTERPRET") == 0) {
            int id;
            if (pocet_poli == 5 &&
                parsuj_int(pole[1], &id) && id > 0 &&
                interpret_pridej(f, id, pole[2], pole[3], pole[4]) == OK) {
                /* Interpret uspesne pridan */
            } else {
                printf("Varovani: radek %d je poskozeny, preskakuji.\n", cislo_radku);
            }
        } else if (strcmp(pole[0], "VYSTOUPENI") == 0) {
            int id, id_int, den, zacatek, konec, scena;
            if (pocet_poli == 7 &&
                parsuj_int(pole[1], &id) && id > 0 &&
                parsuj_int(pole[2], &id_int) &&
                parsuj_int(pole[3], &den) &&
                parsuj_int(pole[4], &zacatek) &&
                parsuj_int(pole[5], &konec) &&
                parsuj_int(pole[6], &scena) &&
                vystoupeni_pridej(f, id, id_int, den, zacatek, konec, scena) == OK) {
                /* Vystoupeni uspesne pridano */
            } else {
                printf("Varovani: radek %d je poskozeny, preskakuji.\n", cislo_radku);
            }
        } else {
            /* Neznamy typ zaznamu */
            printf("Varovani: radek %d je poskozeny, preskakuji.\n", cislo_radku);
        }
    }

    fclose(fp);

    if (!festival_nacten) {
        festival_uvolni(f);
        return CHYBA_SOUBOR;
    }

    f->zmeneno = 0;
    return OK;
}
