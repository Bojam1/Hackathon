#include "stdafx.h"
#include "ShoottingEnemy.h"

ShoottingEnemy::ShoottingEnemy(b2World &world, b2Vec2 const &position, int width, int height) : Enemy(world, position, width, height) {
	speed = 1;
	bodyDef.userData = this;
}

ShoottingEnemy::~ShoottingEnemy() {

}

void ShoottingEnemy::Update(b2Vec2 target, b2World world) {
	geometry.x = boxBody->GetPosition().x;
	geometry.y = boxBody->GetPosition().y;
	
	float distanceToPlayer = sqrt(pow(target.x - geometry.x, 2) + pow(target.y - geometry.y,2));
	if (distanceToPlayer < 200)
	{
		b2Vec2 temp = b2Vec2(target.x - geometry.x, target.y - geometry.y);
		bullets.push_back(Projectile(world, b2Vec2(geometry.x, geometry.y), temp));
	}
	else 
	{
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
	}

	m_sprite->SetPosition(boxBody->GetPosition().x, boxBody->GetPosition().y);
}