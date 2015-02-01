#ifndef pkupBEHAVIOR_H
#define pkupBEHAVIOR_H

#include "Behavior.h"
#include "entity.h"
using namespace std;

class PickupBehavior :public Behavior
{
private:
	DrawManager* drawManager;
	Entity* entity;
	Player* player;
public:
	PickupBehavior(DrawManager* drawMngr,Entity* e,Player* plyr){ 
		drawManager = drawMngr;
		entity = e;
		player = plyr;
	}
	bool exists(){ return true; }
	string displayText(){ return "Pick up "+entity->getInventoryItem()->getItem()->getName(); }
	void action();
};
#endif