#include "Surface.h"

Surface::Surface() {
}

SDL_Surface* Surface::OnLoad(const char* file) {
	SDL_Surface* surfTemp = NULL;
	SDL_Surface* surfRet = NULL;

	surfTemp = SDL_LoadBMP(file);
	if (surfTemp == NULL) {
		return NULL;
	}

	surfRet = SDL_ConvertSurfaceFormat(surfTemp, SDL_PIXELFORMAT_RGBA32, 0);
	return surfRet;
}

bool Surface::OnDraw(SDL_Surface* surfDest, SDL_Surface* surfSrc, int x, int y) {
	if (surfDest == NULL || surfSrc == NULL) {
		return false;
	}

	SDL_Rect destR;
	destR.x = x;
	destR.y = y;

	SDL_BlitSurface(surfSrc, NULL, surfDest, &destR);

	return true;
}