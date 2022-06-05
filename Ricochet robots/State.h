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
	enum Direction { W, N, E, S };
	State();
	void InitState(int& wallsLeft, int& gameGoalPosition, int& game_active_position_i, int& game_active_position_j);
	MatrixField* GetBoard();
	void Print();
	int ToHash();
	int active_position_i;
	int active_position_j;
	int FindEnd(State::Direction direction, int i, int j, int& result_i, int& result_j);
	bool CanMove(State::Direction direction);
	MatrixField& GetActive();
	MatrixField& GetNextField(int i, int j, State::Direction direction);
	void DoMove(State::Direction direction);
	static Direction GetOppositeDirection(Direction direction);

private:
	MatrixField board[SIZE * SIZE];
	int goalPosition = 0;
	pair<int, int> robot_positions[4]; // 4 tuples for robot coordinates
	

	void printHorizontalDashes(int i, function<bool(int, int)> isWallPresent);
};
