#ifndef _PLAYER_H
#define _PLAYER_H

#include <Box2D/Box2D.h>
#include <SDL.h>
#include "Renderer.h"
#include "CollisionResponder.h"


class Enemy : public CollisionResponder {
private:
	SDL_Rect geometry;
	b2Body* boxBody;
	int speed;
	enum Direction { Up, Down, Left, Right };
	Direction m_dir;


public:
	Enemy(b2World &world, b2Vec2 const &position, int width, int height, Direction dir);
	~Enemy();

	void Move(Direction dir);

	b2Vec2 GetPosition() const;
	float GetHeight() const;
	float GetWidth() const;
	void Update();

};
#endif