#pragma once

#include <SDL.h>

#define SCREEN_WIDTH 640
#define SCREEN_HEIGHT 480

class Application {
private:
	bool m_Running;

	SDL_Window* m_Window;
	SDL_Renderer* m_Renderer;
	SDL_Surface* m_WindowSurface;
public:
	Application();

	int Run();	//Called by main when the application starts up. Contains the main game loop.


	bool Startup();	//Called when application starts.

	//virtual functions corresponding to callback
	virtual void OnStart() {}
	virtual void OnUpdate() {}
	virtual void OnDraw() {}
	virtual void OnQuit() {}

	//Called once per frame
	void ProcessEvent(SDL_Event* e);
	void Update();
	void Render();

	void Teardown();	//Called when application finishes

private:
	SDL_Window* CreateWindow() const;
};