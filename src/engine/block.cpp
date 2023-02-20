#include "../include/block.h"

Block::Block() {}

Block::Block(int array[][2], int size, bool multiRotate, int id) {
	rows = size;
	cols = size;
	mat = new int*[size];
	for (size_t i = 0; i < size; i++) {
		mat[i] = new int[size];
		for (size_t j = 0; j < size; j++) {
			mat[i][j] = array[i][j];
		}
	}
	flipAble = multiRotate;
	index = id;
	//cout << "invoked" << endl;
}

Block::Block(int array[][3], int size, bool multiRotate, int id) {
	rows = size;
	cols = size;
	mat = new int*[size];
	for (size_t i = 0; i < size; i++) {
		mat[i] = new int[size];
		for (size_t j = 0; j < size; j++) {
			mat[i][j] = array[i][j];
		}
	}
	flipAble = multiRotate;
	index = id;
}

	
Block::Block(int array[][4], int size, bool multiRotate, int id) {
	rows = size;
	cols = size;
	mat = new int*[size];
	for (size_t i = 0; i < size; i++) {
		mat[i] = new int[size];
		for (size_t j = 0; j < size; j++) {
			mat[i][j] = array[i][j];
		}
	}
	flipAble = multiRotate;
	index = id;
}


/*
Block& Block::operator=(const Block &blk) {
	rows = blk.rows;
	cols = blk.cols;
	mat = blk.mat;
	return *this;
}
*/

/*
Block& Block::operator=(Block &&blk) {
	rows = blk.rows;
	cols = blk.cols;
	mat = blk.mat;
	cout << "invoked" << endl;
	blk.mat = nullptr;
	return *this;
}
*/

Block::~Block() {
	for (int i = 0; i < rows; i++) {
		delete[] mat[i];
	}
	delete[] mat;
}

void Block::rotateLeft() {	
	int top = 0;
	int bottom = rows - 1;
	
	while (bottom >= top) {
		int left = top;
		int right = bottom;
		for (int i =  0; i < right - left; i++) {
			int first = mat[top][left + i];
			
			mat[top][left + i] = mat[top + i][right];
			mat[top + i][right] = mat[bottom][right - i];
			mat[bottom][right - i] = mat[bottom - i][left];
			mat[bottom - i][left] = first;
			
		}
		bottom--;
		top++;
	}
}

void Block::rotateRight() {
	
	int top = 0;
	int bottom = rows - 1;
	
	while (bottom >= top) {
		int left = top;
		int right = bottom;
		for (int i = 0; i < right - left; i++) {
			int first = mat[top][left + i];
			
			mat[top][left + i] = mat[bottom - i][left];
			mat[bottom - i][left] = mat[bottom][right - i];
			mat[bottom][right - i] = mat[top + i][right];
			mat[top + i][right] = first;
			
		}
		bottom--;
		top++;
	}
}

void Block::blkReset() {
	r = -1;
	c = 0;
	if (index == 6) {	//'O' block
		r = 0;
	}
	for (int i = 0; i < rows; i++) {
		for (int j = 0; j < cols; j++) {
			switch (index) {	//ik you could just made an array of them but I am lazy
			case 0:
				mat[i][j] = arrI[i][j];
				break;
			case 1:
				mat[i][j] = arrL[i][j];
				break;
			case 2:
				mat[i][j] = arrJ[i][j];
				break;
			case 3:
				mat[i][j] = arrZ[i][j];
				break;
			case 4:
				mat[i][j] = arrS[i][j];
				break;
			case 5:
				mat[i][j] = arrT[i][j];
				break;
			case 6:
				mat[i][j] = arrO[i][j];
				break;
			default:
				break;
			}
		}
	}
} 