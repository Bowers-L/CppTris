#pragma once

#include "Engine/Core.h"

#include "GameObjects/Grid.h"
#include "GameObjects/Piece.h"

#define DELAYED_AUTO_SHIFT_FRAME_DELAY 16
#define AUTO_SHIFT_FRAME_DELAY 6

#define HARD_DROP_DELAY 2

namespace game {
	class Game : public core::Application
	{
	private:
		Grid* m_Grid;
		Piece* m_CurrentPiece;
		input::Input m_Input;

		int m_CurrLevelSpeed;

		int m_DropTimer;
		int m_DasTimer;
	public:
		Game(const char* title);

		void OnStart();	//Initialize game data
		//void OnEvent(SDL_Event* e);
		void OnKeyDown(SDL_KeyboardEvent* e);
		void OnKeyUp(SDL_KeyboardEvent* e);
		void OnUpdate();	//Update game data
		void OnDraw();	//Render game objects
		//void OnQuit();	//Do any cleanup

		void spawnNextPiece();
	private:
		void UpdateDrop();
		void UpdateDas();
	};
}