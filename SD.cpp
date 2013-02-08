#include "SD.h"
char status;
void SD::send(char c){
	SPDR = c;
	while (!(SPSR & (1 << SPIF)));
}
char SD::get(){
	send(0XFF);
	return SPDR;
}
void SD::start(){
	PORTG&=~_BV(SSSD);
}
void SD::stop(){
	PORTG|=_BV(SSSD);
}
#define CMD0 0x00
#define CMD8 0x08
#define CMD17 0x11
#define CMD55 0x37
#define ACMD41 0x29
int SD::sendcmd(char cmd, uint32_t arg){
	start();
	send(cmd | 0x40);
	for (int8_t s = 24; s >= 0; s -= 8) send(arg >> s);
	uint8_t crc = 0xFF;
	if (cmd == 0x00) crc = 0X95;  // correct crc for CMD0 with arg 0
	if (cmd == 0x08) crc = 0X87;  // correct crc for CMD8 with arg 0X1AA
	send(crc);
	for (int i=0;(status=get()&0X80)&&(i!=0XFF);i++);
	stop();
	return status;
}
int SD::sendacmd(char cmd, uint32_t arg){
	sendcmd(CMD55, 0);
	return sendcmd(cmd,arg);
}
void SD::sdprobe(){
	stop();
	for (uint8_t i = 0; i < 10; i++) send(0XFF);
	start();
	for(int i=0;i<512;i++){
		sect[i]=sendcmd(CMD0, 0)+'0';
	}
}
int SD::init(){
    stop();
    for (uint8_t i = 0; i < 20; i++) send(0xFF);
    start();
    while ((status=sendcmd(CMD0, 0)) != 0x01);
    //while ((status=sendacmd(ACMD41,0))!=0x00);
}
int SD::readsect(int sectnum){
    int i;
    uint16_t ix;
    char r1 =  sendcmd(CMD17,0);
    for (ix = 0; ix < 50000; ix++) {
        if (r1 == (char)0x00) break;
        r1 = get();
    }
    if (r1 != (char)0x00) {
    return 1;
    }
    //read from the card will start after the framework
    while(get() != (char)0xFE);
    for(i=0; i < 512; i++) {
        while(!(SPSR & (1<<SPIF)));
        sect[i] = SPDR;
        SPDR = get();
    }
    send(0xFF);
    send(0xFF);
    return 0;
}
