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
private:
	int m_Width, m_Height;
	const Shader* m_Shader;
public :
	//Pass in the width and height of the window.
	Renderer(int width, int height);

	//OpenGL Coords are normalized btw -1 and 1, so we need to have a way to normalize pixel coordinates on the screen
	float pixelToNormX(int x);
	float pixelToNormY(int y);

	void clear();
	void setClearColor(float r, float g, float b, float a);
	void setShader(const Shader& shader);

	void drawRect(int x, int y, int w, int h);	
	void draw(const VertexArray& va, const IndexBuffer& ib);
	void draw(const VertexArray& va, const IndexBuffer& ib, const Shader& shader);
};