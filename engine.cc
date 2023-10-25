#include "engine.h"

#define SDL_MAIN_HANDLED
#include "SDL2/SDL.h"

namespace {

	using namespace strawx;

	struct Engine {
		Engine(const int width, const int height);
		~Engine();

		SDL_Window* window;
		SDL_Renderer* renderer;
		SDL_Event event;

		uint8_t engine_state;
		uint16_t refresh_rate;
	};

}

KeyboardStates* strawx::get_kstate(Input* inst)
{
	return &inst->kstate;
}

int main(int argc, char** argv)
{
	
	Engine strawx{ 1280, 720 };

	Game::GetInstance()->Start();

	auto& [repeat, state, down, up] = *get_kstate(Input::GetInstance());

	while (strawx.engine_state) {
		for (int i = 0; i < SDL_NUM_SCANCODES; ++i) {
			down[i] = up[i] = 0;
		}
		while (SDL_PollEvent(&strawx.event))
		{
			switch (strawx.event.type)
			{
			case SDL_QUIT:
				strawx.engine_state = false;
				break;
			
			case SDL_KEYDOWN:
				state[strawx.event.key.keysym.scancode] = 1;
				down[strawx.event.key.keysym.scancode] = 1;
				break;

			case SDL_KEYUP:
				state[strawx.event.key.keysym.scancode] = 0;

				repeat[strawx.event.key.keysym.scancode] = 0;
				up[strawx.event.key.keysym.scancode] = 1;
				break;
			}
		}

		if (Input::GetInstance()->IsKeyPressed(SDL_SCANCODE_ESCAPE))
			strawx.engine_state = false;
		
		Game::GetInstance()->Update(strawx.refresh_rate);


		SDL_SetRenderDrawColor(strawx.renderer, 0, 0, 0, 255);
		SDL_RenderClear(strawx.renderer);

		Game::GetInstance()->Render();
		
		SDL_RenderPresent(strawx.renderer);
	}

	return EXIT_SUCCESS;
}

Engine::Engine(const int width, const int height) :
	window{ nullptr }, renderer{ nullptr }, event{ },
	engine_state{ false }, refresh_rate{ 0 }
{
	SDL_Log("Constructing Engine");

	if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_TIMER) < 0)
	{
		SDL_Log("Init Error: %s", SDL_GetError());
	}

	window = SDL_CreateWindow (
		"Strawx Engine",
		SDL_WINDOWPOS_CENTERED,
		SDL_WINDOWPOS_CENTERED,
		width,
		height,
		0
	);

	if (!window) {
		SDL_Log("Init Error: %s", SDL_GetError());
	}

	renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_PRESENTVSYNC);

	if (!renderer) {
		SDL_Log("Init Error %s", SDL_GetError());
	}

	SDL_DisplayMode mode;
	SDL_GetDisplayMode(SDL_GetWindowDisplayIndex(window), 0, &mode);

	refresh_rate = mode.refresh_rate;

	// if everything went OK
	engine_state = true;

}

Engine::~Engine()
{
	if (window) SDL_DestroyWindow(window);
	
	if (renderer) SDL_DestroyRenderer(renderer);
	
	window = nullptr;
	renderer = nullptr;

	SDL_Quit();

	SDL_Log("Destructing Engine");
}
