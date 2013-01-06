#include "Keyboard.h"
Keyboard::Keyboard() {};
Keyboard::~Keyboard() {};
int Keyboard::waitforhigh(){
	uint8_t attempt = 0;
		for(attempt=0; attempt<12; attempt++) {
			_delay_us(10);
	  		if(bit_is_set(PINA,PA0)) {
	  				return 1;
	  		}
	  		attempt+=1;
	  }
		return 0;
}
int Keyboard::waitforlow(){
	uint8_t attempt = 0;
	for(attempt=0; attempt<12; attempt++) {
		_delay_us(10);
	    if(bit_is_clear(PINA,PA0)) {
	    	return 1;
	    }
	    attempt+=1;
	}
	return 0;
}
int data;
int par;
int ackpar;
int i;
int Keyboard::getscan(){
	DDRA&=~_BV(PA0);
	DDRA&=~_BV(PA1);
	PORTA|=_BV(PA0);
	PORTA|=_BV(PA1);
	data=0;
	par=0;
	ackpar=0;
	if(bit_is_clear(PINA,PA0)&&bit_is_clear(PINA,PA1)){
		for(i=0;i<8;i++){
			data = data >> 1;
			waitforhigh();
			waitforlow();
			if(bit_is_clear(PINA,PA1)){
			}
			if(bit_is_set(PINA,PA1)){
				data|=128;
			}
		}
		waitforhigh();
		waitforlow();
		if(bit_is_set(PINA,PA1)){
			ackpar=1;
		}
		waitforhigh();
		waitforlow();
		if(bit_is_clear(PINA,PA1)){
			return 0;
		}
		return data;
		DDRA|=_BV(PA0);
		DDRA|=_BV(PA1);
		PORTA&=~_BV(PA0);
		PORTA&=~_BV(PA1);
	}
	return 0;
}
char c;
int tmp=0;
char Keyboard::makefriendlychar(){
	c=getscan();
	if(tmp==1){
		_delay_ms(5);
		c=getscan();
		if(c!=0xF0){
			tmp=0;
			return 0;
		}
	}
	switch(c){
	case 0x1C: return 'a';
	case 0x32: return 'b';
    case 0x21: return 'c';
    case 0x23: return 'd';
    case 0x24: return 'e';
    case 0x2B: return 'f';
    case 0x34: return 'g';
    case 0x33: return 'h';
    case 0x43: return 'i';
    case 0x3B: return 'j';
    case 0x42: return 'k';
    case 0x4B: return 'l';
    case 0x3A: return 'm';
    case 0x31: return 'n';
    case 0x44: return 'o';
    case 0x4D: return 'p';
    case 0x15: return 'q';
    case 0x2D: return 'r';
    case 0x1B: return 's';
    case 0x2C: return 't';
    case 0x3C: return 'u';
    case 0x2A: return 'v';
    case 0x1D: return 'w';
    case 0x22: return 'x';
    case 0x35: return 'y';
    case 0x1A: return 'z';
    case 0x29: return ' ';
    case 0x45: return '0';
    case 0x16: return '1';
    case 0x1E: return '2';
    case 0x26: return '3';
    case 0x25: return '4';
    case 0x2E: return '5';
    case 0x36: return '6';
    case 0x3D: return '7';
    case 0x3E: return '8';
    case 0x46: return '9';
    case 0x0E: return '\'';
    case 0x4E: return '-';
    case 0x55: return '=';
    case 0x5D: return '\\';
    case 0xF0: tmp=1; return 0; //????
    case 0x5A: return 1;
    case 0x66: return 2;
    default: return 0; //test
	}
}
int Keyboard::sendset(unsigned char c){

}
char Keyboard::getchar(){
	return makefriendlychar();
}
int Keyboard::setopt(int opt){

}
