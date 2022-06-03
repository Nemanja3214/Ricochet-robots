#include "Game.h"



Game::Game() : current_state(){
	current_state.InitState(wallsLeft, goalPosition, active_position_i, active_position_j);
}

State& Game::GetState() {
	return current_state;
}

Game::Direction Game::getOppositeDirection(Direction direction) {
	switch (direction) {
	case N: return S;
	case S: return N;
	case E: return W;
	case W: return E;
	default: throw exception("Non existant direction");
	};
}

int Game::search(int depth) {
	if (goalPosition == active_position_i * SIZE + active_position_i) {
		return depth;
	}

	if (passedStates.find(current_state.ToHash()) == passedStates.end())
		passedStates[current_state.ToHash()] = depth;
	else if (passedStates[current_state.ToHash()] > depth)
		passedStates[current_state.ToHash()] = depth;
	else
		return 0;

	for (int i = 0; i < 4; ++i) {
		Direction direction = static_cast<Direction>(i);
		if (!CanMove(direction))
			continue;
		
		DoMove(direction);
		int result = 0;
		if (passedStates.find(current_state.ToHash()) == passedStates.end())
			Print();
		result = search(depth + 1);
		DoMove(getOppositeDirection(direction));
		if (result)
			return result;
	}
	return 0;
}

int Game::Search() {
	return search(0);;
}

MatrixField& Game::GetActive() {
	return current_state.GetBoard()[active_position_i * SIZE + active_position_j];
}

bool Game::CanMove(Direction direction) {
	MatrixField activeField = GetActive();
	if (direction == N && (activeField.N || GetNextField(active_position_i, active_position_j, N).S))
		return false;
	else if (direction == S && (activeField.S || GetNextField(active_position_i, active_position_j, S).N))
		return false;
	else if (direction == E && (activeField.E || GetNextField(active_position_i, active_position_j, E).W))
		return false;
	else if (direction == W && (activeField.W || GetNextField(active_position_i, active_position_j, W).E))
		return false;
	else
		return true;
}

MatrixField& Game::GetNextField(int i, int j, Direction direction) {
	switch (direction) {
	case N: return current_state.GetBoard()[(i - 1) * SIZE + j];
	case S: return current_state.GetBoard()[(i + 1) * SIZE + j];
	case E: return current_state.GetBoard()[i * SIZE + (j + 1)];
	case W: return current_state.GetBoard()[i * SIZE + (j - 1)];
	default: throw exception("Next field error");
	}
}

int Game::FindEnd(Direction direction, int i, int j, int& result_i, int& result_j) {
	MatrixField currentField(current_state.GetBoard()[i * SIZE + j]);
	MatrixField nextField;

	if (direction == N) {
		nextField = current_state.GetBoard()[(i - 1) * SIZE + j];
		while (!currentField.N && !nextField.S && i != 0) {
			--i;
			currentField = current_state.GetBoard()[i * SIZE + j];
			nextField = GetNextField(i, j, N);
		}
	}

	if (direction == S) {
		nextField = current_state.GetBoard()[(i + 1) * SIZE + j];
		while (!currentField.S && !nextField.N && i != SIZE - 1) {
			++i;
			currentField = current_state.GetBoard()[i * SIZE + j];
			nextField = GetNextField(i, j, S);
		}
	}

	if (direction == E) {
		nextField = current_state.GetBoard()[i * SIZE + (j + 1)];
		while (!currentField.E && !nextField.W && j != SIZE - 1) {
			++j;
			currentField = current_state.GetBoard()[i * SIZE + j];
			nextField = GetNextField(i, j, E);
		}
	}

	if (direction == W) {
		nextField = current_state.GetBoard()[i * SIZE + (j - 1)];
		while (!currentField.W && !nextField.E && j != 0) {
			--j;
			currentField = current_state.GetBoard()[i * SIZE + j];
			nextField = GetNextField(i, j, W);
		}
	}
	result_i = i;
	result_j = j;
	return i * SIZE + j;
}

void Game::DoMove(Direction direction) {
	int end_i, end_j;
	// find where will robot end
	FindEnd(direction, active_position_i, active_position_j, end_i, end_j);
	// current active field is no longer active
	current_state.GetBoard()[active_position_i * SIZE + active_position_j].A = false;
	// set new active
	active_position_i = end_i;
	active_position_j = end_j;
	current_state.GetBoard()[end_i * SIZE + end_j].A = true;
	current_state.active_position_i = end_i;
	current_state.active_position_j = end_j;

}

void Game::Print() {
	current_state.Print();
}
