#include "Application.h"

Application::Application() : m_Running(false), m_Window(nullptr), m_Renderer(nullptr), m_WindowSurface(nullptr) {
}

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
		return false;
	}

							
	m_Window = CreateWindow();
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

SDL_Window* Application::CreateWindow() const {
	const char* gameTitle = "TBD Game";
	Uint32 windowFlags = SDL_WINDOW_OPENGL;
	return SDL_CreateWindow(gameTitle, SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,
		SCREEN_WIDTH, SCREEN_HEIGHT, windowFlags);
}

void Application::ProcessEvent(SDL_Event* e)
{
	if (e->type == SDL_QUIT) {
		m_Running = false;
	}
}

void Application::Update()
{
}

void Application::Render()
{
	SDL_SetRenderDrawColor(m_Renderer, 0, 0, 0, 255);
	SDL_RenderClear(m_Renderer);
	

	SDL_UpdateWindowSurface(m_Window);
}

void Application::Teardown()
{
	SDL_Quit();
}

int main(int argc, char* argv[]) {
	Application app;

	return app.Run();
}