#include "Game.h"
#include "Engine/Core.h"

#include "GameObjects/Piece.h"

#include <glm/glm.hpp>
#include <random>

using namespace input;

Application* CreateApp() {
	return new Game("CppTris");
}

Game::Game(const char* title) :
	Application(title),
	m_StateManager(new StateManager()),
	m_StateTitle(new StateTitle(this, m_StateManager)),
	m_StateGame(new StateGame(this, m_StateManager))
{
}

//Honestly, at this point the state manager should extend the application class.
void Game::OnStart() {
	m_StateManager->GoTo(m_StateGame);
}

void Game::OnEvent(SDL_Event* e) {
	m_StateManager->OnEvent(e);
}

void Game::OnKeyDown(SDL_KeyboardEvent* e) {
	m_StateManager->OnKeyDown(e);
}
void Game::OnKeyUp(SDL_KeyboardEvent* e) {
	m_StateManager->OnKeyUp(e);
}

void Game::OnUpdate() {
	m_StateManager->Update();
}

void Game::OnDraw() {
	m_StateManager->Draw();
}
void Game::OnQuit() {
	m_StateManager->Cleanup();

	delete m_StateManager;
	delete m_StateTitle;
	delete m_StateGame;
}

StateGame* Game::stateGame() {
	return m_StateGame;
}
