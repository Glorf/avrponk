#include "Picaso.h"
Picaso::Picaso() {}
Picaso::~Picaso() {}
void Picaso::up()
{
	usart.begin(9600,0);
	usart.send(0x55);
	usart.get();
}
void Picaso::setBaud(long b){
	usart.send(0x51);
	switch(b){
		case 9600:
			usart.send(0x06);
			_delay_ms(100);
			usart.begin(9600,1);
			break;
		case 14400:
			usart.send(0x07);
			_delay_ms(100);
			usart.begin(14400,1);
			break;
		case 19200:
			usart.send(0x08);
			_delay_ms(100);
			usart.begin(19200,1);
			break;
		case 31250:
			usart.send(0x09);
			_delay_ms(100);
			usart.begin(31250,0);
			break;
		case 38400:
			usart.send(0x0A);
			_delay_ms(100);
			usart.begin(38400,0);
			usart.get();
			break;
		case 56000:
			usart.send(0x0B);
			_delay_ms(100);
			usart.begin(56000,0);
			break;
		case 57600:
			usart.send(0x0C);
			_delay_ms(100);
			usart.begin(57600,1);
			break;
		case 115200:
			usart.send(0x0D);
			_delay_ms(100);
			usart.begin(115200,0);
			break;
		case 256000:
			usart.send(0x11);
			_delay_ms(100);
			usart.begin(256000,0);
			break;
	}
}
void Picaso::clearScreen(){
	usart.send(0x45);
	usart.get();
}
void Picaso::replaceBackground(int color){
	usart.send(0x42);
	usart.send(color>>8);
	usart.send(color&0xFF);
	usart.get();
}
void Picaso::setResolution(int val){
	usart.send(0x59);
	usart.send(0x0C);
	usart.send(val);
	usart.get();
}
void Picaso::drawRectangle(int x, int y, int lx, int ly, int color){
	usart.send(0x72);
	usart.send(x>>8);
	usart.send(x&0xFF);
	usart.send(y>>8);
	usart.send(y&0xFF);
	usart.send(lx>>8);
	usart.send(lx&0xFF);
	usart.send(ly>>8);
	usart.send(ly&0xFF);
	usart.send(color>>8);
	usart.send(color&0xFF);
	usart.get();
}
void Picaso::printASCIIChar(int ch, int column, int row, int color){
	usart.send(0x54);
	usart.send(ch);
	usart.send(column);
	usart.send(row);
	usart.send(color>>8);
	usart.send(color&0xFF);
	usart.get();
}
void Picaso::printASCIIText(string ch,int column,int row, int color){
	for(int i=0;i<strlen(ch);i++)
	{
		usart.send(0x54);
		usart.send(ch[i]);
		usart.send(column+i);
		usart.send(row);
		usart.send(color>>8);
		usart.send(color&0xFF);
		usart.get();
	}
}
