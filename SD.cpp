#include "SD.h"
char SD::get(){
	return SPDR;
}
void SD::send(char c){
	PORTG&=~_BV(PG5);
	SPDR=c;
	while(!SPSR&_BV(SPIF));
	PORTG|=_BV(PG5);
}
