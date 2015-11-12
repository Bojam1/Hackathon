#ifndef _FOLLOWENEMY_H
#define _FOLLOWENEMY_H

#include <Box2D/Box2D.h>
#include <SDL.h>
#include "Renderer.h"
#include "Enemy.h"


class FollowEnemy : public Enemy {
public:
	FollowEnemy(b2World &world, b2Vec2 const &position, int width, int height);
	~FollowEnemy();

	void Update(b2Vec2 target);
};
#endif