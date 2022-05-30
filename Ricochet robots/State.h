#pragma once // includes are added once
#include <utility>
#include <iostream>
#include <string>
#include <functional>
#include "MatrixField.h"
#include "Definitions.h"
using namespace std;
 // matrix field coding N,S,W,E and A - presence of walls and if it has active robot

class State {
public:
	State();
	State(const State& other);
	void InitState(int& wallsLeft, int& gameGoalPosition, int& active_state_i, int& active_state_j);
	MatrixField* GetBoard();
	void Print();
	int ToHash();
	int active_position_i;
	int active_position_j;


private:
	MatrixField board[SIZE * SIZE];
	int goalPosition = 0;
	pair<int, int> robot_positions[4]; // 4 tuples for robot coordinates
	

	void printHorizontalDashes(int i, function<bool(int, int)> isWallPresent);
};
