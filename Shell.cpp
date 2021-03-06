#include "Shell.h"
#include "Libc.h"
#include "SD.h" //TESTING
POS core;
SD sd; //TESTING
void Shell::begin() {
	if (core.booted==0) {
		if(serialmode==0){
			core.vgaboot(19200,0x00,0x01);
		}
		else{
			core.serialboot(9600,1);
		}
		core.booted+=1;
	}
	core.putfln("PonK OS 1.1.0");
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
		default: s[strlen(s)]=c; core.putch(c); break;
	}
}
void Shell::execute(){
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
			iar=0;
		}
		argv[argc-1][iar]=s[is];
		iar+=1;
		is+=1;
	}
	//APPS DEFINITIONS
	if(strcmp(main,"ponk")==0){
		if(argc>0){
			core.putf("You selected: ");
			for(int i=0;i<argc;i++){
				core.putf(argv[i]);
				core.putf(" ");
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
		uint32_t r=0;
		char w[10];
		for(int i=0;i<argc;i++){
			r=r+atoi(argv[i]);
		}
		itoa(r,w,10);
		core.putfln(w);
		memset(w,0,sizeof(w));
		r=0;
	}
	else if(strcmp(main,"pomnoz")==0){
		uint32_t r=1;
		char w[10];
		for(int i=0;i<argc;i++){
			r=r*atoi(argv[i]);
		}
		itoa(r,w,10);
		core.putfln(w);
		memset(w,0,sizeof(w));
		r=0;
	}
	else if(strcmp(main,"read")==0){
		core.putfln("SD storage read...");
		int result2=sd.readsect(512);
		switch(result2){
			case 0: core.putfln("success!"); break;
			case 1: core.putfln("first trap fail"); break;
			case 2: core.putfln("second trap fail"); break;
			default: core.putfln("unknown trap"); break;
		}
		for(int i=0;i<512;i++){
			core.putch(sd.sect[i]);
		}
	}
	else if(strcmp(main,"init")==0){
		core.putfln("SD storage initialization...");
		int result1=sd.init();
		switch(result1){
			case 0: core.putfln("success!"); break;
			case 1: core.putfln("first trap fail"); break;
			case 2: core.putfln("second trap fail"); break;
			default: core.putfln("unknown trap"); break;
		}
	}
	else if(strcmp(main,"engine")==0){
		if(argc==1){
			if(strcmp(argv[0],"init")==0){
				core.engine(1);
			}
			if(strcmp(argv[0],"start")==0){
				core.engine(2);
			}
			if(strcmp(argv[0],"stop")==0){
				core.engine(3);
			}
		}
	}
}
