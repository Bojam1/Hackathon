#ifndef ENEMYMANAGER_H
#define ENEMYMANAGER_H

#include "Enemy.h"
#include <vector>;
#include <iostream> 
#include "FollowEnemy.h"



using namespace std;


class EnemyManager
{
public:
	static const int MAXENEMIES = 10;
	EnemyManager();
	static void init();
	static void AddEnemy(float x, float y, b2World* world);
	static std::vector<FollowEnemy> enemies;
	static void draw();
	static void LoadFromMap(string name, b2World *world);
	static void update(b2Vec2 target);
	
	static int getEnemiesAlive();
	static bool CheckCollision(b2Body*playerBody);

private:
	static int enemiesAlive;
};

#endif