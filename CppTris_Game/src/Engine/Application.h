#pragma once

#include <SDL.h>
#include <vector>

#include "GameObject.h"
#include "Renderer/Renderer.h"

#define SCREEN_WIDTH 640
#define SCREEN_HEIGHT 480

#define FRAME_DELAY 16

namespace core {
	class Application {
	private:
		bool m_Running;

		const char* m_GameTitle;

		std::vector<GameObject*> m_GameObjects;
	protected:
		SDL_Window* m_Window;

	public:
		Application(const char* gameTitle);

		int Run();	//Called by main when the application starts up. Contains the main game loop.


		bool Startup();	//Called when application starts.

		virtual void OnStart() {}	//Initialize game data
		virtual void OnEvent(SDL_Event* e) {}
		virtual void OnKeyDown(SDL_KeyboardEvent* e) {}
		virtual void OnKeyUp(SDL_KeyboardEvent* e) {}
		virtual void OnUpdate() {}	//Update game data
		virtual void OnDraw() {}	//Render game objects
		virtual void OnQuit() {}	//Do any cleanup

		//Called once per frame
		void ProcessEvent(SDL_Event* e);
		void Update();
		void Render();

		void Teardown();	//Called when application finishes

		void Instantiate(GameObject* object);
		void Destroy(GameObject* object);
	};
}
