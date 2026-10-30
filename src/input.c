/*
 * input.c - nacitani vstupu od uzivatele
 * Vlastnik: Filip (HOTOVO)
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "input.h"

#define MAX_RADEK 256

/* Pomocna: nacte jeden radek do buf bez '\n'. Vraci 0 pri EOF.
 * Prilis dlouhy radek: zbytek zahodit a vratit prazdny retezec. */
static int nacti_radek(const char *vyzva, char *buf, int velikost)
{
    if (vyzva != NULL) {
        printf("%s", vyzva);
        fflush(stdout); /* aby se vyzva vypsala hned pred nacitanim */
    }

    if (fgets(buf, velikost, stdin) == NULL) {
        return 0; /* Konec vstupu (EOF) */
    }

    size_t len = strlen(buf);

    /* Kontrola, zda radek nebyl moc dlouhy (chybi \n a neni to konec souboru) */
    if (len == (size_t)(velikost - 1) && buf[len - 1] != '\n') {
        int ch;
        while ((ch = getchar()) != '\n' && ch != EOF); /* zahozeni zbytku radku */
        buf[0] = '\0'; /* vracime prazdny retezec, at se dotaz zopakuje */
        return 1;
    }

    /* Odstraneni '\n' na konci */
    if (len > 0 && buf[len - 1] == '\n') {
        buf[len - 1] = '\0';
        len--;
    }

    /* Orezani mezer na zacatku a na konci */
    char *start = buf;
    while (isspace((unsigned char)*start)) {
        start++;
    }
    
    char *end = buf + strlen(buf) - 1;
    while (end >= start && isspace((unsigned char)*end)) {
        *end = '\0';
        end--;
    }

    /* Presunuti orezaneho textu na zacatek bufferu */
    if (start != buf) {
        memmove(buf, start, strlen(start) + 1);
    }

    return 1;
}

int text_je_platny(const char *text)
{
    if (text == NULL || *text == '\0') {
        return 0;
    }
    if (strchr(text, ';') != NULL) {
        return 0;
    }
    return 1;
}

int nacti_text(const char *vyzva, char *text, int velikost)
{
    char buf[MAX_RADEK];
    while (1) {
        if (!nacti_radek(vyzva, buf, sizeof(buf))) return 0;
        
        if (!text_je_platny(buf)) {
            printf("Chyba: Text nesmi byt prazdny a nesmi obsahovat znak ';'.\n");
            continue;
        }
        if (strlen(buf) >= (size_t)velikost) {
            printf("Chyba: Text je prilis dlouhy.\n");
            continue;
        }
        
        strcpy(text, buf);
        return 1;
    }
}

int nacti_cislo(const char *vyzva, int min, int max, int *cislo)
{
    char buf[MAX_RADEK];
    char *konec;
    long hodnota;

    while (1) {
        if (!nacti_radek(vyzva, buf, sizeof(buf))) return 0;

        if (buf[0] == '\0') {
            printf("Chyba: Zadejte cislo.\n");
            continue;
        }

        hodnota = strtol(buf, &konec, 10);

        /* Konec nesmi ukazovat na zacatek (nic nenacteno) a nesmi obsahovat smeti po cisle */
        if (konec == buf || *konec != '\0') {
            printf("Chyba: Neplatny ciselny udaj.\n");
            continue;
        }

        if (hodnota < min || hodnota > max) {
            printf("Chyba: Zadejte cislo v rozsahu %d az %d.\n", min, max);
            continue;
        }

        *cislo = (int)hodnota;
        return 1;
    }
}

int nacti_cas(const char *vyzva, int *minuty)
{
    char buf[MAX_RADEK];
    int h, m;
    char navic;

    while (1) {
        if (!nacti_radek(vyzva, buf, sizeof(buf))) return 0;

        if (buf[0] == '\0') continue;

        /* %c na konci odhali, kdyby uzivatel zadal treba 12:30abc */
        if (sscanf(buf, "%d:%d%c", &h, &m, &navic) != 2) {
            printf("Chyba: Cas zadejte ve formatu HH:MM (napr. 14:30).\n");
            continue;
        }

        if (h < 0 || h > 24 || m < 0 || m > 59 || (h == 24 && m > 0)) {
            printf("Chyba: Neplatny cas. Hodiny musi byt 0-24, minuty 0-59 (max 24:00).\n");
            continue;
        }

        *minuty = h * 60 + m;
        return 1;
    }
}

int nacti_ano_ne(const char *vyzva, int *odpoved)
{
    char buf[MAX_RADEK];
    while (1) {
        if (!nacti_radek(vyzva, buf, sizeof(buf))) return 0;

        if (stejny_text(buf, "a") || stejny_text(buf, "ano")) {
            *odpoved = 1;
            return 1;
        }
        if (stejny_text(buf, "n") || stejny_text(buf, "ne")) {
            *odpoved = 0;
            return 1;
        }
        
        printf("Chyba: Odpovezte prosim 'a' (ano) nebo 'n' (ne).\n");
    }
}

int stejny_text(const char *a, const char *b)
{
    if (a == NULL || b == NULL) return 0;
    
    while (*a && *b) {
        if (tolower((unsigned char)*a) != tolower((unsigned char)*b)) {
            return 0;
        }
        a++;
        b++;
    }
    return (*a == *b);
}

void vypis_cas(int minuty)
{
    printf("%02d:%02d", minuty / 60, minuty % 60);
}