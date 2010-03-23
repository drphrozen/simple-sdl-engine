/*
 * Engine.cpp
 *
 *  Created on: 23/03/2010
 *      Author: drphrozen
 */

#include "Engine.h"
#include "GameException.h"

#include <SDL/SDL.h>

#include <iostream>
using std::endl;

#include <sstream>
using std::ostringstream;

Engine* Engine::engine = 0;
TickFunctionPtr Engine::tickPtr = 0;

Engine::Engine(int width, int height)
	: done(true) {
	/* Initialize SDL */
	if (SDL_Init(SDL_INIT_TIMER | SDL_INIT_VIDEO) < 0) {
		ostringstream stream;
		stream << "Couldn't initialize SDL: " << SDL_GetError() << endl;
		throw GameException(stream.str());
	}

	/* Set video mode */
	screen = SDL_SetVideoMode(width, height, 0, SDL_SWSURFACE | SDL_ANYFORMAT);
	if (!screen) {
		ostringstream stream;
		stream << "Couldn't set " << width << "x" << height << " video mode: %s" << SDL_GetError() << endl;
		throw GameException(stream.str());
	}

	Sprite::screen = screen;

	// TODO: move
	background = SDL_MapRGB(screen->format, 0x99, 0xD9, 0xEA);

	engine = this;
	tickPtr = &Engine::tick;
}

Uint32 Engine::tick_wrapper(Uint32 interval) {
	return (Engine::engine->*tickPtr)(interval);
}


void Engine::start(int fps) {
	done = false;
	SDL_SetTimer((int)(1000.0f/fps), &Engine::tick_wrapper);
	SDL_Event event;
	while (!done) {
		while (SDL_PollEvent(&event)) {
			HandleEvent(event);
		}
	}
}

void Engine::stop() {
	done = true;
}

Engine::~Engine() {
}
