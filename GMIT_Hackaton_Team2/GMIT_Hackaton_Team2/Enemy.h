#ifndef _ENEMY_H
#define _ENEMY_H

#include <Box2D/Box2D.h>
#include <SDL.h>
#include "Renderer.h"
#include "CollisionResponder.h"
#include <MyContactListener.h>
#include "Sprite.h"


class Enemy : public CollisionResponder {
protected:
	b2BodyDef bodyDef;
	b2PolygonShape shape;
	b2FixtureDef myBodyFixtureDef;
	bool takePlayershealth = false;
	SDL_Rect geometry;
	b2Body* boxBody;
	int speed;
	enum Direction { Up, Down, Left, Right };
	Direction m_dir;
	bool alive;
	Sprite* m_sprite;

public:
	Enemy();
	Enemy(b2World &world, b2Vec2 const &position, int width, int height);
	~Enemy();

	void Move(Direction dir);

	b2Vec2 GetPosition() const;
	float GetHeight() const;
	float GetWidth() const;
	bool GetTakePlayershealth();
	void setTakePlayershealth(bool b);
	void Update();
	void Draw();
	void Init(std::string path);

	bool Alive();

	//needed to override the contact classes in the collision reponder
	virtual void onBeginContact(CollisionResponder* other) override;
	virtual void onEndContact(CollisionResponder* other) override;
};
#endif