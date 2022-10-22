#pragma once

#include "Engine/Core.h"

#include "Piece.h"

class Piece;	//forward declaration to prevent circular dependency

#define GRID_NUM_COLS 10
#define GRID_NUM_ROWS 20
#define BLOCK_SIZE 20

//Center horizontally
#define GRID_OFFSET_Y 20
#define GRID_OFFSET_X (SCREEN_WIDTH / 2 - BLOCK_SIZE * 5)

class Grid : public GameObject
{
private:
	char m_Blocks[GRID_NUM_ROWS][GRID_NUM_COLS];
public:
	Grid();

	void draw();
	void drawBlock(int row, int col);

	void placePiece(Piece* piece, int row, int col);
};