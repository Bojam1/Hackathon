#ifndef PLAYER_H
#define PLAYER_H

#include <iostream> 
#include "sdl.h"
#include "Box2D\Box2D.h"
#include "InputHandler.h"
#include "Renderer.h"
#include "Sprite.h"

class Player
{
public:
	Player();

	void Init(SDL_Rect, b2World*);
	bool Update();
	void Draw();
	void Move(InputHandler & input);
	void Jump();

	SDL_Rect getRectangle();
	b2Body* getBody();

private:
	SDL_Rect myRect;

	b2BodyDef myBodyDef;
	b2Body* myBody;
	b2PolygonShape myShape;
	b2FixtureDef myBodyFixtureDef;

	Sprite playerSprite;

	bool canJump;
};

#endif