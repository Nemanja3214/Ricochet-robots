//malapisa
#include "State.h"
#include <random>
#include <time.h>
#include <string>
#include <functional>
State::State() {

}

State::State(const State& other) {
	
}

MatrixField* State::GetBoard() {
	return board;
}

void State::printHorizontalDashes(int i, function<bool(int, int)> isWallPresent) {
	cout << " ";
	for (int j = 0; j < State::SIZE; ++j) {
		if (isWallPresent(i, j))
			cout << "_";
		else
			cout << " ";
		cout << "  ";
	}
	cout << endl;
}

void State::Print() {
	for (int i = 0; i < State::SIZE; ++i) {
		printHorizontalDashes(i, [=](int i, int j) { return board[i * State::SIZE + j].N; });

		for (int j = 0; j < State::SIZE; ++j) {
			if (board[i * State::SIZE + j].W)
				cout << "|";
			else
				cout << " ";

			if(board[i * State::SIZE + j].A)
				cout << "A";
			else if(i * State::SIZE + j == goalPosition)
				cout << "G";
			else
				cout << " ";


			if (board[i * State::SIZE + j].E)
				cout << "|";
			else
				cout << " ";
		}
		cout << endl;

		printHorizontalDashes(i, [=](int i, int j) { return board[i * State::SIZE + j].S; });
	}
}



void State::InitState(int& wallsLeft, int& gameGoalPosition) {
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
				if (N) --wallsLeft;

				S = !(rand() % 20);
				if (S) --wallsLeft;

				W = !(rand() % 20);
				if (W) --wallsLeft;

				E = !(rand() % 20);
				if (E) --wallsLeft;
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
	//TODO add active randomly
	active_position = rand() % (SIZE * SIZE);

	while(board[active_position].CountWalls() < 2)
		active_position = rand() % (SIZE * SIZE);

	board[active_position].A = true;


	goalPosition = rand() % (SIZE * SIZE);
	while (board[goalPosition].CountWalls() < 2)
		goalPosition = rand() % (SIZE * SIZE);
	gameGoalPosition = goalPosition;
}

int State::ToHash() {
	return active_position; // the active robot is the only dynamic factor
}