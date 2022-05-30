#pragma once
struct MatrixField {
	bool N, S, W, E, A;
	MatrixField(bool N, bool S, bool W, bool E, bool A) : N(N), S(S), W(W), E(E), A(A) {};
	MatrixField() : N(false), S(false), W(false), E(false), A(false) {};
	MatrixField(const MatrixField& other);
	int CountWalls();
};