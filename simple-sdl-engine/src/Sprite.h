/*
 * Sprite.h
 *
 *  Created on: 22/03/2010
 *      Author: drphrozen
 */

#ifndef SPRITE_H_
#define SPRITE_H_

#include "SDL/SDL_video.h"
#include "SDL/SDL_image.h"

#include "Position.h"

class Sprite {
	friend class Engine;
public:
	Sprite(SDL_Surface *surface, int indexes = 1);
	Sprite(const char *image_path, int indexes = 1);
	virtual ~Sprite();

	/**
	 * Move this sprite to an absolute position on the screen.
	 * @param x
	 * @param y
	 */
	void setPosition(int x, int y);

	/**
	 * Move this sprite to a relative position on the screen.
	 * @param x
	 * @param y
	 */
	void move(int x, int y);

	SDL_Rect* getRect();

	void setIndex(int i);
	int getIndex();

	void draw();

public:
	const int indexes;

private:
	static SDL_Surface* screen;
	SDL_Surface *surface;
	const int width, height;
	SDL_Rect position;
	int index;
};

#endif /* SPRITE_H_ */
