/*
 * input.c - nacitani vstupu od uzivatele
 * Vlastnik: Filip
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "input.h"

#define MAX_RADEK 256

/* Pomocna: nacte jeden radek do buf bez '\n'. Vraci 0 pri EOF.
 * Prilis dlouhy radek: zbytek zahodit (cist getchar() do '\n')
 * a vratit prazdny retezec, at se dotaz zopakuje. */
static int nacti_radek(const char *vyzva, char *buf, int velikost)
{
    /* TODO:
     * 1. printf vyzvy
     * 2. fgets(buf, velikost, stdin) == NULL -> return 0
     * 3. pokud v buf neni '\n' -> radek byl delsi -> zahodit zbytek
     * 4. odstranit '\n' a mezery na zacatku/konci
     */
    return 0;
}

int nacti_text(const char *vyzva, char *text, int velikost)
{
    /* TODO: smycka - nacti_radek; dokud !text_je_platny -> vypsat duvod, znovu */
    return 0;
}

int nacti_cislo(const char *vyzva, int min, int max, int *cislo)
{
    /* TODO: smycka:
     * - nacti_radek
     * - strtol(buf, &konec, 10); chyba kdyz konec == buf nebo *konec != '\0'
     *   (odmitne "abc", "12abc", prazdny vstup)
     * - mimo <min, max> -> "Zadejte cislo od %d do %d."
     */
    return 0;
}

int nacti_cas(const char *vyzva, int *minuty)
{
    /* TODO: smycka - format HH:MM (sscanf "%d:%d" + kontrola, ze nic nezbylo),
     * hodiny 0-24, minuty 0-59, 24:00 je max; *minuty = h*60 + m */
    return 0;
}

int nacti_ano_ne(const char *vyzva, int *odpoved)
{
    /* TODO: smycka - "a"/"A" -> 1, "n"/"N" -> 0, jinak znovu */
    return 0;
}

int stejny_text(const char *a, const char *b)
{
    /* TODO: porovnat znak po znaku pres tolower(), vratit 1 kdyz shodne */
    return 0;
}

int text_je_platny(const char *text)
{
    /* TODO: 1 kdyz text neni prazdny a neobsahuje ';' (strchr) */
    return 0;
}

void vypis_cas(int minuty)
{
    printf("%02d:%02d", minuty / 60, minuty % 60);
}
