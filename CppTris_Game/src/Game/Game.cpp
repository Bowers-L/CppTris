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
		m_CurrLevelSpeed(10),
		m_CurrentPiece(nullptr),
		m_DropTimer(0),
		m_DasTimer(0),
		m_Grid(nullptr)
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
		m_CurrentPiece = new Piece(Piece::getRandomPieceType(), m_Grid, 0, 5);
		Instantiate(m_CurrentPiece);

		//the spawned piece immediately collides with the grid
		if (m_CurrentPiece->pieceCollidesWithGrid()) {
			resetGame();
		}
	}

	void Game::resetGame() {
		if (m_CurrentPiece != nullptr) {
			Destroy(m_CurrentPiece);
			m_Grid->reset();
		}
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

				InitDas();

				break;
			case SDL_SCANCODE_RIGHT:
				m_Input.right = 1;
				InitDas();
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

	void Game::InitDas() {
		if (m_CurrentPiece->movePosOnGrid(0, m_Input.right - m_Input.left)) {
			m_DasTimer = DELAYED_AUTO_SHIFT_FRAME_DELAY;
		}
		else {
			m_DasTimer = 0;
		}
	}

	void Game::OnUpdate() {
		UpdateDrop();
		UpdateDas();
	}

	void Game::UpdateDrop() {
		if (m_DropTimer <= 0) {
			bool movedDown = m_CurrentPiece->movePosOnGrid(1, 0);
			if (!movedDown) {
				m_CurrentPiece->placeOnGrid();
				spawnNextPiece();
			}

			m_DropTimer = m_Input.down ? HARD_DROP_DELAY : m_CurrLevelSpeed;
		}
		else {
			m_DropTimer--;
		}
	}

	void Game::UpdateDas() {
		int dx = m_Input.right - m_Input.left;
		if (m_Input.left || m_Input.right) {
			if (m_DasTimer <= 0) {
				m_CurrentPiece->movePosOnGrid(0, dx);
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
