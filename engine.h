#ifndef STRAWX_ENGINE_CC_H
#define STRAWX_ENGINE_CC_H

#include "defines.hh"
#include "SDL2/SDL.h"

namespace strawx {

	class Engine final {
	public:
		STX_NODISCARD inline static Engine* GetInstance();

		STX_NODISCARD inline uint16_t GetRefreshRate();

		STX_NODISCARD inline SDL_Renderer* GetRenderer();

		STX_NODISCARD inline bool IsRunning();

		void Start();

		void Update(float dt);

		void Render();

		inline void Exit(bool state);

	private:
		Engine();
		~Engine();
	
	private:
		bool engine_state;
		uint16_t window_size[2];
		uint16_t refresh_rate;
		SDL_Window* window;
		SDL_Renderer* renderer;
	};

	STX_NODISCARD inline Engine* Engine::GetInstance()
	{
		static Engine Strawx;
		return &Strawx;
	}

	STX_NODISCARD inline uint16_t Engine::GetRefreshRate()
	{
		return this->refresh_rate;
	}

	STX_NODISCARD inline SDL_Renderer* Engine::GetRenderer()
	{
		return this->renderer;
	}

	STX_NODISCARD inline bool Engine::IsRunning() {
		return this->engine_state;
	}

	inline void Engine::Exit(bool state) {
		this->engine_state = state;
	}
	
}

#endif
