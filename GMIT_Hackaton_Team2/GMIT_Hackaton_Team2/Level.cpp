
#include "stdafx.h"
using namespace std;
#include "Level.h"
#include "Sprite.h"

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
	
	SDL_Rect source = { 0, 0, 32, 32 };

	for (int y = 0; y < mapY; y++)
	{
		for (int x = 0; x < mapX; x++)
		{
			char c = (char)map[y][x];
			//temp.setPosition((sf::Vector2f(x * SCALE, y * SCALE)));
			if (c == 'w')
			{
				//temp.setTextureRect(sf::IntRect(1 * SCALE, 0, SCALE, SCALE));
				SDL_Rect temp = { x*SCALE, y*SCALE, SCALE, SCALE };
				ObstacleManager::addfloor(temp, "Assets/floor.png");
			}
			if (c == 'B')
			{
				//temp.setTextureRect(sf::IntRect(1 * SCALE, 0, SCALE, SCALE));
				SDL_Rect temp = { x*SCALE, y*SCALE, SCALE, SCALE };
				ObstacleManager::addObstacle(temp, world,"Assets/bot_wall_tophalf.png" );

			}
			if (c == 'b')
			{
				//temp.setTextureRect(sf::IntRect(1 * SCALE, 0, SCALE, SCALE));
				SDL_Rect temp = { x*SCALE, y*SCALE, SCALE, SCALE };
				ObstacleManager::addObstacle(temp, world, "Assets/bot_wall_bottomhalf.png");


			}
			if (c == 'L')
			{
				//temp.setTextureRect(sf::IntRect(0 * SCALE, 0, SCALE, SCALE));
				SDL_Rect temp = { x*SCALE, y*SCALE, SCALE, SCALE };
				ObstacleManager::addObstacle(temp, world, "Assets/left_wall_tophalf.png");

			}
			if (c == 'l')
			{
				//temp.setTextureRect(sf::IntRect(0 * SCALE, 0, SCALE, SCALE));
				SDL_Rect temp = { x*SCALE, y*SCALE, SCALE, SCALE };
				ObstacleManager::addObstacle(temp, world, "Assets/left_wall_bottomhalf.png");

			}
			if (c == 'r')
			{

				SDL_Rect temp = { x*SCALE, y*SCALE, SCALE, SCALE };
				ObstacleManager::addObstacle(temp, world, "Assets/right_wall_bottomhalf.png");

			}
			if (c == 'R')
			{
				
				SDL_Rect temp = { x*SCALE, y*SCALE, SCALE, SCALE };
				ObstacleManager::addObstacle(temp, world, "Assets/right_wall_tophalf.png");

			}
			if (c == '1')
			{
				SDL_Rect temp = { x*SCALE, y*SCALE, SCALE, SCALE };
				ObstacleManager::addfloor(temp,  "Assets/door_t_l.png");
			}
			if (c == '2')
			{
				
				SDL_Rect temp = { x*SCALE, y*SCALE, SCALE, SCALE };
				ObstacleManager::addfloor(temp,  "Assets/door_t_r.png");
			}
			if (c == '3')
			{

				SDL_Rect temp = { x*SCALE, y*SCALE, SCALE, SCALE };
				ObstacleManager::addfloor(temp, "Assets/door_b_l.png");
			}
			if (c == '4')
			{

				SDL_Rect temp = { x*SCALE, y*SCALE, SCALE, SCALE };
				ObstacleManager::addfloor(temp,  "Assets/door_b_r.png");
			}
			if (c == 'D')
			{

				SDL_Rect temp = { x*SCALE, y*SCALE, SCALE, SCALE };
				ObstacleManager::addfloor(temp,  "Assets/r_door_t_l.png");
			}
			if (c == 'O')
			{

				SDL_Rect temp = { x*SCALE, y*SCALE, SCALE, SCALE };
				ObstacleManager::addfloor(temp, "Assets/r_door_t_r.png");
			}
			if (c == 'd')
			{

				SDL_Rect temp = { x*SCALE, y*SCALE, SCALE, SCALE };
				ObstacleManager::addfloor(temp,  "Assets/r_door_b_l.png");
			}
			if (c == 'o')
			{

				SDL_Rect temp = { x*SCALE, y*SCALE, SCALE, SCALE };
				ObstacleManager::addfloor(temp,"Assets/r_door_b_r.png");
			}
			if (c == 'U')
			{

				SDL_Rect temp = { x*SCALE, y*SCALE, SCALE, SCALE };
				ObstacleManager::addfloor(temp,  "Assets/b_door_t_l.png");
			}
			if (c == 'V')
			{

				SDL_Rect temp = { x*SCALE, y*SCALE, SCALE, SCALE };
				ObstacleManager::addfloor(temp,  "Assets/b_door_t_r.png");
			}
			if (c == 'u')
			{

				SDL_Rect temp = { x*SCALE, y*SCALE, SCALE, SCALE };
				ObstacleManager::addfloor(temp,  "Assets/b_door_b_l.png");
			}
			if (c == 'v')
			{

				SDL_Rect temp = { x*SCALE, y*SCALE, SCALE, SCALE };
				ObstacleManager::addfloor(temp,  "Assets/b_door_b_r.png");
			}
			if (c == '5')
			{

				SDL_Rect temp = { x*SCALE, y*SCALE, SCALE, SCALE };
				ObstacleManager::addfloor(temp, "Assets/l_door_t_l.png");
			}
			if (c == '6')
			{

				SDL_Rect temp = { x*SCALE, y*SCALE, SCALE, SCALE };
				ObstacleManager::addfloor(temp, "Assets/l_door_t_r.png");
			}
			if (c == '7')
			{

				SDL_Rect temp = { x*SCALE, y*SCALE, SCALE, SCALE };
				ObstacleManager::addfloor(temp, "Assets/l_door_b_l.png");
			}
			if (c == '8')
			{

				SDL_Rect temp = { x*SCALE, y*SCALE, SCALE, SCALE };
				ObstacleManager::addfloor(temp, "Assets/l_door_b_r.png");
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



