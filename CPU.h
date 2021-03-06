#ifndef CPU_H
#define CPU_H
typedef char * string;
//#define DATA PINA&_BV(PA1)
#define SSETH PB4
#define SSSD PG5
#define MISO PB3
#define MOSI PB2
#define SCK PB1
#define HWSS PB0
#include <avr/io.h>
#include <util/delay.h>
#include <string.h>
class USART1 {
	public:
		USART1();
		~USART1();
		void begin(long baudrate, int turbo);
		void send(char info);
		void get();
		void end();
};
class USART0 {
	public:
		USART0();
		~USART0();
		void begin(long baudrate, int turbo);
		void send(char info);
		char get();
		void end();
};
class SPI1 {
	public:
		SPI1();
		~SPI1();
		int st=0;
		void begin();
		void send(char arg);
		char get();
		void sdstart();
		void sdstop();
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
class engine{
	public:
		int init();
		int start();
		int stop();
	private:
		int stat=0;
};
#endif
		
