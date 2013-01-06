#ifndef KEYBOARD_H
#define KEYBOARD_H
#include "CPU.h"
class Keyboard {
	private:
		int getscan();
		char makefriendlychar();
		int sendset(unsigned char c);
	public:
		int waitforlow(); //do private!
		int waitforhigh(); //to też!
		Keyboard();
		~Keyboard();
		char getchar();
		int setopt(int opt);
};
#endif
