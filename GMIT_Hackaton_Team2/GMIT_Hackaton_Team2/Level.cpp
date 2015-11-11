
#include "stdafx.h"
using namespace std;
#include "Level.h"

Level::Level()
{
}

void Level::LoadLevel(std::string name)
{
	std::vector<std::string> map = Level::LoadFromTextFile(name);
	const int mapX = 58;
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
				//SDL_Rect temp = { x*SCALE, y*SCALE, SCALE, SCALE };
				//PlatformManager::addPlatform(temp, world);


			}
			if (c == 'w')
			{
				//temp.setTextureRect(sf::IntRect(0 * SCALE, 0, SCALE, SCALE));

			}
			if (c == 'R')
			{
				//temp.setTextureRect(sf::IntRect(4 * SCALE, 0, SCALE, SCALE));
				//PlatformManager::addFloor(x*SCALE, y*SCALE, SCALE, SCALE, world, texture);

			}
			if (c == 'L')
			{

				//temp.setTextureRect(sf::IntRect(3 * SCALE, 0, SCALE, SCALE));
				//PlatformManager::addFloor(x*SCALE, y*SCALE, SCALE, SCALE, world, texture);
			}
			if (c == 'l')
			{

				//temp.setTextureRect(sf::IntRect(2 * SCALE, 0, SCALE, SCALE));
				//PlatformManager::addLeftSensor(x * SCALE, y*SCALE, SCALE, SCALE, world, 1);	//1 for left sensor
			}
			if (c == 'r')
			{

				//temp.setTextureRect(sf::IntRect(4 * SCALE, 0, SCALE, SCALE));
				//PlatformManager::addLeftSensor(x * SCALE, y*SCALE, SCALE, SCALE, world, 0);	//0 for right sensor
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
