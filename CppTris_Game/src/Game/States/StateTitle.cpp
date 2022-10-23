#include "StateTitle.h"

StateTitle::StateTitle(Game* app, StateManager* stateManager) :
	State(app, stateManager)
{
}

void StateTitle::OnKeyDown(SDL_KeyboardEvent* e) {
	switch (e->keysym.scancode) {
	case SDL_SCANCODE_X:
		m_StateManager->GoTo(context()->stateGame());
	}
}