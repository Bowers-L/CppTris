#include "Piece.h"

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

void Piece::draw() {
	Shader* shader = getShader();
	//shader->setUniform4f("u_Color", 1.0f, 0.0f, 0.0f, 1.0f);
	Renderer::setShader(*shader);

	PieceData data = pieceData.at(m_PieceType);
	for (int row = 0; row < PIECE_GRID_SIZE; row++) {
		for (int col = 0; col < PIECE_GRID_SIZE; col++) {
			int index = row * PIECE_GRID_SIZE + col;
			char blockAtIndex = data.m_BlockGridPositions[0][index];

			if (blockAtIndex) {
				int blockXPos = m_Position.x + (col - PIECE_CENTER_COL) * BLOCK_SIZE;
				int blockYPos = m_Position.y + (row - PIECE_CENTER_ROW) * BLOCK_SIZE;
				Renderer::drawRect(blockXPos, blockYPos, BLOCK_SIZE, BLOCK_SIZE);
			}
		}
	}
}

void Piece::setPosOnGrid(Grid* grid, int row, int col)
{
	m_Position.x = grid->position().x + BLOCK_SIZE * col;
	m_Position.y = grid->position().y + BLOCK_SIZE * row;
}

PieceType Piece::getRandomPieceType() {
	float rand = 0.0f;
	return (PieceType) ((int) (rand*NUM_PIECES));
}