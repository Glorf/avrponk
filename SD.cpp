#include "SD.h"
char SD::get(){
	char c;
	PORTG&=~_BV(PG5);
	c=SPDR;
	PORTG|=_BV(PG5);
	return c;
}
void SD::send(char c){
	PORTG&=~_BV(PG5);
	SPDR=c;
	while(!SPSR&_BV(SPIF));
	PORTG|=_BV(PG5);
}
char SD::read()
{
	send('r');
	return get();
}
