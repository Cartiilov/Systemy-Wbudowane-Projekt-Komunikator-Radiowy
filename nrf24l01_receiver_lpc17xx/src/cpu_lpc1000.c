/*
 * @author
 * Copyright (C) 2012 Luis R. Hilario http://www.luisdigital.com
 *
 */

#include "cpu_lpc1000.h"
#include "lpc17xx_ssp.h"

volatile uint32_t msTicks;

void SysTick_Handler(void) {
	msTicks++;
}

void Delay_Init(void) {
	SysTick_Config(SystemCoreClock / 1000);
}

void Delay_ms(int ms) {
	msTicks = 0;
	while (msTicks < ms);
}

void SSPInit(void) {
	SSP_CFG_Type sspChannelConfig;

	NRF24L01_CE_OUT;
	NRF24L01_CE_LOW;

	LPC_PINCON->PINSEL0 |= 0x2U<<30; //SCK0
	LPC_PINCON->PINSEL1 |= 0x2<<2;  //MISO0
	LPC_PINCON->PINSEL1 |= 0x2<<4;	//MOSI0

	NRF24L01_CSN_OUT;
	NRF24L01_CSN_HIGH;

	SSP_ConfigStructInit(&sspChannelConfig);
	SSP_Init(LPC_SSP0, &sspChannelConfig);
	SSP_Cmd(LPC_SSP0, ENABLE);
}

char SPI(char TX_Data) {
	while ((LPC_SSP0->SR & (SSP_SR_TNF | SSP_SR_BSY)) != SSP_SR_TNF);
	LPC_SSP0->DR = TX_Data;

	while ((LPC_SSP0->SR & (SSP_SR_BSY | SSP_SR_RNE)) != SSP_SR_RNE);
	return LPC_SSP0->DR;
}
