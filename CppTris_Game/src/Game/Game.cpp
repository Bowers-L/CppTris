#include "Game.h"
#include "Engine/Core.h"

#include <glm/glm.hpp>

using namespace input;

core::Application* CreateApp() {
	return new game::Game("CppTris");
}

namespace game {
	Game::Game(const char* title) : Application(title), m_Player(200, 200, 1, 1), m_Input(), m_PlayerVx(6), m_PlayerVy(6) {
		m_Input.up = 0;
		m_Input.down = 0;
		m_Input.left = 0;
		m_Input.right = 0;
	}

	void Game::OnStart() {
		DEBUG_LOG("Starting the Game");
		//SDL_Texture* playerTex = texture::LoadTexture(m_Renderer, "Assets/Sprites/Temp_DOGGO.bmp");
		//m_Player.SetTex(playerTex);
	}

	void Game::OnKeyDown(SDL_KeyboardEvent* e)
	{
		if (e->repeat == 0) {
			switch (e->keysym.scancode) {
			case SDL_SCANCODE_UP:
				m_Input.up = 1;
				break;
			case SDL_SCANCODE_DOWN:
				m_Input.down = 1;
				break;
			case SDL_SCANCODE_LEFT:
				m_Input.left = 1;
				break;
			case SDL_SCANCODE_RIGHT:
				m_Input.right = 1;
				break;
			default:
				break;
			}
		}
	}

	void Game::OnKeyUp(SDL_KeyboardEvent* e)
	{
		if (e->repeat == 0) {
			switch (e->keysym.scancode) {
			case SDL_SCANCODE_UP:
				m_Input.up = 0;
				break;
			case SDL_SCANCODE_DOWN:
				m_Input.down = 0;
				break;
			case SDL_SCANCODE_LEFT:
				m_Input.left = 0;
				break;
			case SDL_SCANCODE_RIGHT:
				m_Input.right = 0;
				break;
			default:
				break;
			}
		}
	}

	void Game::OnUpdate() {
		int dx = m_Input.right - m_Input.left;
		int dy = m_Input.down - m_Input.up;
		if (dx != 0 && dy != 0) {
			m_Player.x += (int) ((float) (dx * m_PlayerVx) * SQRTWO);
			m_Player.y += (int) ((float) (dy * m_PlayerVy) * SQRTWO);
		}
		else {
			m_Player.x += dx * m_PlayerVx;
			m_Player.y += dy * m_PlayerVy;
		}
	}

	void Game::OnDraw() {
		//The Data to Render
		float vertices[] = { -1.0f, -1.0f, 0.0f,
									0.0f, 1.0f, 0.0f,
									1.0f, -1.0f, 0.0f
		};

		unsigned int indices[] = { 0, 1, 2 };

		//Create vertex array with data
		VertexArray vao;
		VertexBuffer vbo(vertices, 9 * sizeof(GL_FLOAT), GL_STATIC_DRAW);
		VertexBufferLayout vbLayout;
		vbLayout.push<float>(3);
		vao.addBuffer(vbo, vbLayout);

		//Create Index Buffer
		IndexBuffer ibo(indices, 3, GL_STATIC_DRAW);

		//Create Shader
		Shader shader("Assets/Shaders/Basic.shader");
		shader.setUniformMat4f("u_MVP", glm::mat4(1));
		shader.setUniform4f("u_Color", 1.f, 0.f, 0.f, 1.f);

		m_Renderer.draw(vao, ibo, shader);
	}
}
