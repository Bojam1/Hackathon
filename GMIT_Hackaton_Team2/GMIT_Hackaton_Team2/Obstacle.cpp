
#include "stdafx.h"
#include "Obstacle.h"
#include "Renderer.h"
#include <SDL_image.h>

Obstacle::Obstacle()
{
}

Obstacle::Obstacle(SDL_Rect pRect, b2World *wWorld, string path)
{

	myRect = pRect;

	// Define the ground body.
	myBodyDef.position.Set(pRect.x + pRect.w / 2 - 17, pRect.y + pRect.h / 2 - 15);
	myBodyDef.type = b2_staticBody;

	// Define the ground box shape.
	// The extents are the half-widths of the box.
	myShape.SetAsBox(pRect.w / 2 - 10, pRect.h / 2);
	myBodyFixtureDef.shape = &myShape;

	// Call the body factory which allocates memory for the ground body
	// from a pool and creates the ground box shape (also from a pool).
	// The body is also added to the world.
	myBody = wWorld->CreateBody(&myBodyDef);
	SDL_Rect source = { 0,0,32,32 };

	// Add the ground fixture to the ground body.
	myBody->CreateFixture(&myBodyFixtureDef);
	sprite.Init(path, pRect, source);
	sprite.SetOffset(16, 16);
}

void Obstacle::Draw()
{
	sprite.Draw();
}
