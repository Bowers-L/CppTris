#pragma once

#include "../Application.h"
#include "StateManager.h"

class StateManager;
class Application;

class State
{
protected:
	Application* m_App;
	StateManager* m_StateManager;
public:
	State(Application* app, StateManager* stateManager);

	virtual void OnEnter() {}

	virtual void OnEvent(SDL_Event* e) {}
	virtual void OnKeyDown(SDL_KeyboardEvent* e) {}
	virtual void OnKeyUp(SDL_KeyboardEvent* e) {}
	virtual void OnUpdate() {}
	virtual void OnDraw() {}

	virtual void OnExit() {}
};