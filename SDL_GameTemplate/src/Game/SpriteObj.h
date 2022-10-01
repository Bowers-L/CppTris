#pragma once

#include <SDL.h>

class SpriteObj {
private:
	SDL_Texture* m_Tex;
public:
	int x;
	int y;

public:
	SpriteObj(int x, int y);

	void Draw(SDL_Renderer* renderer);

	void SetTex(SDL_Texture* tex);
};