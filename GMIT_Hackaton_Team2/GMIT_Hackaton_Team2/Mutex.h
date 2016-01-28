#pragma once
#ifndef MUTEX_H
#define MUTEX_H

#include <SDL_thread.h>

class Mutex {
public:
	bool Lock();
	void Unlock();
	static Mutex* GetInstance();
	~Mutex()
	{
		instanceFlag = false;
	}
private:
	Mutex();
	static bool instanceFlag;
	static Mutex* instance;
	SDL_mutex *mutex;
};
#endif