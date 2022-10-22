#pragma once

#include "Engine/Core.h"

#define GRID_SIZE_X 10
#define GRID_SIZE_Y 20
#define BLOCK_SIZE 20

//Center horizontally
#define GRID_OFFSET_Y 20
#define GRID_OFFSET_X (SCREEN_WIDTH / 2 - BLOCK_SIZE * 5)

class Grid : public GameObject
{
public:
	Grid();

	void draw();
};