#include "MyJoystickFunctions.h"
#include "MyGuiFunctions.h"
#include "MyUsartFunctions.h"
#include "MyNrfFunctions.h"

struct GUI choice;
extern char msgPieceBufSend[_Buffer_Size];

void innitGUI()
{
	choice.opt1 = 1;
	choice.opt2 = 0;
	choice.guiPointer = drawGUI;
}

void resetOptions(){
	choice.opt1 = 1;
	choice.opt2 = 0;
}

void changeOptions(){
	choice.opt1 = !choice.opt1;
	choice.opt2 = !choice.opt2;
}

//
void JoystickManage(void)
{
	if ((Joystick_GetState() == 0b01000))
	{
		changeOptions();
		choice.guiPointer(choice.opt1);
		Delay_ms(500);
	}
	else if(Joystick_GetState() == 0b10000){
		changeOptions();
		choice.guiPointer(choice.opt1);
		Delay_ms(500);
	}
	else if (Joystick_GetState() == 0b00100)
	{
		if(choice.guiPointer ==  drawGUI )
		{
			clearScreen();
			choice.guiPointer = drawWriteMessageGUI;
			choice.guiPointer(choice.opt1);
			receiveMessageFromUart(msgPieceBufSend, sizeof(msgPieceBufSend)/sizeof(char));
			printMessageAccepted();
				
			Delay_ms(500);
		}
		else if(choice.guiPointer == drawWriteMessageGUI)
		{
			if(choice.opt1)
			{
				NRF24L01_Send(msgPieceBufSend);
				Delay_ms(500);
				clearFragment(40, 3, 41, 30);
				printMessageSent();
			}
			else
			{
				clearScreen();
				choice.guiPointer = drawGUI;
				choice.guiPointer(choice.opt1);
			}
		}
	}
}