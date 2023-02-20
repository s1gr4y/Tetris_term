#ifndef BLOCK_H
#define BLOCK_H

#include <stdio.h>
#include <iostream>

#include "../include/constants.h"

using namespace std;

using namespace UniversalVars;

class Block {
public:
	int **mat;
	int index = 0;
	int rows = 0;
	int cols = 0;
	int r = -1;
	int c = 0;
	
	bool alternator = false;	//false == rotate left, true == rotate right
	bool flipAble = false;
	
	Block();
	~Block();
	
	Block(int array[][2], int size, bool multiRotate, int id);
	Block(int array[][3], int size, bool multiRotate, int id);
	Block(int array[][4], int size, bool multiRotate, int id);
	//Block& operator=(const Block &blk);
	//Block& operator=(Block &&blk);
	
	init();
	void rotateLeft();
	void rotateRight();
	void blkReset();	//reset orientation and position.
};

#endif