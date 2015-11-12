#include "stdafx.h"
#include "Player.h"
#include <SDL_image.h>

// Constructor
Player::Player() : MAX_AMMO(10), ammo(MAX_AMMO)
{
}

void Player::Init(SDL_Rect pRect, b2World *pWorld)
{
	myRect = pRect;
	spriteOffset = 32;
	//myBodyDef.type = b2_staticBody;
	myBodyDef.type = b2_dynamicBody;
	myBodyDef.position.Set(pRect.x, pRect.y);
	myBody = pWorld->CreateBody(&myBodyDef);
	myBodyDef.userData = this;
	myShape.SetAsBox(pRect.w / 2, pRect.h / 2);

	myBodyFixtureDef.shape = &myShape;
	myBodyFixtureDef.friction = 100;
	myBody->CreateFixture(&myBodyFixtureDef);

	source = { 0, 0, 32, 64 };

	playerSprite.Init("Assets/leftMovement.png", pRect, source);
	playerSprite.SetOffset(16, 32);

	canJump = true;
}

//Doesnt work... Oh well... Who really cares?
void Player::Animate()
{
	spriteOffset += 32;

	if (spriteOffset > 96)
		spriteOffset = 32;

	source = { 0,0, spriteOffset, 64 };
}

bool Player::Update()
{

	myRect.x = myBody->GetPosition().x;
	myRect.y = myBody->GetPosition().y;

	// Can jump if y-velocity is 0
	if (myBody->GetLinearVelocity().y == 0)
	{
		canJump = true;
		myBodyFixtureDef.friction = 100;
	}
	else
	{
		canJump = false;
		myBodyFixtureDef.friction = 0;
	}

	playerSprite.SetPosition(myBody->GetPosition().x, myBody->GetPosition().y);


	return true;
}

void Player::Move(InputHandler & input)
{
	const Uint8 *keys = SDL_GetKeyboardState(NULL);

	if (keys[SDL_SCANCODE_A]) {
		//myBody->SetTransform(b2Vec2(myBody->GetPosition().x - 0.75, myBody->GetPosition().y), 0);
		//myBody->SetLinearVelocity(b2Vec2(-2, 0));
		Animate();
		myBody->ApplyLinearImpulse(b2Vec2(-2, 0), b2Vec2(0, 0), true);
	}

	if (keys[SDL_SCANCODE_D]) {
		//myBody->SetLinearVelocity(b2Vec2(2, 0));
		//myBody->SetTransform(b2Vec2(myBody->GetPosition().x + 0.75, myBody->GetPosition().y), 0);
		myBody->ApplyLinearImpulse(b2Vec2(2, 0), b2Vec2(0, 0), true);
	}

	if (keys[SDL_SCANCODE_W]) {
		//myBody->SetLinearVelocity(b2Vec2(0, -2));
		//myBody->SetTransform(b2Vec2(myBody->GetPosition().x, myBody->GetPosition().y - 0.75), 0);
		myBody->ApplyLinearImpulse(b2Vec2(0, -2), b2Vec2(0, 0), true);
	}

	if (keys[SDL_SCANCODE_S]) {
		//myBody->SetLinearVelocity(b2Vec2(0, 2));
		//myBody->SetTransform(b2Vec2(myBody->GetPosition().x, myBody->GetPosition().y + 0.75), 0);
		myBody->ApplyLinearImpulse(b2Vec2(0, 2), b2Vec2(0, 0), true);
	}

	if (!keys[SDL_SCANCODE_D] && !keys[SDL_SCANCODE_A] && !keys[SDL_SCANCODE_W] && !keys[SDL_SCANCODE_S])
	{
		myBody->SetLinearVelocity(b2Vec2(0, 0));
	}

	//Fire control
	l = keys[SDL_SCANCODE_LEFT];
	r = keys[SDL_SCANCODE_RIGHT];
	u = keys[SDL_SCANCODE_UP];
	d = keys[SDL_SCANCODE_DOWN];
}

void Player::Draw()
{
	playerSprite.Draw();
}

SDL_Rect Player::getRectangle()
{
	return myRect;
}

b2Body *Player::getBody()
{
	return myBody;
}

b2Vec2 Player::getPosition()
{
	return myBody->GetPosition();
}

void Player::onBeginContact(CollisionResponder * other)
{
}

void Player::onEndContact(CollisionResponder * other)
{
}
