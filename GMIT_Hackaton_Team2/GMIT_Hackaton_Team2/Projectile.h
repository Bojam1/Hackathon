#ifndef PROJECTILE_H
#define PROJECTILE_H

#include "Box2D\Box2D.h"
#include "CollisionResponder.h"

class Projectile : public CollisionResponder {
private:
	SDL_Rect geometry_;
	b2Body * boxBody_;
	b2BodyDef bodyDef_;// Adding this breaks world step
	int speed_;

	b2Vec2 origin_;
	b2Vec2 direction_;

	Sprite* sprite_;
	bool alive_;

	const int SIZE = 20;


public:
	Projectile(b2World &world, b2Vec2 position, b2Vec2 direction);
	Projectile(b2World &world, b2Vec2 position, b2Vec2 direction, int speed);


	b2Vec2 GetPosition() const;
	float GetHeight() const;
	float GetWidth() const;
	void Update();
	void Draw();
	void Init(std::string path);
	bool isAlive() const;
	void Die();

	bool operator=(Projectile other);

	void Refire(b2Vec2 position, b2Vec2 direction, int speed);

	//needed to override the contact classes in the collision reponder
	virtual void onBeginContact(CollisionResponder* other) override;
	virtual void onEndContact(CollisionResponder* other) override;
};

#endif