#ifndef SD_H
#define SD_H
#include "CPU.h"
class SD {
	public:
		int init();
		int sendcmd(char cmd, uint32_t arg);
		int sendacmd(char cmd, uint32_t arg);
		char sect[512];
		int readsect(int sectnum); //read sect and put to char table sect
		int writesect(int sectnum); //write sect to specified sectnum
		void sdprobe();
};
#endif
