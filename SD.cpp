#include "SD.h"
char SD::get(){
	char c;
	c=SPDR;
	return c;
}
void SD::send(char c){
	SPDR=c;
	while(!SPSR&_BV(SPIF));
}
void SD::start(){
	PORTG&=~_BV(PG5);
}
void SD::stop(){
	PORTG|=_BV(PG5);
}
void SD::sendcmd(char cmd, uint32_t arg, char crc){
	send(0xFF);
	send(cmd);
	send((arg>>24)&0xFF);
	send((arg>>16)&0xFF);
	send((arg>>8)&0xFF);
	send((arg>>0)&0xFF);
	send(crc);
	send(0xFF);
	send(0xFF);
	get();
}
void SD::init(){
    char i;
    stop();                    //disable CS
    for(i=0; i < 10; i++)
    send(0xFF);                // Send 10 * 8 = 80 clock pulses 400 kHz
    start();                //enable CS
    for(i=0; i < 2; i++)
    send(0xFF);
	sendcmd(0x40,0,0x95); //REBOOT
	char rez=get();
	while(rez!=0){
		sendcmd(0x41,0,0xFF);
		rez=get();
	}
	SPCR &= ~(_BV(SPR0));
}
int SD::readsect(int sectnum){
	sendcmd(0x51,0,0xFF);
	int tmp=1;
	tmp=get();
	for(uint16_t xa=0;xa<10000;xa++){
		if(tmp==0) break;
		send(0xFF);
		tmp=get();
	}
	if(tmp!=0x00) return 1;
	while(get()!=0xFE);
    for(int i=0;i<512;i++){
        sect[i]=get();
        send(0xFF);
    }
    send(0xFF);
    send(0xFF);
    return 0;
}
