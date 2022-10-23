#include "Game.h"
#include "Engine/Core.h"

#include "GameObjects/Piece.h"

#include <glm/glm.hpp>
#include <random>

using namespace input;

core::Application* CreateApp() {
	return new game::Game("CppTris");
}

namespace game {
	Game::Game(const char* title) :
		Application(title),
		m_StateManager(core::StateManager()),
		m_StateGame(StateGame(this))
	{
	}

	//Honestly, at this point the state manager should extend the application class.
	void Game::OnStart() {
		m_StateManager.GoTo(&m_StateGame);
	}

	void Game::OnEvent(SDL_Event* e) {
		m_StateManager.OnEvent(e);
	}

	void Game::OnKeyDown(SDL_KeyboardEvent* e) {
		m_StateManager.OnKeyDown(e);
	}
	void Game::OnKeyUp(SDL_KeyboardEvent* e) {
		m_StateManager.OnKeyUp(e);
	}

	void Game::OnUpdate() {
		m_StateManager.Update();
	}

	void Game::OnDraw() {
		m_StateManager.Draw();
	}
	void Game::OnQuit() {
		m_StateManager.Cleanup();
	}
}
