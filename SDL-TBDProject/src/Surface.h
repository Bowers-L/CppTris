#pragma once

#include <SDL.h>

class Surface {
public:
	Surface();

	static SDL_Surface* OnLoad(char* file);
};

