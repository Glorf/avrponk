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
char SD::sendcmd(char cmd, uint32_t arg, char crc){
	PORTG&=~_BV(PG5);
	send(0xFF);
	send(cmd);
	send(arg>>24);
	send(arg>>16);
	send(arg>>8);
	send(arg);
	send(crc);
	send(0xFF);
	send(0xFF);
	return get();
	PORTG|=_BV(PG5);
}
void SD::init(){
	sendcmd(0x40,0,0x95); //REBOOT
	char rez=1;
	while(rez!=0){
		sendcmd(0x41,0,0xFF);
		rez=get();
	}
}
int SD::readsect(int sectnum){
	sendcmd(0x51,512*sectnum,0xFF);
	char tmp;
	tmp=get();
	for(uint16_t xa;xa<1000;xa++){
		if(tmp==0x00) break;
		send(0xFF);
		tmp=get();
	}
	if(tmp!=0x00) return 1;
	tmp=0;
	for(uint16_t xb;xb<1000;xb++){
		if(tmp==0xFE) break;
		send(0xFF);
		tmp=get();
	}
    for(int i=0;i<512;i++){
        while(!(SPSR&_BV(SPIF)));
        sect[i]=SPDR;
        send(0xFF);
        SPDR=get();
    }
    send(0xFF);
    send(0xFF);
    return 0;
}
