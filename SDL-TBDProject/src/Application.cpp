#include "Application.h"

Application::Application() : m_Running(true), m_Window(nullptr) {
	m_Running = true;
}

int Application::Run() {
	if (!Startup()) {
		return -1;
	}

	SDL_Event e;
	while (m_Running) {
		while (SDL_PollEvent(&e)) {
			OnEvent(&e);
		}

		OnUpdate();
		OnRender();
	}

	Teardown();
	return 0;
}

bool Application::Startup()
{
	if (SDL_Init(SDL_INIT_EVERYTHING) < 0) {
		return false;
	}

	const char* gameTitle = "TBD Game";
	Uint32 flags = SDL_WINDOW_OPENGL;
	if ((m_Window = SDL_CreateWindow(	gameTitle,					//title of window
										SDL_WINDOWPOS_UNDEFINED,	//xpos of window
										SDL_WINDOWPOS_UNDEFINED,	//ypos of window
										SCREEN_WIDTH,				//width
										SCREEN_HEIGHT,				//height
										flags)						//flags
		) == NULL) {

		return false;
	}

	return true;
}

void Application::OnEvent(SDL_Event* e)
{
	if (e->type == SDL_QUIT) {
		m_Running = false;
	}
}

void Application::OnUpdate()
{
}

void Application::OnRender()
{
}

void Application::Teardown()
{
	SDL_Quit();
}

int main(int argc, char* argv[]) {
	Application app;

	return app.Run();
}