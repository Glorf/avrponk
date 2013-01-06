#include "Libc.h"
#include "CPU.h"
#include "Keyboard.h"
#include "Picaso.h"
Picaso vga;
CPU cpu;
Keyboard kbd;
void POS::boot(int baud,int background, int resolution)
{
	vga.up();
	vga.setBaud(baud);
	vga.clearScreen();
	vga.replaceBackground(0xFFFF); //dev
	vga.setResolution(0x01);
}
char POS::scanf()
{
	return kbd.getchar();
}
string POS::scanfp(char ending)  //NOT WORKING YET
{
	char ch;
	ch=kbd.getchar();
	while (ch!=0){
		vga.printASCIIChar(ch,position,line,0);
		position+=1;
	}
}
void POS::putf(string s)
{
	vga.printASCIIText(s,position,line,0xFFFF);
	position+=strlen(s);
}
void POS::backch(char c){
	position-=1;
	vga.printASCIIChar(c,position,line,0);
}
void POS::putfln(string s)
{
	vga.printASCIIText(s,position,line,0xFFFF);
	position=0;
	line+=1;
}
void POS::putch(char c){
	vga.printASCIIChar(c,position,line,0xFFFF);
	position+=1;
}
