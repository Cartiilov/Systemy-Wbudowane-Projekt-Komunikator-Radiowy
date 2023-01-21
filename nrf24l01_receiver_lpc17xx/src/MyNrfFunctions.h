#ifndef MY_NRF_FUNCTIONS
#define MY_NRF_FUNCTIONS

#include "nrf24l01.h"
#include "cpu_lpc1000.h"
#include <stdlib.h>
#include <string.h>
#include "MyUsartFunctions.h"

#define _Buffer_Size 32
#define	_Address_Width 5

void NRF24L01_Receive(char Buf[_Buffer_Size]);

void NRF24L01_Send(char Buf[_Buffer_Size]);

bool msgToReceivePresent();

void getMsgAndPrint();

#endif