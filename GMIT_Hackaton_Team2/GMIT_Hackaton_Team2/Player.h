#ifndef PLAYER_H
#define PLAYER_H

#include <iostream> 
#include "sdl.h"
#include "Box2D\Box2D.h"
#include "InputHandler.h"
#include "Renderer.h"
#include "Sprite.h"
#include "CollisionResponder.h"
#include <MyContactListener.h>

class Player : public CollisionResponder
{
public:
	Player();

	void Init(SDL_Rect, b2World*);
	bool Update();
	void Draw();
	void Move(InputHandler & input);
	void Animate();
	void Add_SubHealth(int amount);

	SDL_Rect getRectangle();
	b2Body* getBody();
	b2Vec2 getPos();

	//needed to override the contact classes in the collision reponder
	virtual void onBeginContact(CollisionResponder* other) override;
	virtual void onEndContact(CollisionResponder* other) override;

private:
	int health;
	SDL_Rect myRect;
	SDL_Rect source;
	int spriteOffset;
	b2BodyDef myBodyDef;
	b2Body* myBody;
	b2PolygonShape myShape;
	b2FixtureDef myBodyFixtureDef;

	Sprite playerSprite;

	bool canJump;
};

#endif