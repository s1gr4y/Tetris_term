#ifndef PRINTER_H
#define PRINTER_H

#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>

#include <iostream>
#include <string>

#ifdef _WIN32	
	#include <Windows.h>
	#include <conio.h>
	#define kbhit() _kbhit()
	
	#define getCharInp() _getch()
	//#define sleep(val) Sleep(val)
#else
	#include <sys/ioctl.h> //fionread
	#include <termios.h>
	#include <stdbool.h>
	
	#define getCharInp() getChar()
#endif

using namespace std;


class Printer {
	
	static unsigned int lineCount;
	static const char *CLEAR_SCREEN_ANSI;

public:
	static unsigned int inc();
	static void ResetLineCount();
	static unsigned int GetLineCount();
	
	static void HideCursor();
	static void EnableCursor();
	static void CLR_SRC();
	
	
	
	#ifdef __linux__ 
	static int kbhit();
	#endif

};

#endif