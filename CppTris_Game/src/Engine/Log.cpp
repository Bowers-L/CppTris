#pragma once

#include "Log.h"

#include <glad/glad.h>

void SDLLogError(const char* file, int line) {
	DEBUG_LOG_ERROR("[SDL Error] (%s) at %s:%d", SDL_GetError(), file, line);
}

void GLClearError() {
	while (glGetError() != GL_NO_ERROR);
}

bool GLLogCall(const char* function, const char* file, int line) {
	if (GLenum error = glGetError()) {
		DEBUG_LOG_ERROR("[OpenGL Error] (%s) %s at %s:%d", error, file, line);
		return false;
	}

	return true;
}