#include "Application.h"

#include <iostream>

namespace core {

	Application::Application(const char* gameTitle, Uint32 windowFlags) : 
		m_GameTitle(gameTitle), 
		m_WindowFlags(windowFlags), 
		m_Running(false), 
		m_Window(nullptr), 
		m_Renderer(nullptr) {}

	int Application::Run() {
		if (!Startup()) {
			return -1;
		}

		m_Running = true;
		while (m_Running) {
			SDL_Event e;
			while (SDL_PollEvent(&e)) {
				ProcessEvent(&e);
			}

			Update();
			Render();

			SDL_Delay(FRAME_DELAY);	//Lock the framerate at 62.5 fps
		}

		Teardown();
		return 0;
	}

	bool Application::Startup()
	{
		if (SDL_Init(SDL_INIT_EVERYTHING) < 0) {
			SDL_LogMessage(SDL_LOG_CATEGORY_APPLICATION, SDL_LOG_PRIORITY_ERROR, "Could not initialize SDL: %s", SDL_GetError());
			return false;
		}

		m_Window = SDL_CreateWindow(m_GameTitle, SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,
			SCREEN_WIDTH, SCREEN_HEIGHT, m_WindowFlags);
		if (m_Window == NULL) {

			return false;
		}

		m_Renderer = SDL_CreateRenderer(m_Window, -1, 0);
		if (m_Renderer == NULL) {
			return false;
		}

		OnStart();

		return true;
	}

	void Application::ProcessEvent(SDL_Event* e)
	{
		switch (e->type) {
		case SDL_QUIT:
			m_Running = false;
		case SDL_KEYDOWN:
			OnKeyDown(&e->key);
			break;
		case SDL_KEYUP:
			OnKeyUp(&e->key);
			break;
		default:
			OnEvent(e);
			break;
		}
	}

	void Application::Update()
	{
		OnUpdate();
	}

	void Application::Render()
	{
		SDL_SetRenderDrawColor(m_Renderer, 128, 128, 128, 255);
		SDL_RenderClear(m_Renderer);

		OnDraw();

		SDL_RenderPresent(m_Renderer);
	}

	void Application::Teardown()
	{
		OnQuit();
		SDL_Quit();
	}
}
