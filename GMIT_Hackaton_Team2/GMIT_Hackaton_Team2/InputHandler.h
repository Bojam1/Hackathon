#pragma once
#ifndef INPUTHANDLER_H
#define INPUTHANDLER_H

#include <SDL.h>

class InputHandler {
public:
	static InputHandler* GetInstance();
	~InputHandler()
	{
		instanceFlag = false;
	}
	bool CheckInput(SDL_Keycode key, SDL_Event event);
private:
	static bool instanceFlag;
	static InputHandler* instance;
	//SDL_Event event;
};

#endif