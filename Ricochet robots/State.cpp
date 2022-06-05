//malapisa
#include "State.h"
#include <random>
#include <time.h>
#include <string>
#include <functional>
State::State() {

}

State::State(const State& other) {
	this->active_position_i = other.active_position_i;
	this->active_position_j = other.active_position_j;
	this->goal_position_i = other.goal_position_i;
	this->goal_position_j = other.goal_position_j;
	this->depth = other.depth;
	copy(begin(other.board), end(other.board), board);
}

void State::printHorizontalDashes(int i, function<bool(int, int)> isWallPresent) {
	cout << " ";
	for (int j = 0; j < SIZE; ++j) {
		if (isWallPresent(i, j))
			cout << "_";
		else
			cout << " ";
		cout << "  ";
	}
	cout << endl;
}

void State::Print() {
	for (int i = 0; i < SIZE; ++i) {
		// print north walls
		printHorizontalDashes(i, [=](int i, int j) { return board[i * SIZE + j].N; });

		// print east and west walls
		for (int j = 0; j < SIZE; ++j) {
			if (board[i * SIZE + j].W)
				cout << "|";
			else
				cout << " ";

			if(board[i * SIZE + j].A)
				cout << "A";
			else if(i == goal_position_i && j == goal_position_j)
				cout << "G";
			else
				cout << " ";


			if (board[i * SIZE + j].E)
				cout << "|";
			else
				cout << " ";
		}
		cout << endl;

		// print south walls
		printHorizontalDashes(i, [=](int i, int j) { return board[i * SIZE + j].S; });
	}
}
void State::DoMove(Direction direction) {
	int end_i, end_j;
	// find where will robot end
	FindEnd(direction, active_position_i, active_position_j, end_i, end_j);
	// current active field is no longer active
	board[active_position_i * SIZE + active_position_j].A = false;
	// set new active
	active_position_i = end_i;
	active_position_j = end_j;
	board[end_i * SIZE + end_j].A = true;

}

State::Direction State::GetOppositeDirection(State::Direction direction) {
	switch (direction) {
	case N: return S;
	case S: return N;
	case E: return W;
	case W: return E;
	default: throw exception("Non existant direction");
	};
}


void State::InitState(int& wallsLeft, int& game_goal_position_i, int& game_goal_position_j, int& game_active_position_i, int& game_active_position_j) {
	srand(time(NULL));
	bool N, S, W, E, A;
	for (int i = 0; i < SIZE; ++i) {
		for (int j = 0; j < SIZE; ++j) {
			N = false;
			S = false;
			W = false;
			E = false;
			A = false;

			// randomly generate walls
			if (wallsLeft > 0) {
				N = !(rand() % 20);
				if (N)
					--wallsLeft;
				else
				{
					S = !(rand() % 20);
					if (S) --wallsLeft;
				}
				
				if (S || N) {
					W = !(rand() % 1);
					if (W)
						--wallsLeft;
					else {
						E = !(rand() % 1);
						if (E) --wallsLeft;
					}
					
				}
				
			}
			// edges of the board guarantee walls
			if (i == 0)
				N = true;
			if (j == 0)
				W = true;
			if (j == SIZE - 1)
				E = true;
			if (i == SIZE - 1)
				S = true;

			board[i * SIZE + j].E = E;
			board[i * SIZE + j].N = N;
			board[i * SIZE + j].W = W;
			board[i * SIZE + j].S = S;
		}
	}
	/*
	// randomly choose active position
	int active_position = rand() % (SIZE * SIZE);

	while(board[active_position].CountWalls() < 2)
		active_position = rand() % (SIZE * SIZE);

	board[active_position].A = true;
	active_position_i = active_position / SIZE;
	active_position_j = active_position % SIZE;
	game_active_state_i = active_position_i;
	game_active_state_j = active_position_j;

	// randomly set goal for robot
	goalPosition = rand() % (SIZE * SIZE);
	while (board[goalPosition].CountWalls() < 2)
		goalPosition = rand() % (SIZE * SIZE);
	gameGoalPosition = goalPosition;*/

	//TEST
	board[0].A = true;
	active_position_i = 0;
	active_position_j = 0;
	game_active_position_i = active_position_i;
	game_active_position_j = active_position_j;

	goal_position_i = 7;
	goal_position_j = 7;
	game_goal_position_i = goal_position_i;
	game_goal_position_j = goal_position_j;
}

MatrixField& State::GetActive() {
	return board[active_position_i * SIZE + active_position_j];
}

int State::ToHash() {
	return active_position_i * SIZE + active_position_j ; // the active robot is the only dynamic factor
}


bool State::CanMove(Direction direction) {
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

MatrixField& State::GetNextField(int i, int j, Direction direction) {
	switch (direction) {
	case N: return board[(i - 1) * SIZE + j];
	case S: return board[(i + 1) * SIZE + j];
	case E: return board[i * SIZE + (j + 1)];
	case W: return board[i * SIZE + (j - 1)];
	default: throw exception("Next field error");
	}
}

int State::FindEnd(Direction direction, int i, int j, int& result_i, int& result_j) {
	MatrixField currentField(board[i * SIZE + j]);
	MatrixField nextField;

	if (direction == N) {
		nextField = board[(i - 1) * SIZE + j];
		while (!currentField.N && !nextField.S && i != 0) {
			--i;
			currentField = board[i * SIZE + j];
			nextField = GetNextField(i, j, N);
		}
	}

	if (direction == S) {
		nextField = board[(i + 1) * SIZE + j];
		while (!currentField.S && !nextField.N && i != SIZE - 1) {
			++i;
			currentField = board[i * SIZE + j];
			nextField = GetNextField(i, j, S);
		}
	}

	if (direction == E) {
		nextField = board[i * SIZE + (j + 1)];
		while (!currentField.E && !nextField.W && j != SIZE - 1) {
			++j;
			currentField = board[i * SIZE + j];
			nextField = GetNextField(i, j, E);
		}
	}

	if (direction == W) {
		nextField = board[i * SIZE + (j - 1)];
		while (!currentField.W && !nextField.E && j != 0) {
			--j;
			currentField = board[i * SIZE + j];
			nextField = GetNextField(i, j, W);
		}
	}
	result_i = i;
	result_j = j;
	return i * SIZE + j;
}

