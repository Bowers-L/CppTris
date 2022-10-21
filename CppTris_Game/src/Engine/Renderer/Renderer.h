#pragma once

#include <glad/glad.h>

#include "Engine/Log.h"

#include "buffers/Buffers.h"

#include "Shader.h"

#define GLCall(x) GLClearError();\
	x;\
	ASSERT(GLLogCall(#x, __FILE__, __LINE__))

void GLClearError();
bool GLLogCall(const char* function, const char* file, int line);

class Renderer {
public :
	static void clear();
	static void setClearColor(float r, float g, float b, float a);

	static void draw(const VertexArray& va, const IndexBuffer& ib, const Shader& shader);
};