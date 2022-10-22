#include "Grid.h"

Grid::Grid()
	: GameObject(GRID_OFFSET_X, GRID_OFFSET_Y)
{
}

void Grid::draw() {
	Shader* shader = getShader();
	shader->setUniform4f("u_Color", 0.5f, 0.5f, 0.5f, 1.0f);
	Renderer::setShader(*shader);
	Renderer::drawRect(GRID_OFFSET_X, GRID_OFFSET_Y, GRID_SIZE_X * BLOCK_SIZE, GRID_SIZE_Y * BLOCK_SIZE);
}
