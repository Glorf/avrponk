#include "Shell.h"
#include "Libc.h"
POS core;
void Shell::begin() {
	if (core.booted==0) {
		core.boot(19200,0xFF,0x01);
		core.booted+=1;
	}
	core.putfln("PonK OS 1.0");
	core.putfln("PonK Industries Polska");
	core.putf(">");
}
char Shell::scan(){
	return core.scanf();
}
char s[20];
void Shell::update(char c) {
	switch(c){
		case 0: break;
		case 1:
			core.putfln("");
			core.putfln(s);
			execute(s);
			core.putf(">");
			for(int i=0;i<20;i++){
				s[i]=0;
			}
			break;
		case 2:
			core.backch(s[strlen(s)-1]);
			s[strlen(s)-1]=0;
			break;
		default: s[strlen(s)]=c; core.putch(c); break; //impl!
	}
}
void Shell::execute(string cmd){
	if(strcmp(cmd,"ponk")==0){
		core.putfln("    ###    ");
		core.putfln("   #####   ");
		core.putfln("  #######  ");
		core.putfln("   #####    PonK Industries product! ");
		core.putfln("    ###    ");
		core.putfln("     #     ");
		core.putfln("     #     ");
		core.putfln("     #     ");
	}
	else if(strcmp(cmd,"kalkulator")==0){

	}
}
