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

glm::vec3& GameObject::position()
{
	return m_Position;
}
