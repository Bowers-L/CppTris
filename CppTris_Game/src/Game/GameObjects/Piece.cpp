#include "Piece.h"

Piece::Piece(int x, int y) :
	GameObject(x, y)
{
}

Piece::Piece() :
	Piece(0, 0)
{
}

void Piece::draw() {
	//Create Shader
	Shader shader("Assets/Shaders/Basic.shader");
	shader.setUniformMat4f("u_MVP", glm::mat4(1));
	shader.setUniform4f("u_Color", 1.f, 0.f, 0.f, 1.f);

	Renderer::setShader(shader);
	Renderer::drawRect(m_Position.x, m_Position.y, 100, 100);
}