# Správa hudebního festivalu

Semestrální projekt v jazyce C. Konzolový program pro evidenci interpretů, programu festivalu a prodeje vstupenek s ukládáním dat do souboru.

## Sestavení a spuštění

```bash
make
./festival
```

Data se ukládají do souboru `festival.txt` ve složce programu.

## Struktura projektu

```
include/     hlavičkové soubory (datové typy a rozhraní modulů)
src/         zdrojové kódy modulů
docs/        ARCHITEKTURA.md – datové typy, pravidla, formát souboru
             VYVOJARSKA.md   – vývojářská dokumentace
prezentace/  prezentace projektu
Makefile
```

Podrobný popis architektury je v [docs/ARCHITEKTURA.md](docs/ARCHITEKTURA.md).

## Tým a role

| Člen | Role | Zodpovídá za |
|---|---|---|
| **Jakub Macura** | vedoucí týmu, správce architektury | návrh architektury a datových typů, rozdělení úkolů, koordinace, slučování pull requestů do `main`, sjednocení záznamu testů, kontrola dokumentace a prezentace |
| **Filip** | hlavní vývojář | implementace jádra programu, technické detaily kódu, code review |
| **Bojdan** | vývojář | vstupenky a práce se soubory |
| **Saša** | vývojář, dokumentace | rozšíření programu, uživatelská a vývojářská dokumentace, prezentace |

## Rozdělení práce

Práce probíhá ve třech fázích podle toho, jak na sobě části programu závisí.

### Fáze 0 – architektura (Jakub) ✅

Datové typy (`festival.h`), rozhraní všech modulů (`include/*.h`), kostry zdrojových souborů s popisem, co mají funkce dělat, `main.c`, `festival.c` a dokumentace architektury.

### Fáze 1 – jádro programu (Filip)

| Soubory | Úkoly | Testy |
|---|---|---|
| `input.c`, `interpret.c`, `program.c`, `menu.c`, `Makefile` | bezpečné čtení vstupu, správa interpretů (přidání, duplicita, hledání podle názvu a žánru), scény a vystoupení, kontrola času a kolizí, řazení programu, hlavní nabídka | 1–8, 12, 15 |

Jako první musí být hotové `input.c` a `interpret.c`, protože je používají ostatní moduly.

### Fáze 2 – vstupenky a ukládání dat (Bojdan)

Začíná, jakmile jsou hotové funkce `interpret_pridej`, `scena_pridej` a `vystoupeni_pridej`.

| Soubory | Úkoly | Testy |
|---|---|---|
| `vstupenky.c`, `storage.c` | kapacita a prodej vstupenek, přehled obsazenosti, uložení dat do souboru, načtení při spuštění, ošetření neúplných a poškozených dat, ukončení programu bez ztráty dat | 9, 10, 11, 13, 14, 16 |

### Fáze 3 – rozšíření, dokumentace a prezentace (Saša)

Začíná nad hotovou a funkční verzí z fází 1 a 2. Rozšíření jsou v samostatném souboru, aby nezasahovala do povinných funkcí.

| Soubory | Úkoly | Testy |
|---|---|---|
| `rozsireni.c` | volitelné funkce: filtrování programu podle dne a podle scény, vyhledání interpreta podle země, export programu do textového souboru | testy vlastních rozšíření |
| `README.md` | uživatelský návod (sekce níže): ovládání menu, ukázky použití, chybové hlášky | – |
| `docs/VYVOJARSKA.md` | vývojářská dokumentace: popis modulů a jejich funkcí, datových struktur, formátu souboru a způsobu sestavení (vychází z `include/*.h` a `ARCHITEKTURA.md`) | – |
| `prezentace/` | prezentace projektu: zadání, architektura, rozdělení práce, ukázka programu, výsledky testů | – |

Prezentace a dokumentace musí být hotové **týden před termínem prezentace**, aby je Jakub stihl zkontrolovat.

### Testování

- Každý vývojář provede a zaznamená testy svých modulů.
- Jakub výsledky sjednotí do jednoho záznamu a před prezentací se všech 16 scénářů ze zadání provede znovu na finální verzi.

### Pravidla spolupráce

- Každý pracuje ve vlastní větvi. Do `main` jde kód jen přes pull request.
- Filip dělá code review, Jakub pull request po schválení sloučí do `main`.
- Kód se před sloučením musí přeložit bez varování (`-Wall -Wextra`).
- Změny datových typů (`festival.h`), rozhraní modulů (`include/*.h`) a formátu souboru schvaluje Jakub.
- Pokud část práce není hotová v dohodnutém termínu, Jakub ji přidělí jinému členovi týmu, nebo se vynechá (u volitelných funkcí).

## Uživatelský návod

*Doplní Saša ve fázi 3.*
