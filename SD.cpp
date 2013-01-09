#include "SD.h"
void SD::start(){
	PORTG|=_BV(PG5);
}
void SD::stop(){
	PORTG&=~_BV(PG5);
}
char SD::get(){
	return SPDR;
}
void SD::send(char c){
	SPDR=c;
}
