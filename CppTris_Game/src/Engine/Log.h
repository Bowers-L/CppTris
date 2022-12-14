#pragma once

#include <SDL.h>

#define DEBUG_LOG(x, ...) SDL_LogMessage(SDL_LOG_CATEGORY_APPLICATION, SDL_LOG_PRIORITY_INFO, x, __VA_ARGS__)
#define DEBUG_LOG_WARNING(x, ...) SDL_LogMessage(SDL_LOG_CATEGORY_APPLICATION, SDL_LOG_PRIORITY_WARN, x, __VA_ARGS__)
#define DEBUG_LOG_ERROR(x, ...) SDL_LogMessage(SDL_LOG_CATEGORY_APPLICATION, SDL_LOG_PRIORITY_ERROR, x, __VA_ARGS__)
#define DEBUG_LOG_CRITICAL(x, ...) SDL_LogMessage(SDL_LOG_CATEGORY_APPLICATION, SDL_LOG_PRIORITY_CRITICAL, x, __VA_ARGS__)

#define ASSERT(x) if (!(x)) __debugbreak();
#define SDL_CALL(x)		if (x < 0) {\
							SDLLogError(__FILE__, __LINE__);\
						};

#define GL_CALL(x)		GLClearError();\
						x;\
						ASSERT(GLLogCall(#x, __FILE__, __LINE__))

void SDLLogError(const char* file, int line);
bool GLLogCall(const char* function, const char* file, int line);
void GLClearError();