#include "Surface.h"

Surface::Surface() {
}

SDL_Surface* Surface::OnLoad(char* file) {
	SDL_Surface* surfTemp = NULL;
	SDL_Surface* surfRet = NULL;

	surfTemp = SDL_LoadBMP(file);
	if (surfTemp == NULL) {
		return NULL;
	}

	surfRet = SDL_ConvertSurfaceFormat(surfTemp, SDL_PIXELFORMAT_RGBA32, 0);
	return surfRet;
}