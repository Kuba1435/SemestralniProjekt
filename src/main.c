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


//docasnej testovaci program pro vse co udelal sikovnej filipek (input.c, interpreter,vstupenky)
//spusteni ve stylu:  gcc -Wall -Wextra -I include src/main.c src/festival.c src/input.c src/interpret.c src/vstupenky.c src/program.c -o festival_test
//.\festival_test.exe

/*
#include <stdio.h>
#include "festival.h"
#include "interpret.h"
#include "vstupenky.h"
#include "program.h"
#include "input.h"

int main(void)
{
    Festival f;
    int volba;
    
    festival_init(&f);
    
    printf("--- TESTOVACI SPUSTENI: KOMPLETNI MODULY ---\n");
    
    while (1) {
        printf("\n=== HLAVNI TESTOVACI MENU ===\n");
        printf("1) Sprava interpretu\n");
        printf("2) Sprava programu (sceny a vystoupeni)\n");
        printf("3) Sprava vstupenek\n");
        printf("0) Ukoncit testovani\n");
        
        if (!nacti_cislo("Vyberte modul pro testovani: ", 0, 3, &volba)) {
            break; 
        }
        
        if (volba == 0) {
            break;
        } else if (volba == 1) {
            menu_interpreti(&f);
        } else if (volba == 2) {
            menu_program(&f);
        } else if (volba == 3) {
            menu_vstupenky(&f);
        }
    }
    
    festival_uvolni(&f);
    
    printf("Testovaci program uspesne skoncil.\n");
    return 0;
}
*/
