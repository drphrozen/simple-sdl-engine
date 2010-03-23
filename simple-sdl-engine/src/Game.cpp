#include <SDL/SDL.h>
#include <SDL/SDL_timer.h>
#include <SDL/SDL_video.h>

#include "Sprite.h"
#include "Engine.h"

class TestEngine : public Engine {
private:
	Sprite dog;
	int count;
	SDL_Event event;
public:
	TestEngine(int width, int height) :
		Engine(width, height), dog("dog.png", 8), count(0)
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
		if(++tick%10 == 0)
			dog.setIndex(++frame%2);
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
			case SDL_KEYDOWN:
				stop();
				break;
			default:
				break;
		}
	}
};

int main(int argc, char **argv)
{
	TestEngine engine(640, 480);
	engine.start(30);
	return 0;
}

