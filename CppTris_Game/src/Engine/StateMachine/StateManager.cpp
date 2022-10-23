#include "StateManager.h"

StateManager::StateManager() :
	m_CurrState(nullptr)
{}

void StateManager::GoTo(State* newState)
{
	if (m_CurrState != nullptr) {
		m_CurrState->OnExit();
	}

	newState->OnEnter();
	m_CurrState = newState;
}

void StateManager::OnEvent(SDL_Event* e) {
	if (m_CurrState != nullptr) {
		m_CurrState->OnEvent(e);
	}
}

void StateManager::OnKeyDown(SDL_KeyboardEvent* e) {
	if (m_CurrState != nullptr) {
		m_CurrState->OnKeyDown(e);
	}
}

void StateManager::OnKeyUp(SDL_KeyboardEvent* e) {
	if (m_CurrState != nullptr) {
		m_CurrState->OnKeyUp(e);
	}
}

void StateManager::Update()
{
	if (m_CurrState != nullptr) {
		m_CurrState->OnUpdate();
	}
}

void StateManager::Draw() {
	if (m_CurrState != nullptr) {
		m_CurrState->OnDraw();
	}
}

void StateManager::Cleanup() {
	if (m_CurrState != nullptr) {
		m_CurrState->OnExit();
		m_CurrState = nullptr;
	}
}