#pragma once

#include "Engine/Core.h"

#include "Piece.h"

class Piece;	//forward declaration to prevent circular dependency

#define GRID_NUM_COLS 10
#define GRID_NUM_ROWS 20
#define BLOCK_SIZE 20

//Center horizontally and vertically
#define GRID_OFFSET_Y (SCREEN_HEIGHT / 2 - BLOCK_SIZE * GRID_NUM_ROWS / 2)
#define GRID_OFFSET_X (SCREEN_WIDTH / 2 - BLOCK_SIZE * GRID_NUM_COLS / 2)

class Grid : public GameObject
{
private:
	char m_Blocks[GRID_NUM_ROWS][GRID_NUM_COLS];
public:
	Grid();

	void reset();

	void draw();
	void drawBlock(int row, int col);

	bool isBlockAt(int row, int col);

	void placePiece(Piece* piece, int row, int col);
};