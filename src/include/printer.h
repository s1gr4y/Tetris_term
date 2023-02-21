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
	
	#define Clear_Board() Printer::Windows_goto_xy(0, 0)
#else
	#include <sys/ioctl.h> //fionread
	#include <termios.h>
	#include <stdbool.h>
	
	#define Clear_Board() Printer::Linux_clear()
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
	
	#ifdef _WIN32
	static void Windows_goto_xy(short x, short y);
	#endif
	
	#ifdef __linux__
	static void Printer::Linux_clear();
	#endif
	
	#ifdef __linux__ 
	static int kbhit();
	#endif

};

#endif