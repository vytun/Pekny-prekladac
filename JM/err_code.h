
#define OK 0

//chyba v programu v rámci lexikální analýzy (chybná struktura aktuálního lexému).
#define ERR_LEX 1

//chyba v programu v rámci syntaktické analýzy (chybná syntaxe programu)
#define ERR_SYN 2

//sémantická chyba v programu – nedefinovaná funkce/proměnná, pokus o redefinici funkce/proměnné, atd.
#define ERR_NDEF 3

//sémantická chyba typové kompatibility v aritmetických, řetězcových a relačních výrazech, příp. špatný počet či typ parametrů u volání funkce.
#define ERR_TYPE 4

//ostatní sémantické chyby
#define ERR_OTHER 5

//interní chyba překladače tj. neovlivněná vstupním programem (např. chyba alokace paměti, atd.)
#define ERR_INT 99
