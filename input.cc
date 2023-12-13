#include "input.h"

using namespace strawx;

Input::Input() 
{
	kstate.repeat.fill(0);
	kstate.state.fill(0);
	kstate.down.fill(0);
	kstate.up.fill(0);
}
