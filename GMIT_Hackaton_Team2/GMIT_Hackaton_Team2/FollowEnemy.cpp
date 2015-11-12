#include "stdafx.h"
#include "FollowEnemy.h"

FollowEnemy::FollowEnemy(b2World &world, b2Vec2 const &position, int width, int height) : Enemy(world,position,width,height){
	speed = 1;
}

FollowEnemy::~FollowEnemy() {

}

void FollowEnemy::Update(b2Vec2 target) {
	geometry.x = boxBody->GetPosition().x;
	geometry.y = boxBody->GetPosition().y;

	if (target.x > geometry.x)
	{
		Move(Right);
	}
	else if (target.x < geometry.x) 
	{
		Move(Left);
	}
	if (target.y > geometry.y)
	{
		Move(Down);
	}
	else if (target.y < geometry.y)
	{
		Move(Up);
	}

	m_sprite->SetPosition(boxBody->GetPosition().x, boxBody->GetPosition().y);
}