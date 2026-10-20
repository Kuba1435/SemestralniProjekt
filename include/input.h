/*
 * input.h
 * Nacitani vstupu od uzivatele. Nikde jinde v programu se nepouziva scanf!
 *
 * Vsechny funkce nacti_* se ptaji tak dlouho, dokud uzivatel nezada
 * spravnou hodnotu. Vraci:
 *   1 = hodnota nactena
 *   0 = konec vstupu (Ctrl+Z / Ctrl+D) -> volajici ma hned skoncit (return)
 */
#ifndef INPUT_H
#define INPUT_H

/* Povinny text - nesmi byt prazdny, nesmi obsahovat ';' */
int nacti_text(const char *vyzva, char *text, int velikost);

/* Cele cislo od min do max (text nebo "12abc" odmitne) */
int nacti_cislo(const char *vyzva, int min, int max, int *cislo);

/* Cas ve tvaru HH:MM, ulozi ho v minutach od pulnoci */
int nacti_cas(const char *vyzva, int *minuty);

/* Odpoved a/n, do odpoved ulozi 1 (ano) nebo 0 (ne) */
int nacti_ano_ne(const char *vyzva, int *odpoved);

/* Vrati 1, pokud jsou texty stejne bez ohledu na velka/mala pismena */
int stejny_text(const char *a, const char *b);

/* Vrati 1, pokud je text neprazdny a neobsahuje ';' */
int text_je_platny(const char *text);

/* Vypise minuty jako HH:MM, napr. 1230 -> "20:30" */
void vypis_cas(int minuty);

#endif
