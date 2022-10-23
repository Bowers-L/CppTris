#pragma once

#include "Engine/Core.h"

#include "../Game.h"

#include "../GameObjects/Piece.h"
#include "../GameObjects/Grid.h"

#define DELAYED_AUTO_SHIFT_FRAME_DELAY 16
#define AUTO_SHIFT_FRAME_DELAY 4

#define HARD_DROP_DELAY 2


class Grid;
class Piece;
class Game;

class StateGame : public State
{
private:
	input::Input m_Input;

	Grid* m_Grid;
	Piece* m_CurrentPiece;
	int m_CurrLevelSpeed;

	int m_DropTimer;
	int m_DasTimer;

public:
	StateGame(Game* app, StateManager* stateManager);

	void OnEnter();
	void OnUpdate();
	void OnKeyDown(SDL_KeyboardEvent* e);
	void OnKeyUp(SDL_KeyboardEvent* e);

	void spawnNextPiece();
	void resetGame();
private:
	void InitDas();
	void UpdateDrop();
	void UpdateDas();
};