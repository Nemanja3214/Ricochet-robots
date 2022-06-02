#pragma once
#include <iostream>
#include <utility>
#include "State.h"
#include <unordered_map>
#include <string>
#include <random>
#include <time.h>
#include <unordered_map>
#include "Definitions.h"
using namespace std;

class Game {
public:
	enum Direction { W, N, E, S, NO_DIRECTION };
	Game();
	State& GetState();
	int Search();
	void DoMove(Direction direction);
	void Print();
	int FindEnd(Direction direction, int& result_i, int& result_j);
	bool CanMove(Direction direction);
	MatrixField& GetActive();
	MatrixField& GetNextField(int i, int j, Direction direction);
	int active_position_i;
	int active_position_j;
private:
	State current_state;
	int search(int depth, Direction previousDirection);
	Direction getOppositeDirection(Direction direction);
	int wallsLeft = MAX_NUM_OF_WALLS;
	int goalPosition = 0;
	unordered_map<int, int> passedStates;
	
	
};