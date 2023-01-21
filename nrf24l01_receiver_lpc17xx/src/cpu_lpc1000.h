/*
 * @author
 * Copyright (C) 2012 Luis R. Hilario http://www.luisdigital.com
 *
 */

#include "LPC17xx.h"

/* Port 1, bit 31 is set to GPIO output (NRF24L01 CE) */
#define NRF24L01_CE_OUT		LPC_GPIO1->FIODIR |= (1U<<31)   //P1.31 GPIO CE OUT
#define NRF24L01_CSN_OUT	LPC_GPIO0->FIODIR |= (1U<<9)   //P0.9 GPIO CSN OUT

#define NRF24L01_CE_HIGH	LPC_GPIO1->FIOSET = (1U<<31)
#define NRF24L01_CE_LOW		LPC_GPIO1->FIOCLR = (1U<<31)

#define NRF24L01_CSN_HIGH	LPC_GPIO0->FIOSET = (1<<9)
#define NRF24L01_CSN_LOW	LPC_GPIO0->FIOCLR = (1<<9)

void Delay_Init(void);
void Delay_ms(int us);
void SSPInit(void);
char SPI(char TX_Data);
