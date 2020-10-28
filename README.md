# -VUT-IZP2
## Popis projektu
Najděte pracovní bod diody.

Mějme jednoduché sériové zapojení diody a rezistoru. Známe Shockleyovu rovnici a jeho konstanty. Napište funkci, která pro dané vstupní napětí U_0 a odpor rezistoru R najde pracovní napětí diody odpovídající zadané přesnosti. Dále napište program, který na základě těchto vstupních parametrů na výstup vytiskne pracovní bod diody, tedy napětí a proud.

## Detailní specifikace
### Překlad a odevzdání zdrojového souboru
Odevzdání: Program implementujte ve zdrojovém souboru proj2.c. Zdrojový soubor odevzdejte prostřednictvím informačního systému.

Překlad: Program překládejte s následujícími argumenty:

`$ gcc -std=c99 -Wall -Wextra -Werror proj2.c -lm -o proj2`
### Spuštění a výstup programu
Vstupní data programu budou zadána jako jeho argumenty:

`$ ./proj2 U0 R EPS
Up=XXXX V
Ip=YYYY A`

kde:

- U0 je hodnota vstupního napětí ve Voltech,
- R je odpor rezistoru v Ohmech a
- EPS je absolutní chyba/přestnost/odchylka (epsilon),
- XXXX je hodnota napětí pracovního bodu diody a
- YYYY je hodnota proudu pracovního bodu diody.
- Formát číselného výstupu XXXX a YYYY odpovídá formátovací značce %g.

### Nápověda a vzorce
Voltampérová charakteristika diody v sériovém zapojení s rezistorem:

![Image alt](https://github.com/44sides/-VUT-IZP2/blob/main/img/Vadiody.png)

Proud v rezistoru:

![Image alt](https://github.com/44sides/-VUT-IZP2/blob/main/img/Resistor.png)

Napětí na rezistoru:

![Image alt](https://github.com/44sides/-VUT-IZP2/blob/main/img/Kz2.png)

Proud v diodě (Shockleyova rovnice):

![Image alt](https://github.com/44sides/-VUT-IZP2/blob/main/img/Dioda.png)

Přičemž uvažujme, že závěrný saturační proud a tepelné napětí mají tyto hodnoty:

![Image alt](https://github.com/44sides/-VUT-IZP2/blob/main/img/I0.png)

![Image alt](https://github.com/44sides/-VUT-IZP2/blob/main/img/Ut.png)

Protože je obvod uzavřený, platí 1. Kirchhoffův zákon:

![Image alt](https://github.com/44sides/-VUT-IZP2/blob/main/img/Kz1.png)

### 1. podúkol
Vyjádřete poslední rovnici pomocí napětí U_p, U_0 a R.

### 2. podúkol
Implementujte algoritmické schema pro výpočet posloupnosti využívající metodu půlení intervalu. Ukončující podmínka bude odpovídat absolutní požadované přesnosti výsledku (epsilon).

### 3. podúkol
Napište funkci diode, která pomocí schematu z 2. podúkolu a vzorce z 1. podúkolu hledá hodnotu napětí U_p. Počáteční interval napětí bude od 0 do U_0.

`double diode(double u0, double r, double eps);`

Ve funkci je u0 hodnota vstupního napětí, r je odpor rezistoru a eps je absolutní přesnost (maximální požadovaná odchylka). Funkce v návratové hodnotě vrací nalezené napětí U_p.

### Příklady výstupů
```sh
$ ./proj2 12 47 1e-2
Up=0.673828 V
Ip=0.207937 A
```

```sh
$ ./proj2 12 47 1e-7
Up=0.677633 V
Ip=0.240902 A
```

```sh
$ ./proj2 24 330 1e-7
Up=0.64596 V
Ip=0.0707696 A
```

```sh
$ ./proj2 24 330 1e-20
Up=0.64596 V
Ip=0.0707698 A
```

```sh
$ ./proj2 inf 5 .5
Up=inf V
Ip=inf A
```

```sh
$ ./proj2 -33 5 .1
error: invalid arguments
```
## Hodnocení
Na výsledném hodnocení mají hlavní vliv následující faktory:

- implementace algoritmického schematu pro iterační výpočet,
- implementace metody půlení intervalu a výpočet pracovního bodu,
- ošetření neočekávaných stavů.
