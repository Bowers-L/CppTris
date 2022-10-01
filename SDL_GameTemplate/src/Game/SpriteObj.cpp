#include "Core/Core.h"

#include "SpriteObj.h"

SpriteObj::SpriteObj(int x, int y) : x(x), y(y), scaleX(1), scaleY(1), m_Tex(NULL)
{
}

SpriteObj::SpriteObj(int x, int y, float scaleX, float scaleY) : x(x), y(y), scaleX(scaleX), scaleY(scaleX), m_Tex(NULL)
{
}

void SpriteObj::Draw(SDL_Renderer* renderer) {
	texture::BlitTexture(renderer, m_Tex, x, y, scaleX, scaleY);
}

void SpriteObj::SetTex(SDL_Texture* tex)
{
	m_Tex = tex;
}