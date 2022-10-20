#pragma once

#include <SDL.h>

class GameObj
{
public:
	int x, y;

public:
	virtual void Draw(SDL_Renderer* renderer) = 0;
};