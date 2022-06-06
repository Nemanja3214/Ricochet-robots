#include "Game.h"



Game::Game(int active_position_i, int active_position_j) : start_state(){
	start_state.InitState(wallsLeft, goalPosition, active_position_i, active_position_j);
}

State& Game::GetState() {
	return start_state;
}



int Game::search(int depth, State newState) {
	if (goalPosition == newState.active_position_i * SIZE + newState.active_position_i) {
		return depth;
	}

	if (passedStates.find(newState.ToHash()) == passedStates.end())
		passedStates[newState.ToHash()] = depth;
	else if (passedStates[newState.ToHash()] > depth)
		passedStates[newState.ToHash()] = depth;
	else
		return 0;

	for (int i = 0; i < 4; ++i) {
		State::Direction direction = static_cast<State::Direction>(i);
		if (!newState.CanMove(direction))
			continue;
		
		
		newState.DoMove(direction);
		int result = 0;
		if (passedStates.find(newState.ToHash()) == passedStates.end())
			newState.Print();
		result = search(depth + 1, newState);
		newState.DoMove(State::GetOppositeDirection(direction));
		if (result)
			return result;
	}
	return 0;
}

int Game::Search() {
	return search(0, start_state);
}





//void Game::Print() {
//	state.Print();
//}
