#include "Libc.h"
#include "CPU.h"
#include "Keyboard.h"
#include "Picaso.h"
Picaso vga;
CPU cpu;
SPI1 spi;
USART0 serial;
Keyboard kbd;
engine eng;
void POS::vgaboot(int baud,int background, int resolution)
{
	vga.up();
	vga.setBaud(baud);
	vga.clearScreen();
	vga.replaceBackground(background);
	vga.setResolution(resolution);
}
void POS::serialboot(int baud,int turbo){
	serial.begin(baud,turbo);
}
char POS::scanf()
{
	if(serialmode==0){
		return kbd.getchar();
	}
	else{
		char g=serial.get();
		if(g=='\\') return 1;
		return g;
	}
}
/*string POS::scanfp(char ending)  //NOT WORKING YET
{
	char ch;
	ch=kbd.getchar();
	while (ch!=0){
		vga.printASCIIChar(ch,position,line,0);
		position+=1;
	}
}*/
void POS::serialprint(char ch){
	serial.send(ch);
}
void POS::serialprint(string s){
	for(int i=0;i<strlen(s);i++){
		serialprint(s[i]);
	}
}
void POS::putf(string s)
{
	if(serialmode==0){
		vga.printASCIIText(s,position,line,0xFFFF);
		position+=strlen(s);
	}
	else{
		serialprint(s);
	}
}
void POS::backch(char c){
	if(serialmode==0){
		position-=1;
		vga.printASCIIChar(c,position,line,0);
	}
}
void POS::putfln(string s)
{
	if(serialmode==0){
		vga.printASCIIText(s,position,line,0xFFFF);
		position=0;
		line+=1;
	}
	else{
		serialprint(s);
		serialprint("\n");
	}
}
void POS::putch(char c){
	if(serialmode==0){
		vga.printASCIIChar(c,position,line,0xFFFF);
		position+=1;
	}
	else{
		serialprint(c);
	}
}
void POS::engine(int param){
	switch(param){
	case 1: if(eng.init()==0) putfln("Error: Already initialized"); break;
	case 2: if(eng.start()==0) putfln("Error: Already working or not initialized"); break;
	case 3: if(eng.stop()==0) putfln("Error: Already not working or not initialized"); break;
	}
}
