#ifndef ENGINE_H
#define ENGINE_H

#include <time.h>
#include <chrono>
#include <thread>

#include "printer.h"
#include "block.h"
#include "constants.h"

#ifdef _WIN32	
	#define getKey() _kbhit()
	#define getCharInp() _getch()
#else
	#define getCharInp() getchar()
	#define getKey() Printer::kbhit()
#endif

using namespace UniversalVars;
using namespace std;
using namespace chrono;

class Engine {
	
	int rowCount = 12;
	int colCount = 12;
	
	double dt = 0.f;
	double totalTime = 0.f;
	
	long int tick;
	double tick_float;
	
	//clock_t start_clk;
	//clock_t end_clk;
	
	steady_clock::time_point start_clk;
	steady_clock::time_point end_clk;
	
	char** board = NULL;
	
	long int InvokeDownMoveTick = 0;
	long int Score = 0;
	
	Block *blockList[7];
	
	Block *currBlock;
	Block *nextBlock;
	
	char prevInput;
	char currInput;
	
public:
	Engine();
	Engine(int rows, int cols);
	~Engine();
	
	void InitGame();
	void GameLoop();
	void PrintBoard();
	void PrintStatus(bool flip);
	void PrintStatusHelper(int row);
	
	//logic checks
	void ShiftDownRow(int rowIndex);
	bool IsIntersecting();
	bool IsValidMove(int off_c);
	bool CanMoveDown();
	bool BlockMoveDownOne();
	void GetNextBlock();
	bool CanRotateBlock(bool flip);
	bool WallKickRotate(char lastInp);
	int RowCleared();	//if -1, then no row is filled.

	bool SpawnBlock();
	
	void WriteBoard();
	bool FrameAction(long int tickTime);
	
};

#endif