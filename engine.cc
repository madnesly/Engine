#define SDL_MAIN_HANDLED
#include "engine.h"

using namespace strawx;

namespace { SDL_Event engine_event { }; }

int main() {

	Engine::GetInstance()->Start();

	STX_LOG("Refresh Rate: %d", Engine::GetInstance()->GetRefreshRate());

	while (Engine::GetInstance()->IsRunning()) {

		while (SDL_PollEvent(&engine_event))
		{
			switch (engine_event.type)
			{
			case SDL_QUIT:
				Engine::GetInstance()->Exit(false);
				break;
			
			case SDL_KEYDOWN:
				
				break;
			}
		}
		
		Engine::GetInstance()->Update(60.0f);

		SDL_SetRenderDrawColor(Engine::GetInstance()->GetRenderer(), 0, 0, 0, 255);
		SDL_RenderClear(Engine::GetInstance()->GetRenderer());

		Engine::GetInstance()->Render();

		SDL_RenderPresent(Engine::GetInstance()->GetRenderer());
	}

	return EXIT_SUCCESS;
}

Engine::Engine()
{
	engine_state = false;
	window_size[0] = 720;
	window_size[1] = 430;

	if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_TIMER) < 0)
	{
		STX_LOG("Init Error: %s", SDL_GetError());
	}

	window = SDL_CreateWindow("Strawx Engine", SDL_WINDOWPOS_CENTERED,
		SDL_WINDOWPOS_CENTERED, window_size[0], window_size[1], 0);

	if (!window) {
		STX_LOG("Init Error: %s", SDL_GetError());
	}

	renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_PRESENTVSYNC);

	if (!renderer) {
		STX_LOG("Init Error %s", SDL_GetError());
	}

	SDL_DisplayMode mode;
	SDL_GetDisplayMode(SDL_GetWindowDisplayIndex(window), 0, &mode);

	refresh_rate = mode.refresh_rate;

	STX_LOG("Constructing Engine");

	// if everything went OK
	engine_state = true;

}

Engine::~Engine()
{
	if (window) {
		SDL_DestroyWindow(window);
		window = nullptr;
	}

	if (renderer) {
		SDL_DestroyRenderer(renderer);
		renderer = nullptr;
	}

	STX_LOG("Destructing Engine");
}
