#pragma once

#include <unordered_map>

#include "Engine/Core.h"


class Piece : public GameObject
{
public:
	Piece(int x, int y);
	Piece();

	void draw();
};