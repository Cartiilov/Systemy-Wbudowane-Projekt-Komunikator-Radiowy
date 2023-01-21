#include "MyGuiFunctions.h"

void drawGUI(int opt)
{
	drawBorder();
	printTriangle(30, 20, 1);
	printText("Napisz wiadomosc", 3, 6);
}

void drawWriteMessageGUI(int opt)
{
	drawBorder();
	BresenhamLine(LCD_MAX_X-55, 10, LCD_MAX_X-55, LCD_MAX_Y-10, 0);
	BresenhamLine(35, 10, 35, LCD_MAX_Y-10, 0);
	printText("Wpisz swoja wiadomosc w terminalu komputera", 2, 3);
	printTriangle(210, 50, opt);
	printTriangle(210, 175, !opt);
	printText("WYSLIJ", 15, 10);
	printText("WYJDZ", 15, 25);
}

void printMessageAccepted()
{
	printText("Wiadomosc zostala przyjeta, kliknij wyslij", 40, 3);
}

void printMessageSent()
{
	printText("Wyslano wiadomosc", 40, 3);
}
