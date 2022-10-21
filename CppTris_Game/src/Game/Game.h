#pragma once

#include "Engine/Core.h"

#include "GameObjects/Grid.h"
#include "GameObjects/Piece.h"

namespace game {
	class Game : public core::Application
	{
	private:
		Grid* m_Grid;
		Piece* m_CurrentPiece;
		input::Input m_Input;

		int m_PlayerVx, m_PlayerVy;
		int m_CurrLevelSpeed;
		int m_DropTimer;
	public:
		Game(const char* title);
		void OnStart();	//Initialize game data
		//void OnEvent(SDL_Event* e);
		void OnKeyDown(SDL_KeyboardEvent* e);
		void OnKeyUp(SDL_KeyboardEvent* e);
		void OnUpdate();	//Update game data
		void OnDraw();	//Render game objects
		//void OnQuit();	//Do any cleanup
	};
}