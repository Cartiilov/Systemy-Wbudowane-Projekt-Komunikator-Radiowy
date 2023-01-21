#ifndef MY_LED_FUNCTIONS
#define MY_LED_FUNCTIONS

#include "cpu_lpc1000.h"

#define LED_DIR_OUT LPC_GPIO0->FIODIR |= (1<<3)
#define LED_ON LPC_GPIO0->FIOCLR |= (1<<3)
#define LED_OFF  LPC_GPIO0->FIOSET |= (1<<3)

// powoduje migniecie diod
void Led_Blink(void);

#endif