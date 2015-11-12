#include "stdafx.h"
#include "Door.h"
#include <stdlib.h> 
#include <time.h> 
#include <iostream>
#include <string>

Door::Door()
{
	//topDoor = { 608, 0, 32, 50 };
	SDL_Rect rect = { 608, 0, 32, 50 };
	topDoor = new SDL_Rect();
	leftDoor = new SDL_Rect();
	rightDoor = new SDL_Rect();
	bottomDoor = new SDL_Rect();
}

void Door::LoadRectangle()
{	topDoor->x = 608;
	topDoor->y = 0;
	topDoor->w = 50;
	topDoor->h = 50;

	leftDoor->x = 5;
	leftDoor->y = 320;
	leftDoor->w = 50;
	leftDoor->h = 32;

	rightDoor->x = 1220;
	rightDoor->y = 320;
	rightDoor->w = 50;
	rightDoor->h = 32;

	bottomDoor->x = 608;
	bottomDoor->y = 702;
	bottomDoor->w = 50;
	bottomDoor->h = 50;

}
void Door::LoadRoom()
{
	string text = ".txt";
	roomName = "Level";//; + RandomNumber() + text;
	int number = RandomNumber();
	string num = to_string(number);
	roomName += num;
	roomName += text;
	//roomName.erase(5, 1);
	filePath = roomName;
	roomName = "";

}
int Door::RandomNumber()
{
	int random;
	srand(time(NULL));
	random = rand() % 5 + 1;
	return random;
}

bool Door::CheckTopDoorCollisions(SDL_Rect* playerRect)
{
	//The sides of the rectangles
	int leftA, leftB;
	int rightA, rightB;
	int topA, topB;
	int bottomA, bottomB;

	//Calculate the sides of rect A
	leftA = topDoor->x;
	rightA = topDoor->x + topDoor->w;
	topA = topDoor->y;
	bottomA = topDoor->y + topDoor->h;

	//Calculate the sides of rect B
	leftB = playerRect->x;
	rightB = playerRect->x + playerRect->w;
	topB = playerRect->y;
	bottomB = playerRect->y + playerRect->h;

	//If any of the sides from A are outside of B
	if (bottomA <= topB)
	{
		return false;
	}

	if (topA >= bottomB)
	{
		return false;
	}

	if (rightA <= leftB)
	{
		return false;
	}

	if (leftA >= rightB)
	{
		return false;
	}

	//If none of the sides from A are outside B
	return true;
}
bool Door::CheckBottomDoorCollisions(SDL_Rect* playerRect)
{
	//The sides of the rectangles
	int leftA, leftB;
	int rightA, rightB;
	int topA, topB;
	int bottomA, bottomB;

	//Calculate the sides of rect A
	leftA = bottomDoor->x;
	rightA = bottomDoor->x + bottomDoor->w;
	topA = bottomDoor->y;
	bottomA = bottomDoor->y + bottomDoor->h;

	//Calculate the sides of rect B
	leftB = playerRect->x;
	rightB = playerRect->x + playerRect->w;
	topB = playerRect->y;
	bottomB = playerRect->y + playerRect->h;

	//If any of the sides from A are outside of B
	if (bottomA <= topB)
	{
		return false;
	}

	if (topA >= bottomB)
	{
		return false;
	}

	if (rightA <= leftB)
	{
		return false;
	}

	if (leftA >= rightB)
	{
		return false;
	}

	//If none of the sides from A are outside B
	return true;
}
bool Door::CheckLeftDoorCollisions(SDL_Rect* playerRect)
{
	//The sides of the rectangles
	int leftA, leftB;
	int rightA, rightB;
	int topA, topB;
	int bottomA, bottomB;

	//Calculate the sides of rect A
	leftA = leftDoor->x;
	rightA = leftDoor->x + leftDoor->w;
	topA = leftDoor->y;
	bottomA = leftDoor->y + leftDoor->h;

	//Calculate the sides of rect B
	leftB = playerRect->x;
	rightB = playerRect->x + playerRect->w;
	topB = playerRect->y;
	bottomB = playerRect->y + playerRect->h;

	//If any of the sides from A are outside of B
	if (bottomA <= topB)
	{
		return false;
	}

	if (topA >= bottomB)
	{
		return false;
	}

	if (rightA <= leftB)
	{
		return false;
	}

	if (leftA >= rightB)
	{
		return false;
	}

	//If none of the sides from A are outside B
	return true;
}
bool Door::CheckRightDoorCollisions(SDL_Rect* playerRect)
{
	//The sides of the rectangles
	int leftA, leftB;
	int rightA, rightB;
	int topA, topB;
	int bottomA, bottomB;

	//Calculate the sides of rect A
	leftA = rightDoor->x;
	rightA = rightDoor->x + rightDoor->w;
	topA = rightDoor->y;
	bottomA = rightDoor->y + rightDoor->h;

	//Calculate the sides of rect B
	leftB = playerRect->x;
	rightB = playerRect->x + playerRect->w;
	topB = playerRect->y;
	bottomB = playerRect->y + playerRect->h;

	//If any of the sides from A are outside of B
	if (bottomA <= topB)
	{
		return false;
	}

	if (topA >= bottomB)
	{
		return false;
	}

	if (rightA <= leftB)
	{
		return false;
	}

	if (leftA >= rightB)
	{
		return false;
	}

	//If none of the sides from A are outside B
	return true;
}

SDL_Rect Door::GetTopDoorRect()
{
	return *topDoor;
}
SDL_Rect Door::GetBottomDoorRect()
{
	return *bottomDoor;
}
SDL_Rect Door::GetLeftDoorRect()
{
	return *leftDoor;
}
SDL_Rect Door::GetRightDoorRect()
{
	return *rightDoor;
}