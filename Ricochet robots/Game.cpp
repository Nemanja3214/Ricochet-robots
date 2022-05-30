#include "Game.h"



Game::Game() : current_state() {
	current_state.InitState(wallsLeft, goalPosition);
}

State& Game::GetState() {
	return current_state;
}

int Game::Search(int depth) {
	if (goalPosition == active_position)
		return depth;
	//TODO add to map
}