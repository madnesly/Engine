#ifndef STRAWX_ENGINE_GAME_H
#define STRAWX_ENGINE_GAME_H

#include "input.h"

namespace strawx
{
	struct Game {
		[[nodiscard]] 
		static inline Game* GetInstance()
		{
			static Game inst;
			return &inst;
		}

		void Start();

		void Update(float dt);

		void Render();

	private:
		Game() = default;
		~Game() = default;
	};

}

#endif // STRAWX_ENGINE_GAME_H
