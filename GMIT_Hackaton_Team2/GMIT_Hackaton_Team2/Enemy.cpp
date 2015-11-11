#include "stdafx.h"
#include "Enemy.h"

Enemy::Enemy(b2World &world, b2Vec2 const &position, int width, int height, Direction dir) :CollisionResponder(){
	//Define a b2body
	b2BodyDef bodyDef;
	bodyDef.type = b2_dynamicBody;
	bodyDef.position = b2Vec2(position.x, position.y);
	bodyDef.userData = this;
	//Ask the b2Worldto create our body
	boxBody = world.CreateBody(&bodyDef);

	//Define the shape of the body
	b2PolygonShape shape;
	shape.SetAsBox(width * 0.5f, height * 0.5f);
	boxBody->CreateFixture(&shape, 0.0f);
	boxBody->GetFixtureList()->SetFriction(0.0f);
	boxBody->GetFixtureList()->SetRestitution(0.0f);

	boxBody->SetGravityScale(0.0f);
}

Enemy::~Enemy() {

}

void Enemy::Move(Direction dir) {
	switch (dir)
	{
	case Enemy::Up:
		geometry.y--;
		break;
	case Enemy::Down:
		geometry.y++;
		break;
	case Enemy::Left:
		geometry.x--;
		break;
	case Enemy::Right:
		geometry.x++;
		break;
	default:
		std::cout << "direction not valid" << std::endl;
		break;
	}
}

b2Vec2 Enemy::GetPosition() const {
	return b2Vec2(geometry.x, geometry.y);
}

float Enemy::GetHeight() const {
	return geometry.h;
}

float Enemy::GetWidth() const {
	return geometry.w;
}

void Enemy::Update() {
	Move(Up);
}