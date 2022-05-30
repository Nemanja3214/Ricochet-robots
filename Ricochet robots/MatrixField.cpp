#include "MatrixField.h"

int MatrixField::CountWalls() {
	int numOfWalls = 0;
	if (N)++numOfWalls;
	if (S)++numOfWalls;
	if (W)++numOfWalls;
	if (E)++numOfWalls;
	return numOfWalls;
}

MatrixField::MatrixField(const MatrixField& other) {
	N = other.N;
	W = other.W;
	S = other.S;
	E = other.E;
	A = other.A;
}