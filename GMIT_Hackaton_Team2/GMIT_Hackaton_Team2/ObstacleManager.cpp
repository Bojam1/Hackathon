#include "stdafx.h"
#include "ObstacleManager.h"

bool ObstacleManager::instanceFlag = false;
ObstacleManager* ObstacleManager::instance = NULL;

std::vector<Obstacle> ObstacleManager::floor(0);


void ObstacleManager::Init(b2World * pWorld, SDL_Renderer * gRenderer)
{
}

void ObstacleManager::Draw()
{
	for each  (Obstacle obstacle in floor) {

		obstacle.Draw();
	}
}

void ObstacleManager::Update()
{
}

void ObstacleManager::Reset(SDL_Rect)
{
}

ObstacleManager * ObstacleManager::GetInstance()
{
	if (!instanceFlag)
	{
		instance = new ObstacleManager;
		instanceFlag = true;
		return instance;
	}
	else
	{
		return instance;
	}
}

void ObstacleManager::addObstacle(SDL_Rect pRect, b2World * world, string path)
{
	Obstacle temp(pRect, world,path);

	floor.push_back(temp);
}

void ObstacleManager::ResetRoom(b2World * world)
{
	for each  (Obstacle obstacle in floor) 
	{
		world->DestroyBody(obstacle.myBody);
	}

	floor.clear();
}


