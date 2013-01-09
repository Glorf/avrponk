#ifndef SD_H
#define SD_H
#include "CPU.h"
class SD {
	public:
		void start();
		void stop();
		char get();
		void send(char c);
};
#endif
