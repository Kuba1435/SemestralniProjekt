# Architektura – Správa hudebního festivalu

Správce architektury: **Jakub**. Změny datových typů, rozhraní modulů a formátu souboru schvaluje on.

Datové typy jsou v [include/festival.h](../include/festival.h), funkce každého modulu v `include/<modul>.h`.

## 1. Data

Všechna data jsou v jedné struktuře `Festival` a každá funkce dostane `Festival *f`.

```
Festival
├── nazev, pocet_dni
├── sceny[]        pole názvů scén (např. "Hlavni", "Mala")
├── interpreti[]   dynamické pole Interpret  { id, nazev, zanr, zeme }
├── vystoupeni[]   dynamické pole Vystoupeni { id, id_interpreta, den, zacatek, konec, scena }
├── kapacita, prodano
└── zmeneno        1 = neuložené změny
```

**Pravidla:**
- Vystoupení odkazuje na interpreta přes **`id_interpreta`**, ne přes index. Index se mění při řazení a mazání.
- Scéna se ve vystoupení ukládá jako **index** do `f->sceny`. Scény se nemažou, takže index se nemění.
- **Čas** se ukládá v minutách od půlnoci: `20:30` = `20*60 + 30` = `1230`. Kolize se tak počítá obyčejným porovnáním čísel.
- **Kolize:** stejný den + stejná scéna + `novy.zacatek < stary.konec && stary.zacatek < novy.konec`. Vystoupení, která na sebe navazují (18:00–19:00 a 19:00–20:00), jsou v pořádku.
- **Interpret na dvou místech:** stejný interpret + stejný den + překryv času → odmítnout (`CHYBA_INTERPRET_HRAJE`), i když jde o jinou scénu.

## 2. Pravidla psaní kódu

1. **Funkce, které mění data** (`*_pridej`, `vstupenky_prodej` …), nic nevypisují. Vrací `Vysledek` a hlášku vypíše menu.
2. **Funkce `*_vypis*`** vypisují přímo a vrací počet vypsaných položek (0 → menu vypíše „nenalezeno“).
3. **Ze vstupu se čte jen přes `input.h`.** Žádný `scanf` nikde jinde.
4. Po každé úspěšné změně dat nastaví menu `f->zmeneno = 1`.
5. Názvy jsou česky bez diakritiky a funkce mají prefix podle modulu: `interpret_`, `vystoupeni_`, `vstupenky_`, `storage_`.
6. Pomocné funkce, které se používají jen v jednom souboru, jsou `static` a nejsou v `.h`.
7. Překládá se s `-Wall -Wextra`. Kód s varováními se nemerguje.

## 3. Kuchařka

### Jak vypadá podmenu

```c
void menu_interpreti(Festival *f)
{
    int volba;
    char nazev[MAX_TEXT], zanr[MAX_TEXT], zeme[MAX_TEXT];
    Vysledek v;

    while (1) {
        printf("\n--- Interpreti ---\n");
        printf("1) Pridat interpreta\n");
        printf("2) Vypsat vsechny\n");
        printf("0) Zpet\n");
        if (!nacti_cislo("Volba: ", 0, 2, &volba)) return;   /* konec vstupu */

        if (volba == 0) return;
        if (volba == 1) {
            if (!nacti_text("Nazev: ", nazev, MAX_TEXT)) return;
            if (!nacti_text("Zanr: ", zanr, MAX_TEXT)) return;
            if (!nacti_text("Zeme: ", zeme, MAX_TEXT)) return;

            v = interpret_pridej(f, 0, nazev, zanr, zeme);
            if (v == OK) {
                printf("Interpret byl pridan.\n");
                f->zmeneno = 1;
            } else {
                printf("Chyba: %s\n", vysledek_text(v));
            }
        }
        if (volba == 2) {
            if (interpret_vypis_vse(f) == 0) printf("Zadni interpreti.\n");
        }
    }
}
```

### Jak přidat prvek do dynamického pole

```c
if (f->pocet_interpretu == f->alokovano_interpretu) {
    int nova = (f->alokovano_interpretu == 0) ? 4 : f->alokovano_interpretu * 2;
    Interpret *p = realloc(f->interpreti, nova * sizeof(Interpret));
    if (p == NULL) return CHYBA_PAMET;
    f->interpreti = p;
    f->alokovano_interpretu = nova;
}
f->interpreti[f->pocet_interpretu] = novy;
f->pocet_interpretu++;
```

## 4. Tok programu (`main.c`)

```c
festival_init(&f);
if (storage_nacti(&f, SOUBOR_DATA) != OK)
    menu_zalozeni_festivalu(&f);          /* první spuštění nebo poškozený soubor */
menu_hlavni(&f);
if (f.zmeneno) -> zeptat se "Ulozit zmeny? (a/n)" -> storage_uloz
festival_uvolni(&f);
```

## 5. Formát souboru `festival.txt`

Textový soubor, jeden záznam na řádek, oddělovač `;`. Na začátku řádku je typ záznamu:

```
FESTIVAL;Letni fest;3
VSTUPENKY;5000;1200
SCENA;Hlavni
SCENA;Mala
INTERPRET;1;Kabat;rock;CZ
INTERPRET;2;Prago Union;hip-hop;CZ
VYSTOUPENI;1;1;1;1200;1290;0
VYSTOUPENI;2;2;1;1080;1140;1
```

- `VYSTOUPENI;id;id_interpreta;den;zacatek;konec;scena`, čas je v minutách.
- Ukládá se v tomto pořadí. Scény a interpreti musí být před vystoupeními, aby šlo zkontrolovat, že existují.
- Řádek s neznámým typem, špatným počtem polí nebo nesmyslnou hodnotou se přeskočí a vypíše se varování.
- Po načtení musí `dalsi_id_*` být větší než největší načtené `id`. To řeší `*_pridej` při volání s `id > 0`.

## 6. Rozdělení práce

Rozdělení práce, fáze a role jsou v [README.md](../README.md#rozdělení-práce).

**Na čem závisí pořadí:**
1. `input.c` a `interpret_najdi_id` musí být hotové jako první, používají je ostatní moduly.
2. `storage.c` se začne psát, až existují `interpret_pridej`, `scena_pridej` a `vystoupeni_pridej`.
3. Rozšíření (`rozsireni.c`) se dělají až nad funkční verzí a do povinných modulů zasahují jen jedním řádkem v menu.

## 7. Volitelná rozšíření (až po dokončení povinných funkcí)

Plánovaná rozšíření: filtrování programu podle dne a podle scény, vyhledání interpreta podle země, export programu do `.txt`.
Rozšíření nesmí měnit `festival.h` ani formát souboru bez domluvy týmu.
