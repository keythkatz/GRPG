#include "talkBehavior.h"
#include "NPC.h"
#include "UI.h"

string TalkBehavior::displayText(){ return "Talk to " + ii->getname(); }
void TalkBehavior::action(){
	VECTOR2 collisionVector;
	if (entity->collidesWith(*thePlayer, collisionVector))
	{
		ui->addChatText(ii->getname() + ": " + message);
	}
	else
	{
		thePlayer->setVictim(entity);
		thePlayer->setNPCAction(this);
	}
}