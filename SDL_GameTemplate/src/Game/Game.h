#pragma once

#include "Core/Core.h"

#include "SpriteObj.h"

namespace game {
	class Game : public core::Application
	{
	private:
		SpriteObj m_Player;
	public:
		Game(const char* title, Uint32 flags);
		void OnStart();	//Initialize game data
		//void OnEvent(SDL_Event* e);
		//void OnUpdate();	//Update game data
		void OnDraw();	//Render game objects
		//void OnQuit();	//Do any cleanup
	};
}