#pragma once

#include "../Application.h"

#include "State.h"

class State;

class StateManager
{
private:
	State* m_CurrState;
public:
	StateManager();

	void GoTo(State* newState);

	void OnEvent(SDL_Event* e);
	void OnKeyDown(SDL_KeyboardEvent* e);
	void OnKeyUp(SDL_KeyboardEvent* e);
	void Update();
	void Draw();
	void Cleanup();
};