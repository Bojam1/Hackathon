#ifndef _COLLISION_RESPONDER_H
#define _COLLISION_RESPONDER_H

#include "Sprite.h"

class CollisionResponder{
public:
	virtual ~CollisionResponder() {}
	virtual void onBeginContact(CollisionResponder* other) = 0;
	virtual void onEndContact(CollisionResponder* other) = 0;
};
#endif