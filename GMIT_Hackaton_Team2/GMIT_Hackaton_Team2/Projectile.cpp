#include "stdafx.h"
#include "Projectile.h"
#include "SDL\include\SDL2_gfxPrimitives.h"

Projectile::Projectile(b2World &world, b2Vec2 position, b2Vec2 direction) : origin_(position), direction_(direction), alive_(true)
{
	geometry_.x = position.x;
	geometry_.y = position.y;
	geometry_.w = SIZE;
	geometry_.h = SIZE;

	direction_.Normalize();
	
	//Define a b2body
	b2BodyDef bodyDef;
	bodyDef.type = b2_dynamicBody;
	bodyDef.position = b2Vec2(position.x, position.y);
	bodyDef.userData = this;
	bodyDef.bullet = true;
	//Ask the b2Worldto create our body
	boxBody_ = world.CreateBody(&bodyDef);

	//Define the shape of the body
	b2PolygonShape shape;
	shape.SetAsBox(SIZE * 0.5f, SIZE * 0.5f);
	boxBody_->CreateFixture(&shape, 0.0f);
	boxBody_->GetFixtureList()->SetFriction(0.0f);
	boxBody_->GetFixtureList()->SetRestitution(0.0f);

	boxBody_->SetGravityScale(0.0f);

	speed_ = 10;
}

b2Vec2 Projectile::GetPosition() const
{
	return b2Vec2(geometry_.x, geometry_.y);
}

float Projectile::GetHeight() const
{
	return geometry_.h;
}

float Projectile::GetWidth() const
{
	return geometry_.w;
}

void Projectile::Update()
{
	b2Vec2 movement = direction_;
	
	movement *= speed_;

	boxBody_->SetLinearVelocity(movement);
	
	geometry_.x = boxBody_->GetPosition().x;
	geometry_.y = boxBody_->GetPosition().y;

	sprite_->SetPosition(geometry_.x, geometry_.y);
}

void Projectile::Draw()
{
	sprite_->Draw();
}

void Projectile::Init(std::string path)
{
	SDL_Rect tempSRC{ 0, 0, SIZE, SIZE };
	sprite_ = new Sprite();
	sprite_->Init(path, geometry_, tempSRC);
}

bool Projectile::isAlive() const
{
	return alive_;
}

bool Projectile::operator=(Projectile other)
{
	return alive_ == other.isAlive();
}

void Projectile::onBeginContact(CollisionResponder * other)
{
}

void Projectile::onEndContact(CollisionResponder * other)
{
}
