#ifndef MY_USART_FUNCTIONS
#define MY_USART_FUNCTIONS

#include "PIN_LPC17xx.h"
#include "lpc17xx_ssp.h"
#include "cpu_lpc1000.h"
#include <stdlib.h>
#include "MyLcdFunctions.h"

// wysyla wiadomosc przez UART
// string[] - string do wyslania
void sendUsartString(char string[]);

// wysyla wiadomosc przez UART i idzie do nowej linii
// string[] - string do wyslania
void sendUsartStringNewLine(char string[]);

// pobiera char z UART
char getChar();

// pobiera tekst od urzadzenia zewnetrzego przez UART do 
// wyslanie '`' to informacja o nowej lini
// wyswietla otrzymana wiadomosc na bierzaco na wyswietlaczu LCD
// buffer - bufer do zapisania odebranej wiadomosci
// maxLen - maksymalna dlugosc przyjetej wiadomosci
void getResponseFromUart(char* buffer, int maxLen);

// Konfiguracja UARTa
void UartConfigure();

// wysyla do urzdzenia zewnetrznego prompt o wpisaniu wiadomosci do wyslania radiem
// sendMsgBuff - bufor na przyjeta wiadomosc
// size - rozmiar bufora
void receiveMessageFromUart(char* sendMsgBuff, int size);

// wysyla do urzdzenia zewnetrznego prompt o wpisaniu nazwy uzytkownika
// pobiera odpowiedz i zapisuje ja do bufora 'uzytkownik'
// uzytkownik - bufor na przyjeta odpowiedz
// size - rozmiar bufora
void getUser(char* uzytkownik, int size);

// wysyla do urzadzenia zewnetrznego prompt o podaniu kanalu do komunikacji radiowej
// na podstawie otrzymanej wiadomosci zwraca numer kanalu
int getChannel();

// wyswietla instrukcje na urzadzeniu zewnetrznym i pobiera nazwe uzytkownika oraz kanal radiowy
void getUserAndChannel(char* user, int* channel, int userSize);

#endif