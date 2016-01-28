#include "stdafx.h"
#include "Player.h"
#include <SDL_image.h>

// Constructor
Player::Player() :CollisionResponder()
{
	
}

void Player::Init(SDL_Rect pRect, b2World *pWorld)
{

	mutex = SDL_CreateMutex();

	health = 5;

	myRect = pRect;
	spriteOffset = 32;
	//myBodyDef.type = b2_staticBody;
	myBodyDef.type = b2_dynamicBody;
	myBodyDef.position.Set(myRect.x + myRect.w*0.5f, myRect.y + myRect.h*0.5f);
	myBody = pWorld->CreateBody(&myBodyDef);

	myShape.SetAsBox(pRect.w / 2, pRect.h / 2);

	myBodyFixtureDef.shape = &myShape;
	myBodyFixtureDef.friction = 100;
	myBody->CreateFixture(&myBodyFixtureDef);

	source = { 0, 0, 32, 64 };

	playerSprite.Init("Assets/rightAnimation.png", pRect, source);
	playerSprite.SetOffset(16, 32);

	myBodyDef.userData = this;

	canJump = true;
	//Set sprite clips
	gSpriteClips[0].x = 0;
	gSpriteClips[0].y = 0;
	gSpriteClips[0].w = 60;
	gSpriteClips[0].h = 66;

	gSpriteClips[1].x = 60;
	gSpriteClips[1].y = 0;
	gSpriteClips[1].w = 60;
	gSpriteClips[1].h = 66;

	gSpriteClips[2].x = 120;
	gSpriteClips[2].y = 0;
	gSpriteClips[2].w = 60;
	gSpriteClips[2].h = 66;

	gSpriteClips[3].x = 180;
	gSpriteClips[3].y = 0;
	gSpriteClips[3].w = 60;
	gSpriteClips[3].h = 66;

	gSpriteClips[4].x = 240;
	gSpriteClips[4].y = 0;
	gSpriteClips[4].w = 60;
	gSpriteClips[4].h = 66;

	gSpriteClips[5].x = 300;
	gSpriteClips[5].y = 0;
	gSpriteClips[5].w = 60;
	gSpriteClips[5].h = 66;

	gSpriteClips[6].x = 360;
	gSpriteClips[6].y = 0;
	gSpriteClips[6].w = 60;
	gSpriteClips[6].h = 66;

	gSpriteClips[7].x = 420;
	gSpriteClips[7].y = 0;
	gSpriteClips[7].w = 60;
	gSpriteClips[7].h = 66;

	frame = 0;
}

//Doesnt work... Oh well... Who really cares?
void Player::Animate()
{
	//Current animation frame

	//Render current frame
	SDL_Rect currentClip = gSpriteClips[frame / 7];
	playerSprite.SetSourceRect(currentClip);

	++frame;

	if (frame / 7 > 7)
	{
		frame = 0;
	}
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

	b2Vec2 result;

	if (keys[SDL_SCANCODE_A]) {
		result = b2Vec2(-2, 0);
	}

	else if (keys[SDL_SCANCODE_D]) {
		result = b2Vec2(2, 0);
	}

	else if (keys[SDL_SCANCODE_W]) {
		result = b2Vec2(0, -2);
	}

	else if (keys[SDL_SCANCODE_S]) {
		result = b2Vec2(0, 2);
	}

	else if (!keys[SDL_SCANCODE_D] && !keys[SDL_SCANCODE_A] && !keys[SDL_SCANCODE_W] && !keys[SDL_SCANCODE_S])
	{
		myBody->SetLinearVelocity(b2Vec2(0, 0));
	}

	//lock
	if (SDL_LockMutex(mutex) == 0) {
		myBody->ApplyLinearImpulse(result, b2Vec2(0, 0), true);
		SDL_UnlockMutex(mutex);
	}
	//unlock
}

void Player::Draw()
{
	playerSprite.Draw();
	Animate();
}

void Player::Add_SubHealth(int amount)
{
	health += amount;
}

SDL_Rect Player::getRectangle()
{
	return myRect;
}

b2Body *Player::getBody()
{
	return myBody;
}

void Player::onBeginContact(CollisionResponder* other)
{
	std::cout << "enemy Collide begin" << std::endl;
	printf("++contact++");
}

void Player::onEndContact(CollisionResponder* other)
{
	std::cout << "enemy Collide end" << std::endl;
	printf("++contact++");
}

b2Vec2 Player::getPos() {
	return b2Vec2(myRect.x, myRect.y);
}