#include <iostream>
#include <string>
#include <unistd.h>

#include "./include/printer.h"
#include "./include/engine.h"

int main(int arg, char* args[]) {
	int rows = 12, cols = 12;
	cout << arg << endl;
	if (arg > 1) {
		rows = stoi(args[1]);
		cols = stoi(args[2]);
	}
	Engine gameEngine(rows, cols);
	/*
	for (int i = 0; i < 10000; i++) {
		cout << "getting spawning block at i: " << i << endl;
		gameEngine.CanRotateBlock(false);
		gameEngine.SpawnBlock();
	}
	*/
	gameEngine.GameLoop();
	
	return 0;
}
