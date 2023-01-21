#include "MyLcdFunctions.h"
#include "MyUsartFunctions.h"
#include "MyJoystickFunctions.h"
#include "MyGuiFunctions.h"
#include "MyNrfFunctions.h"
#include <stdio.h>

char user[30];
int channel;
char msgPieceBufReceive[_Buffer_Size];
char msgPieceBufSend[_Buffer_Size];
char Address[_Address_Width] = { 0x11, 0x22, 0x33, 0x44, 0x55 };
// magazyn 5 ostatnich otrzymanych wiadomosci
char* msgStorage[5];

int main(void)
{
	UartConfigure();
	SSPInit();
	Delay_Init();
	lcdConfiguration();
	init_ILI9325();
	innitGUI();
	Delay_ms(20);
	clearScreen();
	
	getUserAndChannel(user, &channel, sizeof(user)/sizeof(char));
	NRF24L01_Init(_RX_MODE, channel, _1Mbps, Address, _Address_Width, _Buffer_Size);
	drawGUI(1);
	
	while (1)
	{
		JoystickManage();
		if (msgToReceivePresent()) getMsgAndPrint();
	}
}