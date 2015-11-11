#include "stdafx.h"

#include <SDL.h>
#undef main
#include "Box2D\Box2D.h"

int main()
{
	SDL_Rect rect = { 0, 0, 10, 10 };
	b2Vec2 vector = b2Vec2(100, 100);
	system("Pause");
	return 0;
}

