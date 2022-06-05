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
	
	Game(int active_position_i, int active_position_j);
	State& GetState();
	int Search();
	//void Print();

	
private:
	State start_state;
	int search(int depth, State state);
	int wallsLeft = MAX_NUM_OF_WALLS;
	int goalPosition = 0;
	unordered_map<int, int> passedStates;
	
	
};