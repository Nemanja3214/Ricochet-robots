#pragma once
#include <iostream>
#include <utility>
#include "State.h"
#include <unordered_map>
#include <string>
#include <random>
#include <time.h>
#include <unordered_map>
using namespace std;


const int MAX_NUM_OF_WALLS = 20;
class Game {
public:
	Game();
	State& GetState();
	int Search(int depth);
private:
	State current_state;
	int active_position;
	int wallsLeft = MAX_NUM_OF_WALLS;
	int goalPosition = 0;
	unordered_map<int, int> passedStates;
	
};