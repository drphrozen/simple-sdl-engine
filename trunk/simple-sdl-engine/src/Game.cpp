#if defined(__WIN32__)
#include <windows.h>
#endif

#include <SDL/SDL.h>
#include <SDL/SDL_timer.h>
#include <SDL/SDL_video.h>

#include "Sprite.h"
#include "Engine.h"

enum DogDirection {
	DOG_Direction_Right = 0,
	DOG_Direction_Left = 8,
};

class TestEngine : public Engine {
private:
	Sprite dog;
	int count;
	SDL_Event event;
	DogDirection direction;
	bool isKeyDown;

public:
	TestEngine(int width, int height) :
		Engine(width, height), dog("dog.png", 16), count(0), direction(DOG_Direction_Right), isKeyDown(false)
	{
		SDL_FillRect(screen, &screen->clip_rect, background);
		SDL_UpdateRects(screen, 1, &screen->clip_rect);
	}

	Uint32 tick(Uint32 interval)
	{
		static int tick = -1;
		static int frame = 0;
		SDL_FillRect(screen, dog.getRect(), background);
		SDL_UpdateRects(screen, 1, dog.getRect());
		if(isKeyDown && ++tick%10 == 0)
			dog.setIndex((++frame%2) + direction);
		dog.setPosition(event.motion.x, event.motion.y);
		dog.draw();
		return interval;
	}

	void HandleEvent(const SDL_Event& e)
	{
		switch (e.type) {
			case SDL_MOUSEMOTION:
				event = e;
				break;
			case SDL_QUIT:
				stop();
				break;
			case SDL_KEYDOWN:
				isKeyDown = true;
				switch(e.key.keysym.sym) {
				case SDLK_LEFT:
					direction = DOG_Direction_Left;
					break;
				case SDLK_RIGHT:
					direction = DOG_Direction_Right;
					break;
				case SDLK_UP:

					break;
				case SDLK_DOWN:

					break;
				case SDLK_ESCAPE:
					stop();
					break;
				default:
					break;
				}
				break;
			case SDL_KEYUP:
				isKeyDown = false;
				break;
			default:
				break;
		}
	}
};
#if defined(__WIN32__)
int WINAPI WinMain(
    HINSTANCE hInstance,
    HINSTANCE hPrevInstance,
    LPSTR lpCmdLine,
    int nCmdShow)
#else
int main(int argc, char **argv)
#endif
{
	TestEngine engine(640, 480);
	engine.start(30);
	return 0;
}

