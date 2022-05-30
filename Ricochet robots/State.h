#pragma once // includes are added once
#include <utility>
#include <iostream>
#include <string>
#include <functional>
#include "MatrixField.h"
using namespace std;
 // matrix field coding N,S,W,E and A - presence of walls and if it has active robot

class State {
public:
	State();
	State(const State& other);
	void InitState(int& wallsLeft, int& goalPosition);
	MatrixField* GetBoard();
	void Print();
	int ToHash();

	static const int SIZE = 16;

private:
	MatrixField board[SIZE * SIZE];
	int goalPosition = 0;
	pair<int, int> robot_positions[4]; // 4 tuples for robot coordinates
	int active_position;

	void printHorizontalDashes(int i, function<bool(int, int)> predicate);
};
