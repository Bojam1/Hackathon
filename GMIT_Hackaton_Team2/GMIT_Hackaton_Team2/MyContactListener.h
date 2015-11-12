#ifndef _MYCONTACTLISTENER_H
#define _MYCONTACTLISTENER_H
#include <Box2D\Dynamics\Contacts\b2Contact.h>
#include "Enemy.h"
#include "Player.h"

class MyContactListener : public b2ContactListener
{
	void BeginContact(b2Contact* contact) override {

		CollisionResponder* bodyUserDataA = static_cast<CollisionResponder*>(contact->GetFixtureA()->GetBody()->GetUserData());
		CollisionResponder* bodyUserDataB = static_cast<CollisionResponder*>(contact->GetFixtureB()->GetBody()->GetUserData());
		if (bodyUserDataA){
			bodyUserDataA->onBeginContact(bodyUserDataB);
		}
		if (bodyUserDataB){
			bodyUserDataB->onBeginContact(bodyUserDataA);
		}
	}

	void EndContact(b2Contact* contact) override {

		CollisionResponder* bodyUserDataA = static_cast<CollisionResponder*>(contact->GetFixtureA()->GetBody()->GetUserData());
		CollisionResponder* bodyUserDataB = static_cast<CollisionResponder*>(contact->GetFixtureB()->GetBody()->GetUserData());
		if (bodyUserDataA){
			bodyUserDataA->onEndContact(bodyUserDataB);
		}
		if (bodyUserDataB){
			bodyUserDataB->onEndContact(bodyUserDataA);
		}
	}
};
#endif