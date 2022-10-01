#pragma once

#include <SDL.h>

const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 480;

class Application {
private:
	bool m_Running;
	SDL_Window* m_Window;
	SDL_Renderer* m_Renderer;
	SDL_Surface* m_WindowSurface;

	SDL_Surface* m_SurfTest;
public:
	Application();

	int Run();	//Called by main when the application starts up. Contains the main game loop.


	bool Startup();	//Called when application starts.

	//Called once per frame
	void OnEvent(SDL_Event* e);
	void OnUpdate();
	void OnRender();

	void Teardown();	//Called when application finishes

private:
	SDL_Window* CreateWindow() const;
};