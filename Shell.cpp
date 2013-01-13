#include "Shell.h"
#include "Libc.h"
#include "SD.h" //TESTING
POS core;
SD sd; //TESTING
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
char s[50];
void Shell::update(char c) {
	switch(c){
		case 0: break;
		case 1:
			core.putfln("");
			execute();
			core.putf(">");
			for(int i=0;i<50;i++){
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
void Shell::execute(){
	/*
	 * THIS CODE IS NOT WORKING AT ALL!
	 */
	char argv[10][10];
	memset(argv,0,sizeof(argv));
	char main[10];
	memset(main,0,sizeof(main));
	int argc=0;
	int is=0;
	while(is<strlen(s)){
		if(s[is]==' '){
			if(is+1==strlen(s)){
				is+=1;
				break;
			}
			argc+=1;
			is+=1;
			break;
		}
		main[is]=s[is];
		is+=1;
	}
	while(s[is]==' ') is+=1;
	int iar=0;
	while(is<strlen(s)){
		if(s[is]==' '){
			argc+=1;
			is+=1;
		}
		argv[argc-1][iar]=s[is];
		iar+=1;
		is+=1;
	}
	//APPS DEFINITIONS
	if(strcmp(main,"ponk")==0){
		if(argc>0){
			core.putf("You selected: ");
			for(int i=0;i<=argc;i++){
				core.putfln((string)argv[i]);
			}
			core.putfln("");
		}
		core.putfln("   #####    ");
		core.putfln("  #     #   ");
		core.putfln(" #   ##  #  ");
		core.putfln("  # #   #    PonK Industries product! ");
		core.putfln("   #####    ");
		core.putfln("     #     ");
		core.putfln("      #    ");
		core.putfln("    ##     ");
	}
	else if(strcmp(main,"dodaj")==0){
		int r=(int)argv[0]+(int)argv[1];
		core.putf((string)r);
	}
	else if(strcmp(main,"read")==0){
		sd.readsect(1);
		for(int i=0;i<20;i++){
			core.putch(sd.sect[i]);
		}
	}
}
