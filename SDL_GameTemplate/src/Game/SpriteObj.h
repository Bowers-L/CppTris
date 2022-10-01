#pragma once

#include <SDL.h>

class SpriteObj {
private:
	SDL_Texture* m_Tex;
public:
	int x;
	int y;

	int scaleX;
	int scaleY;

public:
	SpriteObj(int x, int y);
	SpriteObj(int x, int y, float scaleX, float scaleY);

	void Draw(SDL_Renderer* renderer);

	void SetTex(SDL_Texture* tex);
};