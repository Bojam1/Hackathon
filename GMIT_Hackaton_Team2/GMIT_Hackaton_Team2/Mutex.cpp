#include "stdafx.h"
#include "Mutex.h"

bool Mutex::instanceFlag = false;
Mutex* Mutex::instance = NULL;

Mutex::Mutex() {
	mutex = SDL_CreateMutex();
}

Mutex* Mutex::GetInstance()
{
	if (!instanceFlag)
	{
		instance = new Mutex();
		instanceFlag = true;
		return instance;
	}
	else
	{
		return instance;
	}
}

bool Mutex::Lock() {
	return SDL_LockMutex(mutex);
}

void Mutex::Unlock() {
	SDL_UnlockMutex(mutex);
}