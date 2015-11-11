#ifndef _BUTTON_H_
#define _BUTTON_H_

#include <iostream>
#include <stdio.h>

#include <windows.h>

#include <random>
#include <string>
#include <cmath>

#include <fstream>

#include <SDL.h>
#include "Sprite.h"
#include "Renderer.h"

static class Button
{
private:
	SDL_Rect rect;
	Sprite* m_sprite;
	
public:

	Button();
	~Button()
	{
		delete m_sprite;
	}
	void Init(SDL_Rect pos,  std::string path);
	bool IsClicked(int x, int y);
	void Draw();
	

};
#endif