#include "DataBase.h"
#include "stdafx.h"

DataBase::DataBase() {
	begin = 0;
	end = 0;
	count = 0;
	empty = SDL_CreateSemaphore(0);
	full = SDL_CreateSemaphore(size);
}

DataBase::~DataBase() {
	SDL_DestroySemaphore(empty);
	SDL_DestroySemaphore(full);
	SDL_DestroyMutex(mutex);
}

b2Vec2 DataBase::Read() {
	while (count == 0)
	{
		SDL_SemWait(empty);
	}
	if (SDL_LockMutex(mutex) == 0);
	//CO
	b2Vec2 result = buffer[begin];
	begin = (begin + 1) % size;
	count--;
	//OC
	SDL_UnlockMutex(mutex);
	SDL_SemPost(full);
	return result;
}

void DataBase::Write(b2Vec2 p) {
	while (count == size - 1)
	{
		SDL_SemWait(full);
	}
	if (SDL_LockMutex(mutex) == 0);
		//CO
		buffer[end] = p;
	end = (end + 1) % size;
	count++;
	//OC
	SDL_UnlockMutex(mutex);
	SDL_SemPost(empty);
}