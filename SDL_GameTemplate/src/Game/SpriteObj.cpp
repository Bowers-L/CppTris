#include "Core/Core.h"

#include "SpriteObj.h"

SpriteObj::SpriteObj(int x, int y) : x(x), y(y), m_Tex(NULL)
{
}

void SpriteObj::Draw(SDL_Renderer* renderer) {
	texture::BlitTexture(renderer, m_Tex, x, y);
}

void SpriteObj::SetTex(SDL_Texture* tex)
{
	m_Tex = tex;
}