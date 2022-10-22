#pragma once

#include <random>
#include <unordered_map>

#include "Engine/Core.h"

#include "Grid.h"
#include "PieceData.h"

class Grid;	//forward declaration to prevent circular dependency

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
	bool rotateCW();
	bool rotateCCW();

	bool isBlockAt(int pieceRow, int pieceCol);
	bool isBlockAt(int pieceRow, int pieceCol, int orientation);

	void placeOnGrid();

	static void setRNG();
	static PieceType getRandomPieceType();
private:
	bool updateOrientation(int newOrientation);

	bool pieceCollidesWithGrid(int centerGridRow, int centerGridCol);
	bool pieceCollidesWithGrid(int centerGridRow, int centerGridCol, int orientation);
	void drawBlock(int x, int y);
};