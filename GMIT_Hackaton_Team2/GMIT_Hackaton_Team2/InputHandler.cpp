#include "stdafx.h"
#include <InputHandler.h>

bool InputHandler::instanceFlag = false;
InputHandler* InputHandler::instance = NULL;

InputHandler* InputHandler::GetInstance()
{
	if (!instanceFlag)
	{
		instance = new InputHandler;
		instanceFlag = true;
		return instance;
	}
	else
	{
		return instance;
	}
}

bool InputHandler::CheckInput(SDL_Keycode key, SDL_Event event) {
		if (event.key.keysym.sym == key)
			return true;
		else
			return false;
}