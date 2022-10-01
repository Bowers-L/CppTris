#pragma once

#include "Core/Application.h"

namespace game {
	class Game : public core::Application
	{
	public:
		Game(const char* title, Uint32 flags);
		void OnStart();

	};
}