#pragma once

#include "Log.h"

void SDLLogCall(const char* file, int line) {
	DEBUG_LOG_ERROR("[SDL Error] (%s) at %s:%d", SDL_GetError(), file, line);
}