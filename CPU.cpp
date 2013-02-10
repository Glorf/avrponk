#include "CPU.h"
/*
 * USART
 */
USART1::USART1() {}
USART1::~USART1() {}
void USART1::begin(long baudrate, int turbo) {
	UBRR1H = (unsigned char)(((F_CPU/(16UL*baudrate))-1)>>8);
	UBRR1L = (unsigned char)((F_CPU/(16UL*baudrate))-1);
	if(turbo==1){
		UCSR1A = (1<<U2X1);
		UBRR1H = (unsigned char)(((F_CPU/(8UL*baudrate))-1)>>8);
		UBRR1L = (unsigned char)((F_CPU/(8UL*baudrate))-1);
	}
	UCSR1B = (1<<RXEN1)|(1<<TXEN1);
}
void USART1::send(int info){
	while ( !( UCSR1A & (1<<UDRE1)) );
   	UDR1 = info;
}
void USART1::end() {
	UCSR1A=0;
	UCSR1B=0;
	UBRR1H=0;
	UBRR1L=0;
}
void USART1::get(){
	while((UCSR1A&(1<<RXC1)) == 0);
	while(UDR1!=0x06);
}
/*
 * CPU
 */
CPU::CPU() {};
CPU::~CPU() {};
void CPU::delay(int del){
	for(int i=0;i<del;i++){
		_delay_ms(1000);
	}
}
void CPU::analogBegin() {
	DDRD=0xFF;
	ADCSRA |= (1 << ADPS2) | (1 << ADPS1) | (1 << ADPS0);
	ADMUX |= (1 << REFS0)|(1 << ADLAR);
	ADCSRA |= (1 << ADEN);
}
int CPU::analog1()
{
	ADCSRA|=(1<<ADSC);
	return ADC;
}
/*
 * SPI
 */
SPI1::SPI1(){};
SPI1::~SPI1(){};
void SPI1::begin(){
	DDRG|=_BV(SSSD); //STOR OUT
	PORTG|=_BV(SSSD);
	DDRB&=~_BV(SSETH); //ETH OUT ?in?
	DDRB&=~_BV(MISO); //MISO IN
	DDRB|=_BV(MOSI); //MOSI OUT
	DDRB|=_BV(SCK); //SCK OUT
	SPCR = (1 << SPE) | (1 << MSTR) | (1 << SPR1) | (1 << SPR0);
	DDRB|=_BV(HWSS); //CONST!
	PORTB|=_BV(HWSS);
	SPSR &= ~_BV(SPI2X); //NO 2X
};
int engine::init(){
	if(stat==0){
		DDRB|=_BV(PB5);
		stat=1;
		return 1;
	}
	else return 0;
}
int engine::start(){
	if(stat==1){
		PORTB|=_BV(PB5);
		stat=2;
		return 1;
	}
	else return 0;
}
int engine::stop(){
	if(stat==2){
		PORTB&=~_BV(PB5);
		stat=1;
		return 1;
	}
	else return 0;
}
