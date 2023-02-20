#include "../include/engine.h"


Engine::Engine() {}

Engine::Engine(int rows, int cols) {
	rowCount = rows;
	colCount = cols;
	cout << rowCount << " || " << colCount << endl;
	board = new char*[rowCount];
	for (int i = 0; i < rowCount; i++) {
		board[i] = new char[colCount];
		memset(board[i], ' ', sizeof(char) * colCount);	//95 == '_'
	}
		
	InitGame();
}

Engine::~Engine() {
	for (int i = 0; i < rowCount; i++) {
		delete[] board[i];
	}
	delete[] board;
	
	for (int i = 0; i < 7; i++) {
		delete blockList[i];
	}
	
}

void Engine::InitGame() {
	srand (time(NULL));
	
	//blockList = new Block[7];
	
	//best to just make the object then assign since elision
	//can occur with the copy-initializer not getting copying right
	
	//actually objects fall out of scope and die, so we lose the pointers.
	//need to make dynamic
	
	//Block tmp0 = Block(arrI, 4, false);
	//blockList[0] = tmp0;
	blockList[0] = new Block(arrI, 4, false, 0);
	
	//Block tmp1(arrL, 3, true);
	//blockList[1] = tmp1;
	blockList[1] = new Block(arrL, 3, true, 1);
	
						
	//Block tmp2 = Block(arrJ, 3, true);
	//blockList[2] = tmp2;
	blockList[2] = new Block(arrJ, 3, true, 2);
	
						
	//Block tmp3 = Block(arrZ, 3, false);
	//blockList[3] = tmp3;
	blockList[3] = new Block(arrZ, 3, false, 3);
	
	
	//Block tmp4 = Block(arrS, 3, false);
	//blockList[4] = tmp4;
	blockList[4] = new Block(arrS, 3, false, 4);
	
	//Block tmp5(arrT, 3, true);
	//blockList[5] = tmp5;
	blockList[5] = new Block(arrT, 3, true, 5);

						
	//Block tmp6(arrO, 2, true);
	//blockList[6] = tmp6;
	blockList[6] = new Block(arrO, 2, true, 6);
	
	//currBlock = (blockList[0]);
	currBlock = (blockList[rand() % 7]);
	nextBlock = (blockList[rand() % 7]);
	SpawnBlock();
	//nextBlock->blkReset();
	//cout << "what it should be " << blockList[6]->mat[0][0] << endl;
	//cout << "what it is " << currBlock->mat[0][0] << endl;
}

void Engine::GetNextBlock() {
	currBlock = nextBlock;
	currBlock->blkReset();
	int index = rand() % 8;
	//cout << "got index " << index << endl;
	nextBlock = blockList[index];
	//cout << "first val of currblk: " << currBlock->mat[0][0] << endl;
	//cout << "first val of nextBlock: " << nextBlock->mat[0][0] << endl;
}

void Engine::GameLoop() {
	Printer::HideCursor();
	Printer::CLR_SRC();
	
	start_clk = clock();
	end_clk = clock();
	
	//board[0][0] = 'X';
	/*
	cout << "hi" << endl;
	cout << "__first val of currblk: " << currBlock->mat[0][0] << endl;
	cout << "is it valid? " << !CanRotateBlock(true) << endl;
	for (int i = 0; i < currBlock->rows; i++) {
		cout << "i " << currBlock->rows << endl;
		for (int j = 0; j < currBlock->cols; j++) {
			cout << currBlock->mat[i][j];
		}
		cout << endl;
	}
	return;
	*/
	char c = 0;
	while (1) {
		end_clk = clock();
		double seconds = (double)(end_clk - start_clk) / CLOCKS_PER_SEC;
		
		start_clk = clock();
		
		dt = seconds;
		totalTime += dt;
		
		tick_float += dt * TICK_RATE;
		tick = (long int)tick_float;
		
		if (c != 0 && c == 'M' || c == 'K') {	//c != 0 is unnecessary
			prevInput = c;
		}
		c = 0;
		if (kbhit()) {
			c = getCharInp();
		}
		if (c == 'q' || c == 27) {	//q or esc
			Printer::CLR_SRC();
			Printer::ResetLineCount();
			break;
		}
		currInput = c;
		switch (c) {
		case 'H':	//up arrow somehow?
			if (!CanRotateBlock(true)) {	//rotate left
				//currBlock->rotateRight();
			}
			break;
		case 'P':	//down
			if (!BlockMoveDownOne()) {
				if (SpawnBlock()) {
					goto END;
				}
			}
			break;
		case 'K':	//left
			if (IsValidMove(-1)) {
				currBlock->c -= 1;
			}
			break;
		case 'M':	//right
			if (IsValidMove(1)) {
				currBlock->c += 1;
			}
			break;
		case 'r':	//rotate right
			if (!CanRotateBlock(false)) {	//rotate left
				//currBlock->rotateLeft();
			}
			break;
		case ' ':	//hard drop need to implement
			{
			for (int i = 0; i < rowCount; i++) {	//a bit hard to read might change
				if (!BlockMoveDownOne()) {
					SpawnBlock();
					break;
				}
			}
			break;
			}
		}
		
		printf("%d\tPlaying TETRIS\n", Printer::inc());
		printf("%d\tCONTROLS [ ESC/q: to quit, r/up: to rotate, left: move block left, right: move block right ]\n", Printer::inc());
		printf("%d\tCurrent tick: %d\n", Printer::inc(), tick);
		printf("%d\tTime since last loop: %f\n", Printer::inc(), seconds);
		printf("%d\tTime since starting the program: %f\n", Printer::inc(), totalTime);
		printf("%d\tRead in %c\n", Printer::inc(), c);
		
		//printf("                                     \r");	//printf("\33[2K");	//clearing line for coords //or use printf("\r\t\t\t\t\t\t\t");
		//printf("%d\tCurrent BLK coords %d, %d\n", Printer::inc(), currBlock->r, currBlock->c);
		printf("%d\tScore: %li\n", Printer::inc(), Score);
		printf("%d\tNext BLK is %d\n", Printer::inc(), currBlock->index);
		///*
		if (FrameAction(66l)) {
			if (!BlockMoveDownOne()) {
				if (SpawnBlock()) {
					goto END;
				}
			}
		}
		//*/
		PrintBoard();


		string formater = "";
		for (int i = 0; i < Printer::GetLineCount(); i++) {
			formater += "\033[F";
		}
		
		printf("%s", formater.c_str());
		//Printer::CLR_SRC();	//bc if we have extra lines from last frame we don't clear it.
		Printer::ResetLineCount();
		PrintStatus(true);	//fliping print state
	}
	
END:
	Printer::CLR_SRC();
	Printer::EnableCursor();
}

void Engine::PrintBoard() {
	printf("%d\t#", Printer::inc());
	for (int j = 0; j < colCount; j++) {
		printf("#");
	}
	printf("#\n");
	
	for (int i = 0; i < rowCount; i++) {
		printf("%d\t#", Printer::inc());
		//printf("rowcount, colCount %d %d", rowCount, colCount);
		if (currBlock->r + currBlock->rows > i && currBlock->r <= i) {
			for (int j = 0; j < colCount; j++) {
				if (currBlock->c + currBlock->cols > j && currBlock->c <= j) {
					//cout << "val at curr blk 0 0 is " << currBlock->mat[0][0] << endl;
					//cout << "r: " << i - currBlock->r << " | c: " << j - currBlock->c << endl;
					//return;
					//printf("rowcount, colCount %d %d", rowCount, colCount);
					//printf(" val at board is %c", board[i][j]);
					if (currBlock->mat[i - currBlock->r][j - currBlock->c] != 32) {
						printf("%c", currBlock->mat[i - currBlock->r][j - currBlock->c]);
					} else {
						printf("%c", board[i][j]);
					}
				} else {
					printf("%c", board[i][j]);
				}
			}
		} else {
			for (int j = 0; j < colCount; j++) {
				printf("%c", board[i][j]);
			}
		}
		printf("#");	//"#\n"
		PrintStatus(false);
	}
	
	printf("%d\t#", Printer::inc());
	for (int j = 0; j < colCount; j++) {
		printf("#");
	}
	printf("#\n");
}

void Engine::PrintStatus(bool flip) {
	static int lineCount = 0;
	static int row = 0;
	static bool done = false;
	
	if (flip) {
		done = false;
		lineCount = 0;
		row = 0;
		return;
	} else if (done) {
		printf("\n");
		return;
	} else {	//otherwise start printing
		const int limit = 4;	//nextBlock->rows + 1;
		if (lineCount == 0) {
			printf("\tNext Tetromino\n");
		} else if (lineCount == 1) {
			printf("\t######\n");
		} else if (lineCount >= nextBlock->rows + 2 && lineCount <= limit) {
			printf("\t#    #\n");
		} else if (lineCount > limit) {
			printf("\t######\n");
			lineCount = 0;
			row = 0;
			done = true;
		} else {
			printf("\t#");
			PrintStatusHelper(row);
			if (nextBlock->rows == 2) {
				printf("  ");
			} else if (nextBlock->rows == 3) {
				printf(" ");
			}
			printf("#\n");
			row++;
		}
		
		lineCount++;
	}
}

void Engine::PrintStatusHelper(int row) {
	if (nextBlock->index == 0) {
		for (int i = 0; i < nextBlock->cols; i++) {
			printf("%c", arrI[row][i]);
		}
	} else if (nextBlock->index == 1) {
		for (int i = 0; i < nextBlock->cols; i++) {
			printf("%c", arrL[row][i]);
		}
	} else if (nextBlock->index == 2) {
		for (int i = 0; i < nextBlock->cols; i++) {
			printf("%c", arrJ[row][i]);
		}
	} else if (nextBlock->index == 3) {
		for (int i = 0; i < nextBlock->cols; i++) {
			printf("%c", arrZ[row][i]);
		}
	} else if (nextBlock->index == 4) {
		for (int i = 0; i < nextBlock->cols; i++) {
			printf("%c", arrS[row][i]);
		}
	} else if (nextBlock->index == 5) {
		for (int i = 0; i < nextBlock->cols; i++) {
			printf("%c", arrT[row][i]);
		}
	} else if (nextBlock->index == 6) {
		for (int i = 0; i < nextBlock->cols; i++) {
			printf("%c", arrO[row][i]);
		}
	}
}

void Engine::ShiftDownRow(int rowIndex) {
	char* rowHolder = board[rowIndex];
	int i = rowIndex;
	for (; i > 0; i--) {	//shift all rows down one by switching mem blocks
		board[i] = board[i-1];
	}
	board[i] = rowHolder; 
	//printf("%d\tSetting row %d\n", Printer::inc(), i);
	memset(rowHolder, ' ', sizeof(char) * colCount);	//memset first row to nothing
}

bool Engine::IsIntersecting() {
	int r = currBlock->r;
	int c = currBlock->c;
	
	for (int i = 0; i < currBlock->rows; i++) {
		for (int j = 0; j < currBlock->cols; j++) {
			if (i+r >= rowCount || j+c >= colCount || i+r < 0 || j+c < 0) {
				if (currBlock->mat[i][j] > 32) {
					return true;
				}
				continue;
			} else if (currBlock->mat[i][j] > 32 && board[i+r][j+c] > 32) {
				return true;
			}
		}
	}
	return false;
}

bool Engine::IsValidMove(int off_c) {
	int r = currBlock->r;
	int c = currBlock->c + off_c;
	
	for (int i = 0; i < currBlock->rows; i++) {
		for (int j = 0; j < currBlock->cols; j++) {
			if (i+r >= rowCount || j+c >= colCount || i+r < 0 || j+c < 0) {
				if (currBlock->mat[i][j] > 32) {
					return false;
				}
				continue;
			} else if (currBlock->mat[i][j] > 32 && board[i+r][j+c] > 32) {
				return false;
			}
		}
	}
	return true;
}

bool Engine::CanMoveDown() {
	int r = currBlock->r + 1;
	int c = currBlock->c;
	
	for (int i = 0; i < currBlock->rows; i++) {
		for (int j = 0; j < currBlock->cols; j++) {
			if (i+r >= rowCount || j+c >= colCount || i+r < 0 || j+c < 0) {
				if (currBlock->mat[i][j] > 32) {
					return false;
				}
				continue;
			} else if (currBlock->mat[i][j] > 32 && board[i+r][j+c] > 32) {
				return false;
			}
		}
	}
	return true;
}

bool Engine::BlockMoveDownOne() {
	int counter = 0;
	if (!CanMoveDown()) {
		WriteBoard();
	chain:
		int row = RowCleared();
		if (row >= 0) {
			counter++;
			ShiftDownRow(row);
			goto chain;	//could also do loop here with seek index to check for more clears
		}
		if (counter == 1) {
			Score += 100;
		} else if (counter == 2) {
			Score += 300;
		} else if (counter >= 3) {
			Score += counter * 150;
		}
		return false;
	} else {
		currBlock->r += 1;
		return true;
	}
}

bool Engine::CanRotateBlock(bool flip) {
	if (!currBlock->flipAble && currBlock->alternator) {	//false, force right
		currBlock->rotateRight();
		if (IsIntersecting()) {
			if (WallKickRotate(prevInput)) {
				currBlock->alternator = !currBlock->alternator;
				return true;
			}
			currBlock->rotateLeft();
			return false;
		}
		currBlock->alternator = !currBlock->alternator;
		return true;
	} else if (!currBlock->flipAble && !currBlock->alternator) {	//false, force right
		currBlock->rotateLeft();
		if (IsIntersecting()) {
			if (WallKickRotate(prevInput)) {
				currBlock->alternator = !currBlock->alternator;
				return true;
			}
			currBlock->rotateRight();
			return false;
		}
		currBlock->alternator = !currBlock->alternator;
		return true;
	}
	
	
	if (flip) {	//rotate left
		currBlock->rotateLeft();
		if (IsIntersecting()) {
			if (WallKickRotate(prevInput)) {
				return true;
			}
			currBlock->rotateRight();
			return false;
		}
	} else {
		currBlock->rotateRight();
		if (IsIntersecting()) {
			if (WallKickRotate(prevInput)) {
				return true;
			}
			currBlock->rotateLeft();
			return false;
		}
	}
	return true;
}

bool Engine::WallKickRotate(char lastInp) {
	if (IsValidMove(1) && IsValidMove(-1)) {
		if (lastInp == 'K') {
			currBlock->c -= 1;
		} else {	//or 'M' but we default right if neither is chosen
			currBlock->c += 1;
		}
	} else if (IsValidMove(1)) {
		currBlock->c += 1;
	} else if (IsValidMove(-1)) {
		currBlock->c -= 1;
	} else {
		return false;
	}
	return true;
}

int Engine::RowCleared() {
	for (int i = rowCount-1; i >= 0; i--) {
		int counter = 0;
		for (int j = 0; j < colCount; j++) {
			if (board[i][j] != 32) {
				counter++;
			} else {
				counter = 0;
				break;
			}
		}
		if (counter >= colCount) {
			return i;
		}
	}
	return -1;
}

bool Engine::SpawnBlock() {
	currBlock->blkReset();	//reset it.
	GetNextBlock();
	if (currBlock->rows == 2) {
		//currBlock->r = 0;
		currBlock->c = colCount/2 - 1;
	} else if (currBlock->rows == 3) {
		currBlock->c = colCount/2 - 1;
	} else {
		currBlock->c = colCount/2 - 2;
	}
	//cout << "here?" << endl;
	return IsIntersecting();
}


void Engine::WriteBoard() {
	int r = currBlock->r;
	int c = currBlock->c;
	
	for (int i = 0; i < currBlock->rows; i++) {
		for (int j = 0; j < currBlock->cols; j++) {
			if (i+r >= rowCount || j+c >= colCount || i+r < 0 || j+c < 0) {
				continue;
			} else {
				if (board[i+r][j+c] <= 32) {
					board[i+r][j+c] = currBlock->mat[i][j];
				}
			}
		}
	}
}

/*
void Engine::DrawCurrBlock() {
	string formater = "";
	for (int i = 0; i < rowCount; i++) {	//run back to top
		formater += "\033[F";
	}
	printf("%s", formater.c_str());
	
	formater = "";
	
	int r = currBlock->r;
	int c = currBlock->c;
	
	for (int i = 0; i < r; i++) {	//run back to top
		formater += "\n";
	}
	
	for (int i = 0; i < c; i++) {	//run back to top
		formater += "";
	}
	printf("%s", formater.c_str());
	
	for (int i = 0; i < currBlock->rows; i++) {
		for (int j = 0; j < currBlock->cols; j++) {
			if (i+r > rowCount || j+c > colCount || i+r < 0 || j+c < 0) {
				continue;
			} else {
				printf("%c", currBlock->mat[i][j]);
			}
		}
		printf("\n");
	}
	
}
*/


bool Engine::FrameAction(long int tickTime) {
	static bool flipSwitch = false;
	static long int savedTick = 0;
	
	if (InvokeDownMoveTick <= 0) {
		InvokeDownMoveTick = tick + tickTime;
	}
	
	if (flipSwitch && tick != savedTick) {
		flipSwitch = !flipSwitch;
		savedTick = 0;
	}
	
	if (InvokeDownMoveTick <= tick && !flipSwitch) {
		flipSwitch = true;
		savedTick = tick;
		InvokeDownMoveTick = 0;
		return true;
	}
	
	return false;
}