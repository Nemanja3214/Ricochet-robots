#include "Game.h"



Game::Game() : current_state() {
	current_state.InitState(wallsLeft, goalPosition, active_position_i, active_position_j);
}

State& Game::GetState() {
	return current_state;
}

int Game::Search(int depth) {
	//if (goalPosition == active_position)
		return depth;
	//TODO add to map
}

// result i and j maybe sufficient
int Game::FindEnd(Direction direction, int& result_i, int& result_j) {
	MatrixField currentField(current_state.GetBoard()[active_position_i * SIZE + active_position_j]);
	MatrixField nextField;
	int i = active_position_i;
	int j = active_position_j;

	if (direction == N) {
		nextField = current_state.GetBoard()[(i - 1) * SIZE + j];
		while (!currentField.N && !nextField.S && i != 0) {
			--i;
			currentField = current_state.GetBoard()[i * SIZE + j];
			nextField = current_state.GetBoard()[(i + 1) * SIZE + j];
		}
		result_i = i;
		result_j = j;
		return i * SIZE + j;
	}

	if (direction == S) {
		nextField = current_state.GetBoard()[(i + 1) * SIZE + j];
		while (!currentField.S && !nextField.N && i != SIZE - 1) {
			++i;
			currentField = current_state.GetBoard()[i * SIZE + j];
			nextField = current_state.GetBoard()[(i + 1) * SIZE + j];
		}
		result_i = i;
		result_j = j;
		return i * SIZE + j;
	}

	if (direction == E) {
		nextField = current_state.GetBoard()[i * SIZE + (j + 1)];
		while (!currentField.E && !nextField.W && j != SIZE - 1) {
			++j;
			currentField = current_state.GetBoard()[i * SIZE + j];
			nextField = current_state.GetBoard()[i * SIZE + (j + 1)];
		}
		result_i = i;
		result_j = j;
		return i * SIZE + j;
	}

	if (direction == W) {
		nextField = current_state.GetBoard()[i * SIZE + (j - 1)];
		while (!currentField.W && !nextField.E && j != 0) {
			--j;
			currentField = current_state.GetBoard()[i * SIZE + j];
			nextField = current_state.GetBoard()[i * SIZE + (j - 1)];
		}
		result_i = i;
		result_j = j;
		return i * SIZE + j;
	}
}

void Game::DoMove(Direction direction) {
	int result_i, result_j;
	int endPosition = FindEnd(direction, result_i, result_j);
}

void Game::Print() {
	current_state.Print();
}
