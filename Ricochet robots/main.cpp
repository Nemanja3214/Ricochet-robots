#include "Game.h"
#include "State.h"
#include "main.h"
using namespace std;
int main() {
	Game g;
	g.Print();
	cout << g.active_position_i << endl;
	cout << g.active_position_j << endl;
	int result_i, result_j;
	g.FindEnd(Game::N, result_i, result_j);
	cout << "N end: " << result_i << ", " << result_j << endl;
	g.FindEnd(Game::S, result_i, result_j);
	cout << "S end: " << result_i << ", " << result_j << endl;
	g.FindEnd(Game::E, result_i, result_j);
	cout << "E end: " << result_i << ", " << result_j << endl;
	g.FindEnd(Game::W, result_i, result_j);
	cout << "W end: " << result_i << ", " << result_j << endl;

	g.DoMove(Game::S);
	g.Print();
	cout << g.active_position_i << endl;
	cout << g.active_position_j << endl;

	return 0;
}