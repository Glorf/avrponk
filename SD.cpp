#include "SD.h"
#include "CPU.h"
SPI1 spi1;
char status;
#define CMD0 0x00
#define CMD8 0x08
#define CMD17 0x11
#define CMD55 0x37
#define ACMD41 0x29
int SD::sendcmd(char cmd, uint32_t arg){
	spi1.sdstart();
	spi1.send(cmd | 0x40);
	for (int8_t s = 24; s >= 0; s -= 8) spi1.send(arg >> s);
	uint8_t crc = 0xFF;
	if (cmd == 0x00) crc = 0X95;  // correct crc for CMD0 with arg 0
	if (cmd == 0x08) crc = 0X87;  // correct crc for CMD8 with arg 0X1AA
	spi1.send(crc);
	for (int i=0;(status=spi1.get()&0X80)&&(i!=0XFF);i++);
	spi1.sdstop();
	return status;
}
int SD::sendacmd(char cmd, uint32_t arg){
	sendcmd(CMD55, 0);
	return sendcmd(cmd,arg);
}
void SD::sdprobe(){
	spi1.sdstop();
	for (uint8_t i = 0; i < 10; i++) spi1.send(0XFF);
	spi1.sdstart();
	for(int i=0;i<512;i++){
		sect[i]=sendcmd(CMD0, 0)+'0';
	}
}
int SD::init(){
	if (spi1.st==0){
		spi1.begin();
	}
    spi1.sdstop();
    for (uint8_t i = 0; i < 10; i++) spi1.send(0xFF);
    spi1.sdstart();
    while ((status=sendcmd(CMD0, 0)) != 0x01);
    while ((status=sendacmd(ACMD41,0))!=0x00);
}
int SD::readsect(int sectnum){
    int i;
    uint16_t ix;
    char r1 =  sendcmd(CMD17,0);
    for (ix = 0; ix < 50000; ix++) {
        if (r1 == (char)0x00) break;
        r1 = spi1.get();
    }
    if (r1 != (char)0x00) {
    return 1;
    }
    //read from the card will start after the framework
    while(spi1.get() != (char)0xFE);
    for(i=0; i < 512; i++) {
        while(!(SPSR & (1<<SPIF)));
        sect[i] = SPDR;
        SPDR = spi1.get();
    }
    spi1.send(0xFF);
    spi1.send(0xFF);
    return 0;
}
