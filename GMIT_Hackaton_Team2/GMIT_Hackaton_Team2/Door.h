#ifndef DOOR_H
#define DOOR_H

#include <iostream> 
#include "SDL.h"

using namespace std;

class Door
{
public:
	Door();
	string filePath;
	void LoadRectangle();
	void LoadRoom();
	int RandomNumber();
	SDL_Rect GetTopDoorRect();
	SDL_Rect GetBottomDoorRect();
	SDL_Rect GetLeftDoorRect();
	SDL_Rect GetRightDoorRect();
	bool CheckTopDoorCollisions(SDL_Rect* playerRect);
	bool CheckBottomDoorCollisions(SDL_Rect* playerRect);
	bool CheckLeftDoorCollisions(SDL_Rect* playerRect);
	bool CheckRightDoorCollisions(SDL_Rect* playerRect);
private:
	string roomName;
	SDL_Rect* topDoor;
	SDL_Rect* bottomDoor;
	SDL_Rect* leftDoor;
	SDL_Rect* rightDoor;
};

#endif

