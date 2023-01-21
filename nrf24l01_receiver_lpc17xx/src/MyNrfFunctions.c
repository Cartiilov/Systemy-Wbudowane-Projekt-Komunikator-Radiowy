#include "MyNrfFunctions.h"

extern char msgPieceBufReceive[_Buffer_Size];
extern char msgPieceBufSend[_Buffer_Size];

void NRF24L01_Receive(char Buf[_Buffer_Size])
{
	NRF24L01_CE_HIGH;
	Delay_ms(130);

	while ((NRF24L01_Get_Status() & _RX_DR) != _RX_DR);

	NRF24L01_CE_LOW;

	NRF24L01_Read_RX_Buf(Buf, _Buffer_Size);
	NRF24L01_Clear_Interrupts();
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

bool msgToReceivePresent()
{
	NRF24L01_CE_HIGH;
	Delay_ms(130);
	bool isMsg = (NRF24L01_Get_Status() & _RX_DR) == _RX_DR;
	NRF24L01_CE_LOW;
	return isMsg;
}

void getMsgAndPrint()
{
	NRF24L01_Receive(msgPieceBufReceive);
	sendUsartStringNewLine("Received msg:");
	sendUsartStringNewLine(msgPieceBufReceive);
	NRF24L01_Flush_RX();
}
