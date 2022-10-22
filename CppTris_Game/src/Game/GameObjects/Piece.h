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
	int m_Orientation;

	Grid* m_Grid;
	int m_GridRow, m_GridCol;
public:
	Piece(PieceType type, Grid* grid, int gridRow, int gridCol);

	void update();
	void draw();

	//Returns if the move was successfully made
	bool setPosOnGrid(int row, int col);
	bool movePosOnGrid(int dRow, int dCol);

	void rotateCW();
	void rotateCCW();

	static void setRNG();
	static PieceType getRandomPieceType();

private:
	bool isBlockAt(int pieceRow, int pieceCol);
	bool pieceCollidesWithGrid(int dRow, int dCol);
	void drawBlock(int x, int y);
};