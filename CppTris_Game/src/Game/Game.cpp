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
		m_Input(), 
		m_PlayerVx(6), 
		m_PlayerVy(6),
		m_CurrLevelSpeed(10),
		m_CurrentPiece(nullptr),
		m_DropTimer(0),
		m_DasTimer(0)
	{
		m_Input.up = 0;
		m_Input.down = 0;
		m_Input.left = 0;
		m_Input.right = 0;
		m_Input.z = 0;
		m_Input.x = 0;
	}

	void Game::OnStart() {
		DEBUG_LOG("Starting the Game");

		m_Grid = new Grid();
		Instantiate(m_Grid);

		Piece::setRNG();
		spawnNextPiece();

		m_DropTimer = m_CurrLevelSpeed;
	}

	void Game::spawnNextPiece() {
		Destroy(m_CurrentPiece);
		m_CurrentPiece = new Piece(Piece::getRandomPieceType(), GRID_OFFSET_X + 5 * BLOCK_SIZE, GRID_OFFSET_Y);
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
				m_DasTimer = DELAYED_AUTO_SHIFT_FRAME_DELAY;
				m_CurrentPiece->movePosOnGrid(m_Grid, 0, m_Input.right - m_Input.left);
				break;
			case SDL_SCANCODE_RIGHT:
				m_Input.right = 1;
				m_DasTimer = DELAYED_AUTO_SHIFT_FRAME_DELAY;
				m_CurrentPiece->movePosOnGrid(m_Grid, 0, m_Input.right - m_Input.left);
				break;
			case SDL_SCANCODE_Z:
				m_Input.z = 1;
				m_CurrentPiece->rotateCCW();
				break;
			case SDL_SCANCODE_X:
				m_Input.x = 1;
				m_CurrentPiece->rotateCW();
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
			case SDL_SCANCODE_Z:
				m_Input.z = 0;
				break;
			case SDL_SCANCODE_X:
				m_Input.x = 0;
				break;
			default:
				break;
			}
		}
	}

	void Game::OnUpdate() {
		int dx = m_Input.right - m_Input.left;
		
		UpdateDrop();
		UpdateDas();

		if (m_CurrentPiece->position().y > SCREEN_HEIGHT) {
			spawnNextPiece();
		}
	}

	void Game::UpdateDrop() {
		if (m_DropTimer <= 0) {
			m_CurrentPiece->movePosOnGrid(m_Grid, 1, 0);
			m_DropTimer = m_CurrLevelSpeed;
		}
		else {
			m_DropTimer--;
		}
	}

	void Game::UpdateDas() {
		if (m_Input.left || m_Input.right) {
			if (m_DasTimer <= 0) {
				m_CurrentPiece->movePosOnGrid(m_Grid, 0, m_Input.right - m_Input.left);
				m_DasTimer = AUTO_SHIFT_FRAME_DELAY;
			}
			else {
				m_DasTimer--;
			}
		}
	}

	void Game::OnDraw() {

	}
}
