#include "MyLedFunctions.h"

// powoduje migniecie diod
void Led_Blink(void)
{
	LED_ON;
	Delay_ms(500);
	LED_OFF;
	Delay_ms(500);
}