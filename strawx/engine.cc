#include "engine.h"
#include "core/common.hh"

#define SDL_MAIN_HANDLED
#include "SDL2/SDL.h"

namespace {

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

namespace strawx 
{
	KeyboardStates& get_kstate(Input& inst)	
	{ 
		return inst.kstate; 
	}
}

int main(int argc, char** argv)
{
	using namespace strawx;
 
	Engine core{ 1280, 720 };

	texture_impl::set_renderer(core.renderer);

	Game::Start();

	auto& [repeat, state, down, up] = get_kstate(Input::GetInstance());

	constexpr float fixed_dt{ 1000.0f / 90.0f };

	float FPS{ }, elapsed{ };
	float current{ }, accumulator{ };

	float previous = static_cast<float>(SDL_GetTicks64());

	while (core.engine_state) {
		
		down.fill(0); up.fill(0);

		FPS += 1.0f;

		current = static_cast<float>(SDL_GetTicks64());
		elapsed = current - previous;
		previous = current;

		accumulator += elapsed;

		// calculates Frames Per Second
		if (static float seconds{ 1.0f }; (SDL_GetTicks64() / 1000.0f) > seconds) {
			SDL_Log("FPS: %f", FPS); FPS = 0.0f;
			seconds += 1.0f;
		}

		while (SDL_PollEvent(&core.event))
		{
			switch (core.event.type)
			{
			case SDL_QUIT:
				core.engine_state = false;
				break;
			
			case SDL_KEYDOWN:
				state[core.event.key.keysym.scancode] = 1;
				down[core.event.key.keysym.scancode] = 1;
				break;

			case SDL_KEYUP:
				state[core.event.key.keysym.scancode] = 0;

				repeat[core.event.key.keysym.scancode] = 0;
				up[core.event.key.keysym.scancode] = 1;
				break;
			}
		}

		if (Input::GetInstance().IsKeyPressed(SDL_SCANCODE_ESCAPE))
			core.engine_state = false;

		while (accumulator >= fixed_dt) {
			Game::Update(fixed_dt);
			accumulator -= fixed_dt;
		}

		SDL_SetRenderDrawColor(core.renderer, 0, 0, 0, 255);
		SDL_RenderClear(core.renderer);

		Game::Render();
		
		SDL_RenderPresent(core.renderer);
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

	SDL_Log("Refresh Rate: %d", refresh_rate);

	// if everything went OK
	engine_state = true;

}

Engine::~Engine()
{
	texture_impl::clear_textures();

	if (renderer) SDL_DestroyRenderer(renderer);
	SDL_Log("destroying renderer [%s]", SDL_GetError());
	
	if (window) SDL_DestroyWindow(window);
	SDL_Log("destroying window [%s]", SDL_GetError());

	renderer = nullptr;
	window = nullptr;

	SDL_Quit();

	SDL_Log("Destructing Engine");
}
