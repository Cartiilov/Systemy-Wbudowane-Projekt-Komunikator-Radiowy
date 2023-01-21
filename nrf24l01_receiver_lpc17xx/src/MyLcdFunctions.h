//                     DISCLAIMER!!!
// wartosci zmiennych 'row' i 'col' zaczynaja sie od 1
//   wstawnie wartosci 1 i 1 oznacza lewy gorny rog

#ifndef MY_LCD_FUNCTIONS
#define MY_LCD_FUNCTIONS

#include "asciiLib.h"
#include "LCD_ILI9325.h"
#include "Open1768_LCD.h"

// rysuje linie od punktu (x1, y1) do (x2, y2)
void BresenhamLine(const int x1, const int y1, const int x2, const int y2, const int color);

// wyswietla podana litere 'let' w rzedzie 'row' i kolumnie 'col'
void printLetter(char let, int row, int col);

// wyswietla linie liter w rzedzie 'row' i zaczynajaca sie od kolumny 'col'
void printLine(char* line, int row, int col);

// wyswietla tekst w polu zaczynajacym sie od rzedu 'row' i po prawej od kolumny 'col'
// zawija slowa tak, aby byly pelne i nie rozdzielone
void printText(char* text, int row, int col);

// usuwa litere z ekranu LCD w rzedzie 'row' i kolumnie 'col'
void clearLeterAtPosition(int row, int col);

// usuwa litery z obszaru w ksztalcie prostokata o wierzcholkach
// (rowStart, colStart) i (rowEnd, colEnd)
void clearFragment(int rowStart, int colStart, int rowEnd, int colEnd);

// czysci ekran LCD
void clearScreen();

// wyswietla trojkat
void printTriangle(int x, int y, int color);

// wyswietla ramke
void drawBorder();

#endif