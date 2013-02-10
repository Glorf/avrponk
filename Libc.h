#ifndef LIBC_H
#define LIBC_H
typedef char * string;
#include <avr/io.h>
#include <util/delay.h>
#include <string.h>
#include <stdlib.h>
class POS{
	private:
		int line=0;
		int position=0;
	public:
		int booted=0;
		int waitforack=0;
		void gotack();
		void boot(int baud,int background, int resolution);
		char scanf();
		string scanfp(char ending);
		void putf(string s);
		void backch(char c);
		void putfln(string s);
		void putch(char c);
		void engine(int param);
};
#endif
