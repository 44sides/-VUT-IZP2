/**
 * @file:       proj2.c
 * @date:       01.12.2019
 * @author:     Vladyslav Tverdokhlib, xtverd01@stud.fit.vutbr.cz
 * Projekt 2:   Iteracni vypocty
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <stdbool.h>

// deklarace konstant
#define I0 1e-12
#define Ut 0.0258563

// vyjadreny vzorec pro Up
double func(double x, double u0, double r)
{
  return (I0 * (exp(x/Ut) - 1)) - ((u0 - x)/r);
}

/* Vypocet 'f(x) = 0' s odchylkou podle metody bisekce:
Vznika usecka [a;b] <=> [0;U0], ve ktere je umisteno "x".
Hledame hodnotu delenim potrebnych usecek napul (zuzujeme interval), dokud neni dosazeno urcite odchylky.
Je delena usecka [a_mid_b]. Pokud f(a) * f(mid) < 0, tudiz 'x' lezi v [a_mid] a vybirame tuto novou usecku. Else vybirame [mid_b].
*/
double diode_up(double u0, double r, double eps)
{
  double a = 0, b = u0; // [a;b] <=> [0;U0]
  double mid;
  int i = 0; // pro eps < 1e-15

    do{
        mid = (a + b)/2;

        // pro jistotu
        if (func(mid, u0, r) == 0.0)
            break;

        // definovani nove usecky
        else if (func(a, u0, r)*func(mid, u0, r) < 0)
            b = mid;
        else
            a = mid;

        if(eps < 1e-15) // nemuze vzniknout hodnota < 1e-15 pri iteracnim vypoctu
          {
           i++;
           if(i == 55)
            break;
          }

    }while (fabs (b - a) >= eps);

    return mid; // 'x'
}

// vzorec pro vypocet Ip
double diode_ip(double up)
{
  return I0 * (exp(up/Ut) - 1);
}

/*Kontrolujeme, zda jsou v argumentech zakazane symboly.
atof() vrati double cislo, kdyz potka neco, krome cislic, nebo bude konec radku.
*/
bool letter_argument_test (double u0, double r, double eps, char **argv)
{
  int i = 0;

  //[u0] kontrola
  if(u0 == 0) // atof() vrati '0' => pokud v radku je '0' nebo první symbol neni cislice.
  {
    // pokud je to '0' (#48 ASCII), tudiz nebude po '0' vic cislic (v dalsi bunce radku bude '\0').
    if((int)argv[1][0] != 48 || argv[1][1] != '\0')
      return 1;
  }
  else // atof() vrati cislo => pokud v radku je nejake cislo (krome 0). Dale ale mohou se obsahovat zak. symboly.
      //Pokud jsou dal symboly, krome '.', 'e', 'E' '-' a "inf", tak se zobrazi chyba.
  {
    while(argv[1][i] != '\0')
    {
      // nemuze obsahovat vsechny symboly, krome
      if(((int)argv[1][i] < 48 || (int)argv[1][i] > 57)
      && argv[1][i] != '.'
      && argv[1][i] != 'e' && argv[1][i] != 'E'
      && argv[1][i] != '-'
      && strcmp (argv[1], "inf") != 0 && strcmp (argv[1], "INF") != 0)
        return 1;
      i++;
    }
  }

  i = 0;

  //[r] kontrola
  if (r == 0) // stejny postup. Postupujeme do dalsiho argumentu v pole - argv[2]
  {
    if((int)argv[2][0] != 48 || argv[2][1] != '\0')
      return 1;
  }
  else
  {
    while(argv[2][i] != '\0')
    {
      if(((int)argv[2][i] < 48 || (int)argv[2][i] > 57)
      && argv[2][i] != '.'
      && argv[2][i] != 'e' && argv[2][i] != 'E'
      && argv[2][i] != '-'
      && strcmp (argv[2], "inf") != 0 && strcmp (argv[2], "INF") != 0)
        return 1;
      i++;
    }
  }

  i = 0;

  //[eps] kontrola
  if(eps == 0) // skoro stejny postup. Postupujeme do dalsiho argumentu v pole - argv[3]. Nepovolime jenom "inf" byt argumentem. To je nesmyslne.
  {
    if((int)argv[3][0] != 48 || argv[3][1] != '\0')
      return 1;
  }
  else
  {
    while(argv[3][i] != '\0')
    {
      if(((int)argv[3][i] < 48 || (int)argv[3][i] > 57)
      && argv[3][i] != '.'
      && argv[3][i] != 'e' && argv[3][i] != 'E'
      && argv[3][i] != '-')
        return 1;
      i++;
    }
  }

  return 0;
}

int main (int argc, char *argv[])
{
  if(argc != 4) // Pokud je argumentu vic nez 3
  {printf("Enter data in the 'U0 R EPS' format\n"); return 0;}

  double u0, r, eps;
  double up, ip;
  // prevod na double
  u0 = atof (argv[1]);
  r = atof (argv[2]);
  eps = atof (argv[3]);

  //vystup zpravy neocekavaneho stavu
  if (letter_argument_test (u0, r, eps, argv))
  {
    printf("Wrong arguments\n");
    return 0;
  }

  //vystup zprav neocekavanych stavu
  if (r == 0)
  {printf("You do not have a resistor!\n"); return 0;}
  else if (r < 0)
  {printf("The resistor should be in (0; +inf)\n"); return 0;}
  if (eps <= 0)
  {printf("The error should be in (0; +inf)\n"); return 0;}
  if (u0 < 0)
  {printf("The voltage should be in [0; +inf)\n"); return 0;}

  up = diode_up(u0, r, eps);
  ip = diode_ip(up);

  if(strcmp (argv[2], "inf") == 0 || strcmp (argv[2], "INF") == 0)
    {up = 0; ip = 0;}

  printf("Up=%g V\nIp=%g A\n", up, ip);

  return 0;
}
