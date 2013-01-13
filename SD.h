#ifndef SD_H
#define SD_H
#include "CPU.h"
class SD {
	public:
		char get();
		void send(char c);
		//usable from here! up, only internal values
		void init();
		char sendcmd(char cmd, uint32_t arg, char crc);
		char sect[512];
		int readsect(int sectnum); //read sect and put to char table sect
		int writesect(int sectnum); //write sect to specified sectnum
};
#endif
