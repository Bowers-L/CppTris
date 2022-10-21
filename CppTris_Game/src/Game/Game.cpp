#include "Game.h"
#include "Engine/Core.h"

#include "GameObjects/Piece.h"

#include <glm/glm.hpp>

using namespace input;

core::Application* CreateApp() {
	return new game::Game("CppTris");
}

namespace game {
	Game::Game(const char* title) : 
		Application(title), 
		m_Player(new Piece(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2)), 
		m_Input(), 
		m_PlayerVx(6), 
		m_PlayerVy(6) 
	{
		m_Input.up = 0;
		m_Input.down = 0;
		m_Input.left = 0;
		m_Input.right = 0;
	}

	void Game::OnStart() {
		DEBUG_LOG("Starting the Game");
		Instantiate(m_Player);
	}

	void Game::OnKeyDown(SDL_KeyboardEvent* e)
	{
		if (e->repeat == 0) {
			switch (e->keysym.scancode) {
			case SDL_SCANCODE_UP:
				m_Input.up = 1;
				break;
			case SDL_SCANCODE_DOWN:
				m_Input.down = 1;
				break;
			case SDL_SCANCODE_LEFT:
				m_Input.left = 1;
				break;
			case SDL_SCANCODE_RIGHT:
				m_Input.right = 1;
				break;
			default:
				break;
			}
		}
	}

	void Game::OnKeyUp(SDL_KeyboardEvent* e)
	{
		if (e->repeat == 0) {
			switch (e->keysym.scancode) {
			case SDL_SCANCODE_UP:
				m_Input.up = 0;
				break;
			case SDL_SCANCODE_DOWN:
				m_Input.down = 0;
				break;
			case SDL_SCANCODE_LEFT:
				m_Input.left = 0;
				break;
			case SDL_SCANCODE_RIGHT:
				m_Input.right = 0;
				break;
			default:
				break;
			}
		}
	}

	void Game::OnUpdate() {
		int dx = m_Input.right - m_Input.left;
		int dy = m_Input.down - m_Input.up;
		if (dx != 0 && dy != 0) {
			m_Player->position().x += (int)((float)(dx * m_PlayerVx) * SQRTWO);
			m_Player->position().y += (int)((float)(dy * m_PlayerVy) * SQRTWO);
		}
		else {
			m_Player->position().x += dx * m_PlayerVx;
			m_Player->position().y += dy * m_PlayerVy;
		}
	}

	void Game::OnDraw() {

	}
}
