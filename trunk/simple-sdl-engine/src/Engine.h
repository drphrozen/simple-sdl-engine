/*
 * Engine.h
 *
 *  Created on: 23/03/2010
 *      Author: drphrozen
 */

#ifndef ENGINE_H_
#define ENGINE_H_

#include "Sprite.h"

#include <SDL/SDL.h>

#include <vector>
using std::vector;

class Engine;

typedef Uint32 (Engine::*TickFunctionPtr)(Uint32);

class Engine {
public:
	Engine(int width, int height);
	virtual ~Engine();
	void start(int fps);
	void stop();
	virtual Uint32 tick(Uint32 interval) = 0;
	virtual void HandleEvent(const SDL_Event&) = 0;

private:
	static Uint32 tick_wrapper(Uint32 interval);
	static Engine* engine;
	static TickFunctionPtr tickPtr;

protected:
	vector<Sprite*> sprites;
	SDL_Surface* screen;
	SDL_Surface* buffer;
	Uint32 background;

private:
	volatile bool done;
};

#endif /* ENGINE_H_ */
