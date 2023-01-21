#include "MyUsartFunctions.h"

// wysyla wiadomosc przez UART
// string[] - string do wyslania
void sendUsartString(char string[])
{
	for (int i = 0; string[i] != '\0';)
		if ((LPC_UART0->LSR & (1<<5)) == (1<<5))
			LPC_UART0->THR = string[i++];
}

// wysyla wiadomosc przez UART i idzie do nowej linii
// string[] - string do wyslania
void sendUsartStringNewLine(char string[])
{
	sendUsartString(string);
	LPC_UART0->THR = '\r';
	LPC_UART0->THR = '\n';
}

// pobiera char z UART
char getChar()
{
	while (!(LPC_UART0->LSR & (1 << 0))) continue;
  return LPC_UART0->RBR;
}

// pobiera tekst od urzadzenia zewnetrzego przez UART do 
// wyslanie '`' to informacja o nowej lini
// wyswietla otrzymana wiadomosc na bierzaco na wyswietlaczu LCD
// buffer - bufer do zapisania odebranej wiadomosci
// maxLen - maksymalna dlugosc przyjetej wiadomosci
void getResponseFromUart(char* buffer, int maxLen)
{
	char c;
	int i = 0;
	char t[2] = " ";
	int row = 5;
	int col = 3;
	while (1)
	{
		c = getChar();
		if (c == '\r') break;
		if (c == '`')
		{
			sendUsartStringNewLine("");
			buffer[i++] = ' ';
			printLetter(' ', row, col++);
			continue;
		}
		if (c == 8) // backspace
		{
			buffer[--i] = '\0';
			t[0] = '\r';
			clearLeterAtPosition(row, --col);
			sendUsartString(t);
			sendUsartString(buffer);
			continue;
		}
		buffer[i++] = c;
		t[0] = c;
		sendUsartString(t);
		printLetter(c, row, col++);
		if (col > 38)
		{
			row++;
			col = 3;
		}
		if (i == maxLen-1) break;
	}
	buffer[i] = '\0';
	sendUsartStringNewLine("");
	clearFragment(5, 3, row, 38);
}

// Konfiguracja UARTa
void UartConfigure()
{
	PIN_Configure(0, 2, 1, 0, 0);
	PIN_Configure(0, 3, 1, 0, 0);
	
	LPC_UART0->LCR = 3 | (1<<7);
	LPC_UART0->DLM = 0;
	LPC_UART0->DLL = 9;
	LPC_UART0->FDR = 1 | (2<<4);
	LPC_UART0->LCR = 3;
}

// wysyla do urzdzenia zewnetrznego prompt o wpisaniu wiadomosci do wyslania radiem
// sendMsgBuff - bufor na przyjeta wiadomosc
// size - rozmiar bufora
void receiveMessageFromUart(char* sendMsgBuff, int size)
{
	sendUsartStringNewLine("Wpisz wiadomosc, ktora chcesz wyslac (max 32 znaki):");
	getResponseFromUart(sendMsgBuff, size);
}

// wysyla do urzdzenia zewnetrznego prompt o wpisaniu nazwy uzytkownika
// pobiera odpowiedz i zapisuje ja do bufora 'uzytkownik'
// uzytkownik - bufor na przyjeta odpowiedz
// size - rozmiar bufora
void getUser(char* uzytkownik, int size)
{
	sendUsartStringNewLine("Wprowadz nazwe uzytkownika:");
	getResponseFromUart(uzytkownik, size);
}

// wysyla do urzadzenia zewnetrznego prompt o podaniu kanalu do komunikacji radiowej
// na podstawie otrzymanej wiadomosci zwraca numer kanalu
int getChannel()
{
	char kanal[5];
	sendUsartStringNewLine("Wprowadz kanal na ktorym bedziesz sie komunikowac [0...125]:");
	getResponseFromUart(kanal, sizeof(kanal)/sizeof(char));
	int channel = atoi(kanal);
	if (channel < 0 || channel > 125) { return getChannel(); }
	return channel;
}

// wyswietla instrukcje na urzadzeniu zewnetrznym i pobiera nazwe uzytkownika oraz kanal radiowy
void getUserAndChannel(char* user, int* channel, int userSize)
{
	printLine("Podazaj za instrukcjami na komputerze", 1, 1);
	getUser(user, userSize);
	*channel = getChannel();
	clearScreen();
}
