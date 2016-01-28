#ifndef _SHOOTTINGENEMY_H
#define _SHOOTTINGENEMY_H

#include <Box2D/Box2D.h>
#include <SDL.h>
#include "Renderer.h"
#include "Enemy.h"
#include "Projectile.h"
#include <vector>

class ShoottingEnemy : public Enemy {
private:
	std::vector<Projectile> bullets;
public:
	ShoottingEnemy(b2World &world, b2Vec2 const &position, int width, int height);
	~ShoottingEnemy();

	void Update(b2Vec2 target, b2World world);
};
#endif