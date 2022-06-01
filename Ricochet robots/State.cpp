//malapisa
#include "State.h"
#include <random>
#include <time.h>
#include <string>
#include <functional>
State::State() {

}

State::State(const State& other) {
	throw new exception("not implemented yet");
}

MatrixField* State::GetBoard() {
	return board;
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
			else if(i * SIZE + j == goalPosition)
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



void State::InitState(int& wallsLeft, int& gameGoalPosition, int& game_active_state_i,  int& game_active_state_j) {
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
			

			// TODO max 3 walls

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
	game_active_state_i = active_position_i;
	game_active_state_j = active_position_j;
	goalPosition = 255;
	gameGoalPosition = 255;
}

int State::ToHash() {
	return active_position_i * SIZE + active_position_j ; // the active robot is the only dynamic factor
}