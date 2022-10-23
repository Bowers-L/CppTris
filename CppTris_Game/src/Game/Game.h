#pragma once

#include "Engine/Core.h"

#include "GameObjects/Grid.h"
#include "GameObjects/Piece.h"

#include "States/StateGame.h"

namespace game {
	class Game : public core::Application
	{
	private:
		core::StateManager m_StateManager;
		StateGame m_StateGame;
	public:
		Game(const char* title);

		void OnStart();	//Initialize game data
		void OnEvent(SDL_Event* e);
		void OnKeyDown(SDL_KeyboardEvent* e);
		void OnKeyUp(SDL_KeyboardEvent* e);
		void OnUpdate();	//Update game data
		void OnDraw();	//Render game objects
		void OnQuit();	//Do any cleanup
	};
}