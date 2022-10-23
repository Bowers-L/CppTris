#pragma once

#include "Engine/Core.h"

#include "GameObjects/Grid.h"
#include "GameObjects/Piece.h"

#include "States/StateGame.h"
#include "States/StateTitle.h"

class StateManager;
class StateTitle;
class StateGame;

class Game : public Application
{
private:
	StateManager* m_StateManager;
	StateTitle* m_StateTitle;
	StateGame* m_StateGame;
public:
	Game(const char* title);

	void OnStart();	//Initialize game data
	void OnEvent(SDL_Event* e);
	void OnKeyDown(SDL_KeyboardEvent* e);
	void OnKeyUp(SDL_KeyboardEvent* e);
	void OnUpdate();	//Update game data
	void OnDraw();	//Render game objects
	void OnQuit();	//Do any cleanup

	StateGame* stateGame();
};