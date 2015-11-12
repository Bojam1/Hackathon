#include "stdafx.h"
#include "Enemy.h"
#include "Player.h"

Enemy::Enemy(){}

Enemy::Enemy(b2World &world, b2Vec2 const &position, int width, int height) :CollisionResponder(){

	geometry.x = position.x;
	geometry.y = position.y;
	geometry.w = width;
	geometry.h = height;

	//Define a b2body
	bodyDef.type = b2_dynamicBody;
	bodyDef.position = b2Vec2(position.x + width*0.5f, position.y + height*0.5f);
	bodyDef.angle = 0;
	//Ask the b2Worldto create our body
	boxBody = world.CreateBody(&bodyDef);

	//Define the shape of the body
	shape.SetAsBox(width * 0.5f, height * 0.5f);
	boxBody->CreateFixture(&shape, 0.0f);

	SDL_Rect tempSRC{ 0,0,50,50 };
	m_sprite = new Sprite();
	m_sprite->Init("Assets/enemy.png", geometry, tempSRC);
	m_sprite->SetOffset(GetWidth()*0.5f, GetHeight()*0.5f);

	alive = true;
}

Enemy::~Enemy() {

}

void Enemy::Move(Direction dir) {
	switch (dir)
	{
	case Enemy::Up:
		geometry.y -= speed;
		break;
	case Enemy::Down:
		geometry.y += speed;
		break;
	case Enemy::Left:
		geometry.x -= speed;
		break;
	case Enemy::Right:
		geometry.x += speed;
		break;
	default:
		std::cout << "direction not valid" << std::endl;
		break;
	}
	boxBody->SetTransform(b2Vec2(geometry.x,geometry.y), 0);
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

bool Enemy::GetTakePlayershealth() {
	return takePlayershealth;
}

void Enemy::setTakePlayershealth(bool b) {
	takePlayershealth = b;
}

void Enemy::Update() {
	geometry.x = boxBody->GetPosition().x;
	geometry.y = boxBody->GetPosition().y;
}

void Enemy::Draw() {
	//if(alive)
	m_sprite->Draw();
}

void Enemy::onBeginContact(CollisionResponder* other) {
	std::cout << "enemy Collide begin" << std::endl;

}

void Enemy::onEndContact(CollisionResponder* other) {
	std::cout << "enemy Collide end" << std::endl;
	takePlayershealth = true;
}

void Enemy::Init(std::string path) {
	SDL_Rect tempSRC{ 0,0,50,50 };
	m_sprite = new Sprite();
	m_sprite->Init(path, geometry, tempSRC);
	m_sprite->SetOffset(GetWidth()*0.5f, GetHeight()*0.5f);
}
bool Enemy::Alive() {
	return alive;
}