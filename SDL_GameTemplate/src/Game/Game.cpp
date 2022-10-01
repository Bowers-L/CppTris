#include "Game.h"

core::Application* CreateApp() {
	return new game::Game("My Game", SDL_WINDOW_OPENGL);
}

namespace game {
	Game::Game(const char* title, Uint32 flags) : Application(title, flags) {}



	void Game::OnStart() {

	}
}
