#pragma once

#include "Engine/Core.h"
#include "../Game.h"

class Game;
class StateManager;

class StateTitle : public State
{
public:
	StateTitle(Game* app, StateManager* stateManager);

	void OnKeyDown(SDL_KeyboardEvent* e);

	inline Game* context() {
		return (Game*) m_App;
	}
};