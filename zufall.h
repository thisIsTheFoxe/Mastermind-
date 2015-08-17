// Headerdatei zum Erzeugen von Zufallszahlen nach ANSI-Standard
// Die Syntax ist der des Borland C++-Builder angepaßt
// Um die Headrerdatei auch im Borland-Umfeld benutzen zu 
// können, wurden die Funktionen Randomize und random 
// umbenannt
// Erstellt Dezember 2006
// Benjamin Thaut
// TG12/3
// ITG Schwäbisch Gmünd

#ifndef _ZUFALL_H_
#define _ZUFALL_H_

#include <time.h>
#include <stdlib.h>
void randomize2()
{
  srand(time(NULL));
}

int random2(int to)
{
  return rand()%(to);
}

int random_from_to(int from, int to)
{
  return rand()%(to - from + 1) + from;
}

#endif
