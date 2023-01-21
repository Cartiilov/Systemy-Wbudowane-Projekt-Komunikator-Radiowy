#include "MyNrfFunctions.h"

// Konfiguruje modul radiowy na kanale 'channel'
void NRFInit(int channel)
{
	NRF24L01_Init(_RX_MODE, channel, _1Mbps, Address, _Address_Width, _Buffer_Size);
}

void NRF24L01_Receive(char Buf[_Buffer_Size])
{
	NRF24L01_CE_HIGH;
	Delay_ms(130);

	while ((NRF24L01_Get_Status() & _RX_DR) != _RX_DR);

	NRF24L01_CE_LOW;

	NRF24L01_Read_RX_Buf(Buf, _Buffer_Size);
	NRF24L01_Clear_Interrupts();
}

// zapisuje otrzymana wiadomosc do jednego ze slotow 'msgStorage'
void saveMsg(char* msg, int msgSize)
{
	// jezeli nadal nie ma pelnej bazy wiadomosci
	for (int i=0; i < 5; ++i)
		if (msgStorage[i] == NULL)
		{
			msgStorage[i] = malloc(msgSize);
			strncpy(msgStorage[i], msg, msgSize);
			return;
		}
	
	// jezeli baza jest pelna i trzeba zwolnic jedno miejsce
	free(msgStorage[0]);
	for (int i=0; i < 4; ++i) msgStorage[i] = msgStorage[i+1];
	msgStorage[4] = malloc(msgSize);
	strncpy(msgStorage[4], msg, msgSize);
}

void NRF24L01_Send(char Buf[_Buffer_Size])
{
	NRF24L01_WriteReg(W_REGISTER | CONFIG, 0b00001010 | _TX_MODE);
	NRF24L01_Write_TX_Buf(Buf, _Buffer_Size);
	NRF24L01_RF_TX();
	
	while ((NRF24L01_Get_Status() & _TX_DS) != _TX_DS);

	NRF24L01_Clear_Interrupts();
	NRF24L01_WriteReg(W_REGISTER | CONFIG, 0b00001010 | _RX_MODE);
}

// dzieli wiadomosc do wyslania na kawalki i wysyla je w krotkich odstepach czasu
void sendMsg(char* msgBuffer, int msgSize)
{
	for (int i=0; i <= msgSize; i+=_Buffer_Size)
	{
		strncpy(msgPieceBufSend, msgBuffSend+i, _Buffer_Size);
		NRF24L01_Send(msgPieceBufSend);
	}
}

// Interrupt uruchamia sie wtedy kiedy RX FIFO jest przynajmniej w polowie pelna.
// Pobiera wiadomosc na rozbita na pare kawalkow.
void SSP0_IRQHandler()
{
	sendUsartStringNewLine("1");
	if (LPC_SSP0->MIS == (1<<2))
	{
		sendUsartStringNewLine("2");
		int i = 0;
		// if (RX FIFO is at least half full)
		while(LPC_SSP0->MIS == (1<<2))
		{
			sendUsartStringNewLine("3");
			NRF24L01_Receive(msgPieceBufReceive);
			strncpy(msgBuffReceive+(_Buffer_Size*i++), msgPieceBufReceive, _Buffer_Size);
		}
		
		saveMsg(msgBuffReceive, strlen(msgBuffReceive)+1);
	}
	NRF24L01_Clear_Interrupts();
}