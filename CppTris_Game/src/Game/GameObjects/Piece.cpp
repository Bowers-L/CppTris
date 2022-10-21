#include "Piece.h"

#include <math.h>
#include <time.h>

std::mt19937_64 Piece::s_RNG;

Piece::Piece(PieceType type, int x, int y) :
	GameObject(x, y),
	m_PieceType(type),
	m_Orientation(0)
{
}

Piece::Piece(PieceType type) :
	GameObject(),
	m_PieceType(type),
	m_Orientation(0)
{
}

void Piece::update() {

}

void Piece::draw() {
	Shader* shader = getShader();
	shader->setUniform4f("u_Color", 0.0f, 0.0f, 1.0f, 1.0f);
	Renderer::setShader(*shader);

	PieceData data = pieceData.at(m_PieceType);
	for (int row = 0; row < PIECE_GRID_SIZE; row++) {
		for (int col = 0; col < PIECE_GRID_SIZE; col++) {
			int index = row * PIECE_GRID_SIZE + col;
			char blockAtIndex = data.m_BlockGridPositions[0][index];

			if (blockAtIndex) {
				int blockXPos = m_Position.x + (col - PIECE_CENTER_COL) * BLOCK_SIZE;
				int blockYPos = m_Position.y + (row - PIECE_CENTER_ROW) * BLOCK_SIZE;
				drawBlock(blockXPos, blockYPos);
			}
		}
	}
}

void Piece::drawBlock(int x, int y) {
	//Draw a rectangle with a 1 pixel border
	Renderer::drawRect(x+1, y+1, BLOCK_SIZE-1, BLOCK_SIZE-1);

	//Drawing the borders

}

void Piece::setPosOnGrid(Grid* grid, int row, int col)
{
	m_Position.x = grid->position().x + BLOCK_SIZE * col;
	m_Position.y = grid->position().y + BLOCK_SIZE * row;
}

void Piece::movePosOnGrid(Grid* grid, int dRow, int dCol)
{
	m_Position.x += dCol * BLOCK_SIZE;
	m_Position.y += dRow * BLOCK_SIZE;
}

PieceType Piece::getRandomPieceType() {
	int rand = s_RNG() % 7;
	DEBUG_LOG("%d", rand);
	return (PieceType) (rand);
}

void Piece::setRNG() {
	s_RNG.seed(std::time(NULL)+1);
}