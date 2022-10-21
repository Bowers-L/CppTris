#include "Application.h"
#include "Log.h"

#include <glad/glad.h>
#include <iostream>


namespace core {

	Application::Application(const char* gameTitle) :
		m_GameTitle(gameTitle),
		m_Running(false),
		m_Window(nullptr)
	{
		Renderer::CreateInstance(SCREEN_WIDTH, SCREEN_HEIGHT);
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

			SDL_Delay(FRAME_DELAY);	//Lock the framerate at 62.5 fps
		}

		Teardown();
		return 0;
	}

	bool Application::Startup()
	{
		SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
		SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 3);
		SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);

		if (SDL_Init(SDL_INIT_EVERYTHING) < 0) {
			SDL_LogMessage(SDL_LOG_CATEGORY_APPLICATION, SDL_LOG_PRIORITY_ERROR, "Could not initialize SDL: %s", SDL_GetError());
			return false;
		}

		m_Window = SDL_CreateWindow(m_GameTitle, SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,
			SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_OPENGL | SDL_WINDOW_SHOWN);
		if (m_Window == NULL) {

			return false;
		}
		
		SDL_GLContext glContext = SDL_GL_CreateContext(m_Window);
		if (glContext == NULL) {
			SDLLogError(__FILE__, __LINE__);
		}

		if (!gladLoadGLLoader( (GLADloadproc) SDL_GL_GetProcAddress))
		{
			std::cout << "Failed to initialize GLAD" << std::endl;
			return -1;
		}

		//m_Renderer = SDL_CreateRenderer(m_Window, -1, 0);
		//if (m_Renderer == NULL) {
		//	return false;
		//}

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
		//There's probably a C++20 way to do this, but I forgot.
		for (auto it = m_GameObjects.begin(); it != m_GameObjects.end(); it++) {
			GameObject* object = *it;
			object->update();
		}

		OnUpdate();
	}

	void Application::Render()
	{
		//SDL_SetRenderDrawColor(m_Renderer, 128, 128, 128, 255);
		//SDL_RenderClear(m_Renderer);

		GL_CALL(glClearColor(0.0f, 0.0f, 0.0f, 1.0f));
		GL_CALL(glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT));

		for (auto it = m_GameObjects.begin(); it != m_GameObjects.end(); it++) {
			GameObject* object = *it;
			object->draw();
		}

		OnDraw();

		SDL_GL_SwapWindow(m_Window);
		//SDL_RenderPresent(m_Renderer);
	}

	void Application::Teardown()
	{
		for (auto it = m_GameObjects.begin(); it != m_GameObjects.end(); it++) {
			delete *it;
		}
		m_GameObjects.clear();

		OnQuit();
		SDL_Quit();
	}

	void Application::Instantiate(GameObject* object)
	{
		m_GameObjects.push_back(object);
	}

	void Application::Destroy(GameObject* object) 
	{
		for (int i = 0; i < m_GameObjects.size(); i++) {
			if (m_GameObjects[i] == object) {
				delete m_GameObjects[i];
				break;
			}
		}
	}
}