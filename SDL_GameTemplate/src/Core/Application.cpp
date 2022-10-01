#include "Application.h"

#include <iostream>

namespace core {

	Application::Application(const char* gameTitle, Uint32 windowFlags) : 
		m_GameTitle(gameTitle), 
		m_WindowFlags(windowFlags), 
		m_Running(false), 
		m_Window(nullptr), 
		m_Renderer(nullptr), 
		m_WindowSurface(nullptr) {}

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
		}

		Teardown();
		return 0;
	}

	bool Application::Startup()
	{
		if (SDL_Init(SDL_INIT_EVERYTHING) < 0) {
			printf("Could not initialize SDL: %s", SDL_GetError());
			return false;
		}

		m_Window = SDL_CreateWindow(m_GameTitle, SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,
			SCREEN_WIDTH, SCREEN_HEIGHT, m_WindowFlags);
		if (m_Window == NULL) {

			return false;
		}
		m_WindowSurface = SDL_GetWindowSurface(m_Window);

		m_Renderer = SDL_CreateRenderer(m_Window, -1, 0);
		if (m_Renderer == NULL) {
			return false;
		}

		return true;
	}

	void Application::ProcessEvent(SDL_Event* e)
	{
		if (e->type == SDL_QUIT) {
			m_Running = false;
		}
	}

	void Application::Update()
	{
		OnUpdate();
	}

	void Application::Render()
	{
		SDL_SetRenderDrawColor(m_Renderer, 0, 0, 0, 255);
		SDL_RenderClear(m_Renderer);

		OnDraw();

		SDL_UpdateWindowSurface(m_Window);
	}

	void Application::Teardown()
	{
		SDL_Quit();
	}
}
