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
		m_Grid = new Grid();
		Instantiate(m_Grid);
		m_CurrentPiece = new Piece(Piece::getRandomPieceType(), GRID_OFFSET_X + 5*BLOCK_SIZE, GRID_OFFSET_Y);
		Instantiate(m_CurrentPiece);
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
		m_CurrentPiece->position().x += dx * m_PlayerVx;
	}

	void Game::OnDraw() {

	}
}
