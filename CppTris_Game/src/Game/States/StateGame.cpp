#include "StateGame.h"

StateGame::StateGame(core::Application* app) :
	State(app),
	m_Grid(nullptr),
	m_CurrentPiece(nullptr),
	m_CurrLevelSpeed(10),
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

void StateGame::OnEnter() {
	DEBUG_LOG("Starting the Game");

	m_Grid = new Grid();
	m_App->Instantiate(m_Grid);

	Piece::setRNG();
	spawnNextPiece();

	m_DropTimer = m_CurrLevelSpeed;
}

void StateGame::spawnNextPiece() {
	m_App->Destroy(m_CurrentPiece);
	m_CurrentPiece = new Piece(Piece::getRandomPieceType(), m_Grid, 0, 5);
	m_App->Instantiate(m_CurrentPiece);

	//the spawned piece immediately collides with the grid
	if (m_CurrentPiece->pieceCollidesWithGrid()) {
		resetGame();
	}
}

void StateGame::resetGame() {
	if (m_CurrentPiece != nullptr) {
		m_App->Destroy(m_CurrentPiece);
		m_Grid->reset();
	}
}

void StateGame::OnKeyDown(SDL_KeyboardEvent* e)
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

void StateGame::OnKeyUp(SDL_KeyboardEvent* e)
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

void StateGame::InitDas() {
	if (m_CurrentPiece->movePosOnGrid(0, m_Input.right - m_Input.left)) {
		m_DasTimer = DELAYED_AUTO_SHIFT_FRAME_DELAY;
	}
	else {
		m_DasTimer = 0;
	}
}

void StateGame::OnUpdate() {
	UpdateDrop();
	UpdateDas();
}

void StateGame::UpdateDrop() {
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

void StateGame::UpdateDas() {
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