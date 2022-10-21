#pragma once

#include "Engine/Core.h"

#include "GameObjects/Piece.h"

#define SQRTWO 0.707

namespace game {
	class Game : public core::Application
	{
	private:
		Piece* m_Player;
		input::Input m_Input;

		int m_PlayerVx, m_PlayerVy;
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