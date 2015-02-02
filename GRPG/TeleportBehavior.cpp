#include "TeleportBehavior.h"
#include "player.h"
#include "NPC.h"
#include "mapLoader.h"

string TeleportBehavior::displayText(){
	return "Request teleport from " + npc->getname();
}

void TeleportBehavior::action()
{
	VECTOR2 collisionVector;
	if (guyDoingTeleport->collidesWith(*player, collisionVector))
	{
		VECTOR2 coordinates = ml->translateIdToCoords(tileID);
		player->setX(coordinates.x);
		player->setY(coordinates.y);
		player->setVictim(0);
		player->releaseDestination();
	}
	else
	{
		player->setVictim(guyDoingTeleport);
		player->setNPCAction(this);
	}
}