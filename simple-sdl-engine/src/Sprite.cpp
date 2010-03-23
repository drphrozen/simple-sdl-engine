/*
 * Sprite.cpp
 *
 *  Created on: 22/03/2010
 *      Author: drphrozen
 */

#include "Sprite.h"

#include "SDL/SDL_image.h"

SDL_Surface* Sprite::screen = 0;

Sprite::Sprite(SDL_Surface *surface, int indexes) :
	indexes(indexes),
	surface(surface),
	width(surface->w/indexes),
	height(surface->h)
{
	position.w = width;
	position.h = height;
	setPosition(0, 0);
	setIndex(0);
}

Sprite::Sprite(const char* image_path, int indexes) :
	indexes(indexes),
	surface(IMG_Load(image_path)),
	width(surface->w/indexes),
	height(surface->h)
{
	position.w = width;
	position.h = height;
	setPosition(0, 0);
	setIndex(0);
}

Sprite::~Sprite()
{
	SDL_FreeSurface(surface);
}

void Sprite::setIndex(int i) {
	index = i;
	SDL_Rect rect = { index*width, 0, width, height };
	SDL_SetClipRect(surface, &rect);
}

int Sprite::getIndex() {
	return index;
}

void Sprite::setPosition(int x, int y)
{
	position.x = x;
	position.y = y;
}

SDL_Rect* Sprite::getRect()
{
	return &position;
}

void Sprite::move(int x, int y)
{
	position.x += x;
	position.y += y;
}

void Sprite::draw()
{
	SDL_BlitSurface(surface, &surface->clip_rect, Sprite::screen, &position);
	SDL_UpdateRects(Sprite::screen, 1, &position);
}
