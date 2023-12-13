#ifndef STRAWX_ENGINE_INPUT_H
#define STRAWX_ENGINE_INPUT_H

#include "SDL2/SDL_scancode.h"
#include <array>

namespace strawx {
	
	struct KeyboardStates 
	{
		std::array<Uint8, SDL_NUM_SCANCODES> repeat;
		std::array<Uint8, SDL_NUM_SCANCODES> state;
		std::array<Uint8, SDL_NUM_SCANCODES> down;
		std::array<Uint8, SDL_NUM_SCANCODES> up;
	};

	class Input final
	{
	public:
		[[nodiscard]] inline static Input& GetInstance()
		{
			static Input instance;
			return instance;
		}

		[[nodiscard]] inline bool IsKeyDown(SDL_Scancode scancode)
		{
			return kstate.state[scancode];
		}

		[[nodiscard]] inline bool IsKeyUp(SDL_Scancode scancode)
		{
			return kstate.up[scancode];
		}

		[[nodiscard]] inline bool IsKeyPressed(SDL_Scancode scancode)
		{
			if (kstate.down[scancode] && (!kstate.repeat[scancode])) {
				kstate.repeat[scancode] = 1;
				return true;
			}
			return false;
		}

	private:
		KeyboardStates kstate;
		friend KeyboardStates& get_kstate(Input& inst);

	private:
		Input();
		~Input() = default;
	};
}

#endif
