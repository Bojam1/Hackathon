#include "stdafx.h"
#include "Player.h"
#include <SDL_image.h>

// Constructor
Player::Player()
{

}

void Player::Init(SDL_Rect pRect, b2World *pWorld)
{
	myRect = pRect;

	//myBodyDef.type = b2_staticBody;
	myBodyDef.type = b2_dynamicBody;
	myBodyDef.position.Set(pRect.x, pRect.y);
	myBody = pWorld->CreateBody(&myBodyDef);

	myShape.SetAsBox(pRect.w / 2, pRect.h / 2);

	myBodyFixtureDef.shape = &myShape;
	myBodyFixtureDef.friction = 100;
	myBody->CreateFixture(&myBodyFixtureDef);

	SDL_Rect source = { 0, 0, 32, 64 };

	playerSprite.Init("Assets/pablo-32x64.png", pRect, source);
	playerSprite.SetOffset(16, 32);

	canJump = true;
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
		myBody->SetTransform(b2Vec2(myBody->GetPosition().x - 0.75, myBody->GetPosition().y), 0);
	}

	if (keys[SDL_SCANCODE_D]) {
		myBody->SetTransform(b2Vec2(myBody->GetPosition().x + 0.75, myBody->GetPosition().y), 0);
	}

	if (keys[SDL_SCANCODE_W]) {
		myBody->SetTransform(b2Vec2(myBody->GetPosition().x, myBody->GetPosition().y - 0.75), 0);
	}

	if (keys[SDL_SCANCODE_S]) {
		myBody->SetTransform(b2Vec2(myBody->GetPosition().x, myBody->GetPosition().y + 0.75), 0);
	}


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