#include "stdafx.h"
#include "EnemyManager.h"
#include "Level.h"


using namespace std;
std::vector<FollowEnemy> EnemyManager::enemies(0);
int EnemyManager::enemiesAlive = 0;

EnemyManager::EnemyManager()
{
}

void EnemyManager::init()
{
}

void EnemyManager::AddEnemy(float x, float y, b2World * world)
{
	b2Vec2 pos(x, y);
	FollowEnemy temp = FollowEnemy( *world, pos, 50, 50);

	enemies.push_back(temp);
	
}

void EnemyManager::draw()
{
	for (int i = 0; i< enemies.size(); i++)
	{
		enemies[i].Draw();
	}
}

void EnemyManager::LoadFromMap(string name, b2World * world)
{
	enemies.clear();
	vector<string> map = Level::LoadFromTextFile(name);
	const int mapX = 41;
	const int mapY = 23;
	const int SCALE = 32;


	for (int y = 0; y < mapY; y++)
	{
		for (int x = 0; x < mapX; x++)
		{
			char c = (char)map[y][x];

			if (c == 'E')
			{

				AddEnemy(x * SCALE, y * SCALE, world);

			}
			if (c == 'S')
			{

				//to do: add sensor to turn enemy around


			}


		}
	}

}

void EnemyManager::update(b2Vec2 target)
{
	enemiesAlive = 0;
	for (int i = 0; i < enemies.size(); i++)
	{
		enemies[i].Update(target);
		if (enemies[i].Alive())
		{
			enemiesAlive++;
		}
	}
}

int EnemyManager::getEnemiesAlive()
{
	return 0;
}

bool EnemyManager::CheckCollision(b2Body * playerBody)
{
	return false;
}
