#include "Piece.h"

#include <math.h>
#include <time.h>

std::mt19937_64 Piece::s_RNG;

Piece::Piece(PieceType type, Grid* grid, int gridRow, int gridCol) :
	m_PieceType(type),
	m_Grid(grid),
	m_Orientation(0),
	m_GridRow(gridRow),
	m_GridCol(gridCol)
{
	setPosOnGrid(gridRow, gridCol);
}

void Piece::update() {

}

void Piece::draw() {
	Shader* shader = getShader();
	shader->setUniform4f("u_Color", 0.0f, 0.0f, 1.0f, 1.0f);	//blue
	Renderer::setShader(*shader);

	PieceData data = pieceData.at(m_PieceType);
	for (int pieceRow = 0; pieceRow < PIECE_GRID_SIZE; pieceRow++) {
		for (int pieceCol = 0; pieceCol < PIECE_GRID_SIZE; pieceCol++) {
			if (isBlockAt(pieceRow, pieceCol)) {
				int blockRow = m_GridRow + pieceRow - PIECE_CENTER_ROW;
				int blockCol = m_GridCol + pieceCol - PIECE_CENTER_COL;
				m_Grid->drawBlock(blockRow, blockCol);
			}
		}
	}
}

void Piece::drawBlock(int x, int y) {
	//Draw a rectangle with a 1 pixel border
	Renderer::drawRect(x+1, y+1, BLOCK_SIZE-1, BLOCK_SIZE-1);
}

bool Piece::setPosOnGrid(int row, int col)
{
	if (!pieceCollidesWithGrid(row, col)) {
		m_GridRow = row;
		m_Position.y = m_Grid->position().y + BLOCK_SIZE * row;

		m_GridCol = col;
		m_Position.x = m_Grid->position().x + BLOCK_SIZE * col;

		return true;
	}

	return false;
}

bool Piece::movePosOnGrid(int dRow, int dCol)
{
	if (!pieceCollidesWithGrid(m_GridRow+dRow, m_GridCol+dCol)) {
		m_GridRow += dRow;
		m_GridCol += dCol;

		m_Position.x += dCol * BLOCK_SIZE;
		m_Position.y += dRow * BLOCK_SIZE;
		return true;
	}
	return false;
}

bool Piece::rotateCW() 
{
	int newOrientation = (m_Orientation + 1) % 4;

	return updateOrientation(newOrientation);
}

bool Piece::rotateCCW() {
	int newOrientation = m_Orientation - 1;
	if (newOrientation < 0) {
		newOrientation = 3;
	}

	return updateOrientation(newOrientation);
}

bool Piece::updateOrientation(int newOrientation) {
	if (!pieceCollidesWithGrid(m_GridRow, m_GridCol, newOrientation)) {
		m_Orientation = newOrientation;
		return true;
	}

	return false;
}

PieceType Piece::getRandomPieceType() {
	PieceType randomPiece = (PieceType) (s_RNG() % 7);
	DEBUG_LOG("Random Piece Generated: %s", pieceTypeString.at(randomPiece));
	return randomPiece;
}

void Piece::setRNG() {
	s_RNG.seed(std::time(NULL));
}

bool Piece::isBlockAt(int pieceRow, int pieceCol, int orientation)
{
	PieceData data = pieceData.at(m_PieceType);
	int index = pieceRow * PIECE_GRID_SIZE + pieceCol;
	return data.m_BlockGridPositions[orientation][index];
}

bool Piece::isBlockAt(int pieceRow, int pieceCol) {
	return isBlockAt(pieceRow, pieceCol, m_Orientation);
}

void Piece::placeOnGrid() {
	m_Grid->placePiece(this, m_GridRow, m_GridCol);
}

bool Piece::pieceCollidesWithGrid() {
	return pieceCollidesWithGrid(m_GridRow, m_GridCol);
}

bool Piece::pieceCollidesWithGrid(int centerGridRow, int centerGridCol) {
	return pieceCollidesWithGrid(centerGridRow, centerGridCol, m_Orientation);
}

bool Piece::pieceCollidesWithGrid(int centerGridRow, int centerGridCol, int orientation) {
	//Check grid positions against the piece data
	//If both are 1, there is a collision

	for (int pieceRow = 0; pieceRow < PIECE_GRID_SIZE; pieceRow++) {
		for (int pieceCol = 0; pieceCol < PIECE_GRID_SIZE; pieceCol++) {
			int gridRow = centerGridRow + pieceRow - PIECE_CENTER_ROW;
			int gridCol = centerGridCol + pieceCol - PIECE_CENTER_COL;

			if (isBlockAt(pieceRow, pieceCol, orientation)) {
				//check grid boundaries
				if (gridRow >= GRID_NUM_ROWS) {
					return true;
				}

				if (gridCol < 0 || gridCol >= GRID_NUM_COLS) {
					return true;
				}

				if (m_Grid->isBlockAt(gridRow, gridCol)) {
					return true;
				}
			}
		}
	}

	return false;
}

int Piece::getGridRow() {
	return m_GridRow;
}

int Piece::getGridCol() {
	return m_GridCol;
}