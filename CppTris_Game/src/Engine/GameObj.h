#pragma once

#include <SDL.h>

class GameObj
{
public:
	int x, y;

public:
	virtual void Draw() = 0;
};