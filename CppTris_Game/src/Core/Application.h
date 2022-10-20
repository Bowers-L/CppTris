#pragma once

#include <SDL.h>

#define SCREEN_WIDTH 640
#define SCREEN_HEIGHT 480

#define FRAME_DELAY 16

namespace core {
	class Application {
	private:
		bool m_Running;

		const char* m_GameTitle;
		Uint32 m_WindowFlags;

	protected:
		SDL_Window* m_Window;
		SDL_Renderer* m_Renderer;

	public:
		Application(const char* gameTitle, Uint32 windowFlags);

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
	};
}