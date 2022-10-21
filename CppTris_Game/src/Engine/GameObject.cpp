#include "GameObject.h"

GameObject::GameObject(glm::vec3 position) :
	m_Position(position)
{
	start();
}

GameObject::GameObject(float x, float y, float z) :
	GameObject(glm::vec3(x, y, z ))
{
}

GameObject::GameObject(float x, float y) :
	GameObject(x, y, 0)
{
}

GameObject::GameObject() :
	GameObject(0, 0)
{
}

GameObject::~GameObject()
{
	onDestroy();
}

Shader* GameObject::getShader()
{
	//The default shader
	Shader* shader = new Shader("Assets/Shaders/Basic.shader");
	shader->setUniformMat4f("u_MVP", glm::mat4(1));
	shader->setUniform4f("u_Color", 1.f, 1.f, 1.f, 1.f);
	return shader;
}

glm::vec3& GameObject::position()
{
	return m_Position;
}
