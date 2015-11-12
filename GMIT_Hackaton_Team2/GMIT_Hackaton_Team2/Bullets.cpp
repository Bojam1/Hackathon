#include "stdafx.h"
#include "Bullets.h"

Bullets::Bullets(b2World &world) : world_(&world), ASSETNAME("Assets/projectile.png"), MAX_AMMO(10)
{
	reserve(MAX_AMMO);
}

bool Bullets::Fire(b2Vec2 position, b2Vec2 direction)
{
	//If we have bullets
	if (size() < MAX_AMMO)
	{
		Projectile temp(*world_, position, direction);
		temp.Init(ASSETNAME);
		push_back(temp);
		return true;
	}

	else return false;
}

void Bullets::Update()
{
	for each (Projectile p in *this)
	{
		if (p.isAlive())
		{
			p.Update();
		}
	}

	//Remove dead bullets
	Cull();
}


void Bullets::Draw()
{
	for each (Projectile p in *this)
	{
		if (p.isAlive())
		{
			p.Draw();
		}
	}
}

bool checkDead(const Projectile p)
{
	return !p.isAlive();
}

void Bullets::Cull()
{
	erase(std::remove_if(begin(), end(), checkDead), end());
}
