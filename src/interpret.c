/*
 * interpret.c - sprava interpretu
 * Vlastnik: Filip (HOTOVO)
 * Vzor menu a realloc viz docs/ARCHITEKTURA.md, kapitola Kucharka.
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "interpret.h"
#include "input.h"

Vysledek interpret_pridej(Festival *f, int id, const char *nazev,
                          const char *zanr, const char *zeme)
{
    if (!text_je_platny(nazev) || strlen(nazev) >= MAX_TEXT ||
        !text_je_platny(zanr) || strlen(zanr) >= MAX_TEXT ||
        !text_je_platny(zeme) || strlen(zeme) >= MAX_TEXT) {
        return CHYBA_VSTUP;
    }

    if (interpret_najdi_nazev(f, nazev) != -1) {
        return CHYBA_DUPLICITA;
    }

    if (id > 0 && interpret_najdi_id(f, id) != -1) {
        return CHYBA_DUPLICITA;
    }

    if (f->pocet_interpretu >= f->alokovano_interpretu) {
        int nova_kapacita = (f->alokovano_interpretu == 0) ? 10 : f->alokovano_interpretu * 2;
        Interpret *nove_pole = (Interpret *)realloc(f->interpreti, nova_kapacita * sizeof(Interpret));
        if (nove_pole == NULL) {
            return CHYBA_PAMET;
        }
        f->interpreti = nove_pole;
        f->alokovano_interpretu = nova_kapacita;
    }

    if (id == 0) {
        id = f->dalsi_id_interpreta;
    }

    Interpret *novy = &f->interpreti[f->pocet_interpretu];
    novy->id = id;
    strcpy(novy->nazev, nazev);
    strcpy(novy->zanr, zanr);
    strcpy(novy->zeme, zeme);

    f->pocet_interpretu++;

    if (id >= f->dalsi_id_interpreta) {
        f->dalsi_id_interpreta = id + 1;
    }

    return OK;
}

int interpret_najdi_id(Festival *f, int id)
{
    for (int i = 0; i < f->pocet_interpretu; i++) {
        if (f->interpreti[i].id == id) {
            return i;
        }
    }
    return -1;
}

int interpret_najdi_nazev(Festival *f, const char *nazev)
{
    for (int i = 0; i < f->pocet_interpretu; i++) {
        if (stejny_text(f->interpreti[i].nazev, nazev)) {
            return i;
        }
    }
    return -1;
}

static void vypis_interpreta(Interpret *i)
{
    printf("%4d  %-30s %-15s %s\n", i->id, i->nazev, i->zanr, i->zeme);
}

int interpret_vypis_vse(Festival *f)
{
    if (f->pocet_interpretu == 0) {
        return 0;
    }

    printf("\n%4s  %-30s %-15s %s\n", "ID", "Nazev", "Zanr", "Zeme");
    printf("-----------------------------------------------------------------------\n");
    for (int i = 0; i < f->pocet_interpretu; i++) {
        vypis_interpreta(&f->interpreti[i]);
    }
    return f->pocet_interpretu;
}

int interpret_vypis_zanr(Festival *f, const char *zanr)
{
    int pocet = 0;
    for (int i = 0; i < f->pocet_interpretu; i++) {
        if (stejny_text(f->interpreti[i].zanr, zanr)) {
            if (pocet == 0) {
                printf("\n%4s  %-30s %-15s %s\n", "ID", "Nazev", "Zanr", "Zeme");
                printf("-----------------------------------------------------------------------\n");
            }
            vypis_interpreta(&f->interpreti[i]);
            pocet++;
        }
    }
    return pocet;
}

void menu_interpreti(Festival *f)
{
    int volba;
    char nazev[MAX_TEXT];
    char zanr[MAX_TEXT];
    char zeme[MAX_TEXT];

    while (1) {
        printf("\n--- Sprava interpretu ---\n");
        printf("1) Pridat interpreta\n");
        printf("2) Vypsat vsechny\n");
        printf("3) Hledat podle nazvu\n");
        printf("4) Hledat podle zanru\n");
        printf("0) Zpet\n");

        if (!nacti_cislo("Vyberte akci: ", 0, 4, &volba)) return;

        if (volba == 0) {
            return;
        } else if (volba == 1) {
            if (!nacti_text("Zadejte nazev: ", nazev, MAX_TEXT)) return;
            if (!nacti_text("Zadejte zanr: ", zanr, MAX_TEXT)) return;
            if (!nacti_text("Zadejte zemi puvodu: ", zeme, MAX_TEXT)) return;

            Vysledek v = interpret_pridej(f, 0, nazev, zanr, zeme);
            if (v == OK) {
                printf("Interpret uspesne pridan.\n");
                f->zmeneno = 1;
            } else {
                printf("Chyba: %s\n", vysledek_text(v));
            }
        } else if (volba == 2) {
            if (interpret_vypis_vse(f) == 0) {
                printf("Zadni interpreti.\n");
            }
        } else if (volba == 3) {
            if (!nacti_text("Zadejte nazev hledaneho interpreta: ", nazev, MAX_TEXT)) return;
            int idx = interpret_najdi_nazev(f, nazev);
            if (idx == -1) {
                printf("Interpret nebyl nalezen.\n");
            } else {
                printf("\n%4s  %-30s %-15s %s\n", "ID", "Nazev", "Zanr", "Zeme");
                printf("-----------------------------------------------------------------------\n");
                vypis_interpreta(&f->interpreti[idx]);
            }
        } else if (volba == 4) {
            if (!nacti_text("Zadejte zanr: ", zanr, MAX_TEXT)) return;
            if (interpret_vypis_zanr(f, zanr) == 0) {
                printf("Nic nenalezeno.\n");
            }
        }
    }
}