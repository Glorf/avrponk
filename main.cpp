#include "Shell.h"
Shell sh;
int main(void) {
	//cpu.analogBegin();
	sh.begin();
	char c;
	while(true){
		c=sh.scan();
		if(c!=0){
			sh.update(c);
		}
	}
}
