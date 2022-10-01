#pragma once

#include <SDL.h>

const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 480;

class Application {
private:
	bool m_Running;
	SDL_Window* m_Window;
public:
	Application();

	int Run();	//Called by main when the application starts up. Contains the main game loop.


	bool Startup();	//Called when application starts.

	//Called once per frame
	void OnEvent(SDL_Event* e);
	void OnUpdate();
	void OnRender();

	void Teardown();	//Called when application finishes
};