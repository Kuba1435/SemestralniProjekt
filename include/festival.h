/*
 * festival.h
 * Spolecne datove typy celeho projektu.
 *
 * POZOR: tento soubor pouzivaji vsichni - zmeny schvaluje Jakub (spravce architektury)!
 */
#ifndef FESTIVAL_H
#define FESTIVAL_H

#define MAX_TEXT  64    /* max. delka textu vcetne '\0' (nazev, zanr, zeme, scena) */
#define MAX_SCEN  10    /* max. pocet scen */
#define MAX_DNI   14    /* max. pocet dni festivalu */

/* Navratove kody funkci, ktere meni data (pridej, prodej, nacti...) */
typedef enum {
    OK = 0,
    CHYBA_VSTUP,        /* prazdny text, zaporne cislo, hodnota mimo rozsah */
    CHYBA_DUPLICITA,    /* interpret se stejnym nazvem uz existuje */
    CHYBA_NENALEZENO,   /* interpret neexistuje */
    CHYBA_CAS,          /* konec pred zacatkem, spatny den */
    CHYBA_KOLIZE,       /* scena je v tu dobu obsazena */
    CHYBA_INTERPRET_HRAJE, /* interpret v tu dobu uz hraje (i na jine scene) */
    CHYBA_KAPACITA,     /* tolik vstupenek uz neni k dispozici */
    CHYBA_PAMET,        /* malloc/realloc selhal */
    CHYBA_SOUBOR        /* soubor nelze otevrit nebo je poskozeny */
} Vysledek;

typedef struct {
    int  id;                /* cislo interpreta, prideluje se automaticky od 1 */
    char nazev[MAX_TEXT];   /* nesmi se opakovat (bez ohledu na velka/mala pismena) */
    char zanr[MAX_TEXT];
    char zeme[MAX_TEXT];
} Interpret;

typedef struct {
    int id;                 /* cislo vystoupeni, prideluje se automaticky od 1 */
    int id_interpreta;      /* kdo hraje - odkaz na Interpret.id */
    int den;                /* 1 .. pocet_dni */
    int zacatek;            /* cas v minutach od pulnoci: 20:30 = 20*60+30 = 1230 */
    int konec;              /* max. 1440 (= 24:00), vystoupeni pres pulnoc nejsou */
    int scena;              /* index do pole Festival.sceny (0 .. pocet_scen-1) */
} Vystoupeni;

/* Vsechna data programu jsou v jedne strukture.
 * Kazda funkce dostane ukazatel Festival *f. */
typedef struct {
    /* zakladni informace */
    char nazev[MAX_TEXT];
    int  pocet_dni;
    char sceny[MAX_SCEN][MAX_TEXT];
    int  pocet_scen;

    /* interpreti - dynamicke pole */
    Interpret *interpreti;
    int pocet_interpretu;           /* kolik interpretu je ulozeno */
    int alokovano_interpretu;       /* pro kolik je alokovana pamet */
    int dalsi_id_interpreta;

    /* vystoupeni - dynamicke pole */
    Vystoupeni *vystoupeni;
    int pocet_vystoupeni;
    int alokovano_vystoupeni;
    int dalsi_id_vystoupeni;

    /* vstupenky */
    int kapacita;                   /* max. pocet vstupenek */
    int prodano;                    /* 0 .. kapacita */

    int zmeneno;                    /* 1 = jsou neulozene zmeny */
} Festival;

void        festival_init(Festival *f);     /* vse vynuluje, dalsi_id = 1 */
void        festival_uvolni(Festival *f);   /* free() dynamickych poli */
const char *vysledek_text(Vysledek v);      /* text chyby pro uzivatele */

#endif
