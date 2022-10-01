#pragma once

#include <SDL.h>

class Surface {
public:
	Surface();

	static SDL_Surface* OnLoad(const char* file);
	static bool OnDraw(SDL_Surface* surfDest, SDL_Surface* surfSrc, int x, int y);
};

