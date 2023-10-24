#include "input.h"

using namespace strawx;

Input::Input() 
{
	for (int i = 0; i < SDL_NUM_SCANCODES; ++i)
	{
		this->kstate.repeat[i] = 0;
		this->kstate.state[i] = 0;
		this->kstate.down[i] = 0;
		this->kstate.up[i] = 0;
	}
}
