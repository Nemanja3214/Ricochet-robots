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
	enum Direction { W, N, E, S };
	Game();
	State& GetState();
	int Search(int depth);
	void DoMove(Direction direction);
	void Print();
	int FindEnd(Direction direction, int& result_i, int& result_j);
	int active_position_i;
	int active_position_j;
private:
	State current_state;
	
	int wallsLeft = MAX_NUM_OF_WALLS;
	int goalPosition = 0;
	unordered_map<int, int> passedStates;
	
	
};