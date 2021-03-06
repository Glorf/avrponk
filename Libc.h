#ifndef LIBC_H
#define LIBC_H
typedef char * string;
#define serialmode 1  //FIRST CONFIGURATION VARIABLE
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
		void vgaboot(int baud,int background, int resolution);
		void serialboot(int baud,int turbo);
		char scanf();
		string scanfp(char ending);
		void putf(string s);
		void backch(char c);
		void putfln(string s);
		void putch(char c);
		void engine(int param);
		void serialprint(string s);
		void serialprint(char ch);
};
#endif
