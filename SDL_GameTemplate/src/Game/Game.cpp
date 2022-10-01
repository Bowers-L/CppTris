#include "Game.h"
#include "Core/Core.h"

core::Application* CreateApp() {
	return new game::Game("My Game", SDL_WINDOW_OPENGL);
}

namespace game {
	Game::Game(const char* title, Uint32 flags) : Application(title, flags), m_Player(200, 200, 5, 1) {
	}

	void Game::OnStart() {
		DEBUG_LOG("Starting the Game");
		SDL_Texture* playerTex = texture::LoadTexture(m_Renderer, "Assets/Sprites/Temp_DOGGO.bmp");
		m_Player.SetTex(playerTex);
	}

	void Game::OnDraw() {
		m_Player.Draw(m_Renderer);
	}
}
