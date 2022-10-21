#pragma once

#include <unordered_map>

#include "Engine/Core.h"

#include "PieceData.h"

#include "Grid.h"


class Piece : public GameObject
{
private:
	PieceType m_PieceType;
	unsigned int m_Orientation;
public:
	Piece(PieceType type, int x, int y);
	Piece(PieceType type);

	void draw();

	void setPosOnGrid(Grid* grid, int row, int col);

	static PieceType getRandomPieceType();
};