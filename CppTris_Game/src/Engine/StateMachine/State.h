#pragma once

#include "../Application.h"

namespace core {
	class State
	{
	protected:
		Application* m_App;
	public:
		State(Application* app);
		virtual void OnEnter() {}

		virtual void OnEvent(SDL_Event* e) {}
		virtual void OnKeyDown(SDL_KeyboardEvent* e) {}
		virtual void OnKeyUp(SDL_KeyboardEvent* e) {}
		virtual void OnUpdate() {}
		virtual void OnDraw() {}

		virtual void OnExit() {}
	};
}