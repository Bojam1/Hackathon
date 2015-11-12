#ifndef OBSTACLEMANGER_H
#define OBSTACLEMANGER_H

#include <iostream> 
#include <SDL.h>			//SDL
#include <stdio.h>
#include <list>
#include "Obstacle.h"
#include "Renderer.h"
#include <vector>;

using namespace std;

class ObstacleManager
{
public:

	void Init(b2World *pWorld, SDL_Renderer* gRenderer);
	void Draw();
	void Update();
	void Reset(SDL_Rect);
	static ObstacleManager* GetInstance();
	static void addObstacle(SDL_Rect pRect, b2World* world, string path);
	static void addfloor(SDL_Rect pRect, string path);
	~ObstacleManager()
	{
		instanceFlag = false;
	}
private:
	ObstacleManager()
	{
		platforms = std::list<Obstacle>();
	}
	std::list<Obstacle> platforms;
	static bool instanceFlag;
	bool moveIndependantly;
	static ObstacleManager* instance;
	static std::vector<Obstacle> obstacles;
	static std::vector<Obstacle> floor;
};
#endif