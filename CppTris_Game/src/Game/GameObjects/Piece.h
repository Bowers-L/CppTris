#pragma once

#include <random>
#include <unordered_map>

#include "Engine/Core.h"

#include "Grid.h"
#include "PieceData.h"


class Piece : public GameObject
{
private:
	static std::mt19937_64 s_RNG;

	PieceType m_PieceType;
	unsigned int m_Orientation;
public:
	Piece(PieceType type, int x, int y);
	Piece(PieceType type);

	void update();
	void draw();

	void setPosOnGrid(Grid* grid, int row, int col);
	void movePosOnGrid(Grid* grid, int dRow, int dCol);

	static void setRNG();
	static PieceType getRandomPieceType();

private:
	void drawBlock(int x, int y);
};