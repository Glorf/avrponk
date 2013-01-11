#ifndef SD_H
#define SD_H
#include "CPU.h"
class SD {
	public:
		char get();
		void send(char c);
		char read();
		void write(char c);
};
#endif
