
#include "stdafx.h"
using namespace std;
#include "Level.h"

const int Level::SCALE = 32;
const int Level::MAXLEVELS = 5;
int Level::currentlevel = 0;
//sf::Texture Level::texture;

Level::Level()
{
}


void Level::LoadLevel(std::string name, b2World * world)
{
	std::vector<std::string> map = Level::LoadFromTextFile(name);
	const int mapX = 41;
	const int mapY = 23;
	for (int y = 0; y < mapY; y++)
	{
		for (int x = 0; x < mapX; x++)
		{
			char c = (char)map[y][x];
			//temp.setPosition((sf::Vector2f(x * SCALE, y * SCALE)));

			if (c == 'F')
			{
				//temp.setTextureRect(sf::IntRect(1 * SCALE, 0, SCALE, SCALE));
				SDL_Rect temp = { x*SCALE, y*SCALE, SCALE, SCALE };
				ObstacleManager::addObstacle(temp, world,"Assets/bottom.png" );


			}
			if (c == 'l')
			{
				//temp.setTextureRect(sf::IntRect(0 * SCALE, 0, SCALE, SCALE));
				SDL_Rect temp = { x*SCALE, y*SCALE, SCALE, SCALE };
				ObstacleManager::addObstacle(temp, world, "Assets/left.png");

			}
			if (c == 'r')
			{

				SDL_Rect temp = { x*SCALE, y*SCALE, SCALE, SCALE };
				ObstacleManager::addObstacle(temp, world, "Assets/right.png");

			}
			if (c == 'R')
			{
				
				SDL_Rect temp = { x*SCALE, y*SCALE, SCALE, SCALE };
				ObstacleManager::addObstacle(temp, world, "Assets/corner.png");

			}
			if (c == 'L')
			{

				SDL_Rect temp = { x*SCALE, y*SCALE, SCALE, SCALE };
				ObstacleManager::addObstacle(temp, world, "Assets/corner_bot_left.png");
			}
			if (c == 't')
			{

				SDL_Rect temp = { x*SCALE, y*SCALE, SCALE, SCALE };
				ObstacleManager::addObstacle(temp, world, "Assets/top_wall_bottomhalf.png");
			}
			if (c == 'T')
			{

				SDL_Rect temp = { x*SCALE, y*SCALE, SCALE, SCALE };
				ObstacleManager::addObstacle(temp, world, "Assets/top_wall_tophalf.png");
			}
		}
	}
}

vector<string> Level::LoadFromTextFile(string name)
{

	vector<string > mystringvector;
	ifstream myfile;
	myfile.open(name);
	string c = "";
	while (myfile >> c)
	{
		mystringvector.push_back(c);
	}

	myfile.close();
	return mystringvector;

	return std::vector<std::string>();
}
