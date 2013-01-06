#ifndef PICASO_H
#define PICASO_H
#include "CPU.h"
class Picaso {
	private:
		void send(int info);
		void getack();
	public:
		USART1 usart;
		Picaso();
		~Picaso();
		void up();
		void setBaud(long b);
		void clearScreen();
		void replaceBackground(int color);
		void drawCircle(int x,int y, int radius, int color);
		void setFont(int val);
		void setResolution(int val);
		void drawRectangle(int x, int y, int lx, int ly, int color);
		void printASCIIChar(int ch, int column, int row, int color);
		void printASCIIText(string ch,int column,int row, int color);
};
#endif
