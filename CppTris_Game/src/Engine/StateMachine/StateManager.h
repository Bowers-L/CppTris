#pragma once

#include "../Application.h"

#include "State.h"

class core::Application;
class core::State;

namespace core {
	class StateManager
	{
	private:
		State* m_CurrState;
	public:
		StateManager();

		void GoTo(core::State* state);

		void OnEvent(SDL_Event* e);
		void OnKeyDown(SDL_KeyboardEvent* e);
		void OnKeyUp(SDL_KeyboardEvent* e);
		void Update();
		void Draw();
		void Cleanup();
	};
}



