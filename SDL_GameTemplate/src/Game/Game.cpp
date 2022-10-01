#include "Game.h"
#include "Core/Core.h"

core::Application* CreateApp() {
	return new game::Game("My Game", SDL_WINDOW_OPENGL);
}

namespace game {
	Game::Game(const char* title, Uint32 flags) : Application(title, flags), m_Player() {}

	void Game::OnStart() {
		DEBUG_LOG("Starting the Game");
		m_Player.x = 100;
		m_Player.y = 100;
		m_Player.tex = texture::LoadTexture(m_Renderer, "Assets/Sprites/Temp_DOGGO.bmp");
	}

	void Game::OnDraw() {
		texture::BlitTexture(m_Renderer, m_Player.tex, m_Player.x, m_Player.y);
	}
}
