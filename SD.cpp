#include "SD.h"
void SD::send(char c){
	SPDR=c;
	while(!SPSR&_BV(SPIF));
}
char SD::get(){
	send(0xFF);
	while(!SPSR&_BV(SPIF));
	return SPDR;
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
	send(0x00); //hum
	send(0x00); //hum
	send(arg>>8); //hum
	send(arg);
	send(crc);
	send(0xFF);
	get();
}
void SD::init(){
    char i;
    stop();                    //disable CS
    for(i=0; i < 10; i++)
    {
    	get();
    }// Send 10 * 8 = 80 clock pulses 400 kHz
    start();                //enable CS
	sendcmd(0x40,0,0x95); //REBOOT
	char g=99;
	sendcmd(0x41,0,0xFF);
	g=get();
	while(g!=0){
		sendcmd(0x41,0,0xFF);
		g=get();
	}
	SPCR &= ~(_BV(SPR0));
}
int SD::readsect(int sectnum){
	sendcmd(0x51,512,0xFF);
	int tmp=1;
	tmp=get();
	for(uint16_t xa=0;xa<10000;xa++){
		if(tmp==0) break;
		send(0xFF);
		tmp=get();
	}
	if(tmp!=0x00) return 1;
	char yourget=0;
	while(yourget!=0xFE) yourget=get();
    for(int i=0;i<512;i++){
        sect[i]=get();
        send(0xFF);
    }
    send(0xFF);
    send(0xFF);
    return 0;
}
