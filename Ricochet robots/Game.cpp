#include "Game.h"
#include <queue>

Game::Game(int active_position_i, int active_position_j) : start_state(){
	start_state.InitState(wallsLeft, goal_position_i, goal_position_j, active_position_i, active_position_j);
}

State& Game::GetState() {
	return start_state;
}

int Game::Search() {
	int depth = 1;
	queue<State> queue;
	queue.push(start_state);
	State currentState;
	passedStates.insert(start_state.ToHash());
	while (!queue.empty()) {
		currentState = queue.front();
		queue.pop();
		for (int i = 0; i < 4; ++i) {
			State::Direction direction = static_cast<State::Direction>(i);
			if (!currentState.CanMove(direction))
				continue;

			// do move
			currentState.DoMove(direction);
			++currentState.depth;

			// check whether it is a solution
			if (currentState.active_position_i == goal_position_i && currentState.active_position_j == goal_position_j) {
				return currentState.depth;
			}
				

			//check whether it has been already been seen
			if (passedStates.find(currentState.ToHash()) == passedStates.end()) {
				currentState.Print();
				queue.push(currentState);
				passedStates.insert(currentState.ToHash());
			}
			--currentState.depth;
			currentState.DoMove(State::GetOppositeDirection(direction));
		}
		cout << "<<<<<<<<<<<<<<<<<<<<<NEW NODE<<<<<<<<<<<<<<<<<<<" << endl;
		++depth;
	}
	return -1;
}





//void Game::Print() {
//	state.Print();
//}
