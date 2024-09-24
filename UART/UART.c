#include "UART.h"
#include <string.h>

unsigned int c;	//signed mean 31_bit, unsign to use all 32_bit 
unsigned char recdata; // for receiving DATA
int num = 1;

void UART_Init(void)
{
	//Uart transmitter
	LPC_SC->PCONP |= 0x00000008;
	LPC_PINCON->PINSEL0 = 0x00000050; //select uart0 pin 5,4 as Tx and 7,6 as RX
	LPC_UART0->LCR = 0x83; // enable latch bit for lock to set baudrate, enable 1 stop bit and select 8 bit car length
	
	LPC_UART0->DLL = 0xA2; // Baudrate=9600 -> 25000000/16/9600 = 162.76 =dec, in hex= A2
	LPC_UART0->DLM = 0x00; // 
	
	LPC_UART0->LCR = 0x03; // Disable latch bit for unlock - after set baudrate, enable 1 stop bit and select 8 bit car length
	LPC_UART0->FCR = 0x07; // Enable FIFo, clear Tx and Rx FIFO
	
	//return 0;
}


void UART_printf(char* str)
{
	int length = strlen(str);
	int i;
	
	while((LPC_UART0->LSR & 0x20) == 0x20)  //Try to set data of 5th bit only
	{
			//LPC_UART0->THR = 'A';
			for(i=0; i<=length; i++)
			{
				LPC_UART0->THR = str[i]; // stare all data in THR register
			}
	}
	
		
	/*
  char a[]="Hello Supremology...!\r"; // compile 1st line and print respective statements
	
		
	while((LPC_UART0->LSR & 0x20) == 0x20)  //Try to set data of 5th bit only
	{
			//LPC_UART0->THR = 'A';
			for(i=0; i<=a[i]; i++)
			{
				LPC_UART0->THR = a[i]; // stare all data in THR register
			}
	}
	*/
	//return 0;
}

int main()
{
	UART_Init();

	while(num)
	{
		
		UART_printf("Hello World!");
		num = 0;
	}
}
