#ifndef OBSTACLE_H
#define OBSTACLE_H

#include <iostream> 
#include "sdl.h"
#include "Box2D\Box2D.h"
//#include "KeyboardInputs.h"
#include "Renderer.h"
#include "Sprite.h"
#include <string>
using namespace std;

class Obstacle
{
public:
	Obstacle();
	Obstacle(SDL_Rect, b2World*, string );
	b2Body* myBody;
	Obstacle(SDL_Rect, string);
	// Public member functions
	void Draw();
	//SDL_Rect getRectangle();
private:
	b2BodyDef myBodyDef;
	b2FixtureDef myBodyFixtureDef;
	Sprite sprite;
	b2PolygonShape myShape;
	SDL_Texture* myTexture;
	//end of platform Sensors
	SDL_Rect gSpriteClips;
	SDL_Rect myRect;
};

#endif#pragma once
