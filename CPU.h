#ifndef CPU_H
#define CPU_H
typedef char * string;
//#define DATA PINA&_BV(PA1)
#include <avr/io.h>
#include <util/delay.h>
#include <string.h>
class USART1 {
	public:
		USART1();
		~USART1();
		void begin(long baudrate, int turbo);
		void send(int info);
		void get();
		void end();
};
class SPI1 {
	public:
		SPI1();
		~SPI1();
		void begin();
		void ethernet(int stat);
		void storage(int stat);
		void send(int mesg);
		int receive();
};
class CPU {
	public:
		CPU();
		~CPU();
		void delay(int del);
		void analogBegin();
		int analog1();
		int analog2();
		int analog3();
};
#endif
		
