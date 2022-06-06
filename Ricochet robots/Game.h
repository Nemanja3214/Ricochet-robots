#pragma once
#include <iostream>
#include <utility>
#include "State.h"
#include <unordered_map>
#include <string>
#include <random>
#include <time.h>
#include <set>
#include "Definitions.h"
using namespace std;

class Game {
public:
	
	Game(int active_position_i, int active_position_j);
	State& GetState();
	int Search();
private:
	State start_state;
	int wallsLeft = MAX_NUM_OF_WALLS;
	int goal_position_i;
	int goal_position_j;
	set<int> passedStates;
	
	
};