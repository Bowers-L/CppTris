#pragma once

#include "Renderer/Renderer.h"

#include <glm/glm.hpp>
#include <SDL.h>

class GameObject
{
protected:
	glm::vec3 m_Position;
public:
	GameObject(glm::vec3 position);
	GameObject(float x, float y, float z);
	GameObject(float x, float y);
	GameObject();

	~GameObject();

	virtual void start() {}
	virtual void update() {}
	virtual void draw() {}
	virtual void onDestroy() {}

	virtual Shader* getShader();

	glm::vec3& position();
};