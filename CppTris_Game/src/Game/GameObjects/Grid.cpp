#include "Grid.h"

Grid::Grid() : 
	GameObject(GRID_OFFSET_X, GRID_OFFSET_Y),
	m_Blocks()
{
	reset();
}

void Grid::reset() {
	for (int row = 0; row < GRID_NUM_ROWS; row++) {
		for (int col = 0; col < GRID_NUM_COLS; col++) {
			m_Blocks[row][col] = 0;
		}
	}
}

void Grid::draw() {
	Shader* shader = getShader();
	Renderer::setShader(*shader);

	//draw border
	shader->setUniform4f("u_Color", 0.5f, 0.5f, 0.5f, 1.0f);	//grey
	Renderer::drawRect(GRID_OFFSET_X, GRID_OFFSET_Y, GRID_NUM_COLS * BLOCK_SIZE, GRID_NUM_ROWS * BLOCK_SIZE);

	//draw blocks
	shader->setUniform4f("u_Color", 1.0f, 0.0f, 0.0f, 1.0f);	//red
	for (int row = 0; row < GRID_NUM_ROWS; row++) {
		for (int col = 0; col < GRID_NUM_COLS; col++) {
			if (m_Blocks[row][col]) {
				drawBlock(row, col);
			}
		}
	}
}

bool Grid::isBlockAt(int gridRow, int gridCol) {
	return m_Blocks[gridRow][gridCol];
}

void Grid::drawBlock(int row, int col) {
	//Draw a rectangle with a 1 pixel border
	int x = m_Position.x + col * BLOCK_SIZE;
	int y = m_Position.y + row * BLOCK_SIZE;
	Renderer::drawRect(x + 1, y + 1, BLOCK_SIZE - 1, BLOCK_SIZE - 1);
}

void Grid::placePiece(Piece* piece, int row, int col) {
	for (int pieceRow = 0; pieceRow < PIECE_GRID_SIZE; pieceRow++) {
		for (int pieceCol = 0; pieceCol < PIECE_GRID_SIZE; pieceCol++) {
			int pieceIndex = pieceRow * PIECE_GRID_SIZE + pieceCol;
			if (piece->isBlockAt(pieceRow, pieceCol)) {
				int gridRow = row + pieceRow - PIECE_CENTER_ROW;
				int gridCol = col + pieceCol - PIECE_CENTER_COL;

				if (gridRow >= 0 && gridRow <= GRID_NUM_ROWS && gridCol >= 0 && gridCol <= GRID_NUM_COLS) {
					m_Blocks[gridRow][gridCol] = 1;
				}
			}
		}
	}

	clearFullLines();
}

void Grid::clearFullLines() {
	bool lineCleared = false;
	do  {
		lineCleared = false;
		for (int gridRow = GRID_NUM_ROWS - 1; gridRow >= 0; gridRow--) {
			if (lineCleared) {
				//move the row down
				moveRowDown(gridRow);
			}
			else {
				lineCleared = checkRowFull(gridRow);
			}
		}

		if (lineCleared) {
			for (int gridCol = 0; gridCol < GRID_NUM_COLS; gridCol++) {
				m_Blocks[0][gridCol] = 0;
			}
		}
	} while (lineCleared);
}

void Grid::moveRowDown(int gridRow) {
	if (gridRow >= GRID_NUM_ROWS - 1) {
		DEBUG_LOG_WARNING("Couldn't move row down because it was the last row.");
		return;
	}

	for (int gridCol = 0; gridCol < GRID_NUM_COLS; gridCol++) {
		m_Blocks[gridRow + 1][gridCol] = m_Blocks[gridRow][gridCol];
	}
}

bool Grid::checkRowFull(int gridRow) {
	bool rowFull = true;
	for (int gridCol = 0; gridCol < GRID_NUM_COLS; gridCol++) {
		if (!m_Blocks[gridRow][gridCol]) {
			rowFull = false;
		}
	}
	return rowFull;
}