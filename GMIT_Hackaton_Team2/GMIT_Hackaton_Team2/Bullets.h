#ifndef BULLETS_H
#define BULLETS_H

#include "stdafx.h"
#include "Projectile.h"
#include <vector>
#include <algorithm>

using std::vector;

class Bullets : public vector<Projectile>
{
private:
	const char* ASSETNAME;
	const int MAX_AMMO;

	b2World * world_;

	void Cull();

public:
	Bullets(b2World &world);

	bool Fire(b2Vec2 position, b2Vec2 direction);
	void Update();
	void Draw();
};

#endif