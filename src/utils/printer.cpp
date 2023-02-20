#include "../include/printer.h"

unsigned int Printer::lineCount = 0;
const char* Printer::CLEAR_SCREEN_ANSI = "\e[1;1H\e[2J";

unsigned int Printer::inc() {
	return lineCount++;
}

void Printer::ResetLineCount() {
	lineCount = 0;
}

unsigned int Printer::GetLineCount() {
	return lineCount;
}

void Printer::HideCursor() {
	printf("\33[?25l");
}

void Printer::EnableCursor() {
	printf("\33[?25h");
}

void Printer::CLR_SRC() {
	write(STDOUT_FILENO, CLEAR_SCREEN_ANSI, 12);
}




#ifdef __linux__
int Printer::kbhit() {
    static bool initflag = false;
    static const int STDIN = 0;

    if (!initflag) {
        // Use termios to turn off line buffering
        struct termios term;
        tcgetattr(STDIN, &term);
        term.c_lflag &= ~ICANON;
        tcsetattr(STDIN, TCSANOW, &term);
        setbuf(stdin, NULL);
        initflag = true;
    }

    int nbbytes;
    ioctl(STDIN, FIONREAD, &nbbytes);  // 0 is STDIN
    return nbbytes;
}
#endif