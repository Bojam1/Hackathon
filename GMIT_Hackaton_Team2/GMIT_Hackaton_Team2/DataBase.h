#pragma once
#ifndef DATABASE_H
#define DATABASE_H

//includes
#include "stdafx.h"
#include "Player.h"
#include <windows.h>
#include <stdio.h>
#include <SDL.h>
#include <SDL_thread.h>
#include <vector>

class DataBase {
public:
	DataBase();
	~DataBase();
	b2Vec2 Read();
	void Write(b2Vec2 p);

private:
	static const int size = 2;
	b2Vec2 buffer[size];
	int begin;
	int end;
	int count;

	SDL_semaphore* empty;
	SDL_semaphore* full;
	SDL_mutex* mutex;
};
#endif
