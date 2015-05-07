#include "Dragonfire.h"
#include "grpg.h"
#include "Aidil.h"

void Dragonfire::draw(Viewport* viewport)
{
	Entity::draw(viewport);
}

bool Dragonfire::initialize(Game *gamePtr, TextureManager* tm, Destination* d, float rotation)
{
	bool result = Entity::initialize(gamePtr, 0, 0, 0, tm);
	setDestination(d);
	image.setRadians(rotation);
	return result;
}

void Dragonfire::update(float frameTime, Game* gamePtr)
{
	//Don't bother doing pathfinding with these, we'll do a simple one
	//Entity::update(frameTime, gamePtr);
	//calculate angle
	VECTOR2 direction = destination->getVector() - getVector();
	VECTOR2 *normalizedDirection = &VECTOR2();
	D3DXVec2Normalize(normalizedDirection, &direction);

	setX(getX() + normalizedDirection->x * aidilNS::dragonfireSpeed * frameTime);
	setY(getY() + normalizedDirection->y * aidilNS::dragonfireSpeed * frameTime);
	float distanceToDest = D3DXVec2Length(&direction);
	if (distanceToDest < aidilNS::dragonfireSpeed * frameTime)
	{
		//We've reached our destination (or are close enough to it, yay!
		gamePtr->getDrawManager()->removeObject(this);
		delete this;
	}
}