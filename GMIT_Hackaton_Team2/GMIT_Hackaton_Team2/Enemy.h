#ifndef _PLAYER_H
#define _PLAYER_H

#include <Box2D/Box2D.h>
#include <SDL.h>
#include "Renderer.h"
#include "CollisionResponder.h"
#include "Sprite.h"


class Enemy : public CollisionResponder {
private:
	SDL_Rect geometry;
	b2Body* boxBody;
	b2BodyDef bodyDef;
	int speed;
	enum Direction { Up, Down, Left, Right };
	Direction m_dir;

	Sprite* m_sprite;

public:
	Enemy(b2World &world, b2Vec2 const &position, int width, int height);
	~Enemy();

	void Move(Direction dir);

	b2Vec2 GetPosition() const;
	float GetHeight() const;
	float GetWidth() const;
	void Update();
	void Draw();
	void Init(std::string path);

	//needed to override the contact classes in the collision reponder
	virtual void onBeginContact(CollisionResponder* other) override;
	virtual void onEndContact(CollisionResponder* other) override;
};
#endif