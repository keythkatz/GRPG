//  Module:             Games Programming
//  Assignment2:        GRPG
//  Student Name:       Matthew Lee
//  Student Number:     s10128677

#ifndef QUESTLOADER_H
#define QUESTLOADER_H

#include "constants.h"
#include "Quest.h"
#include "GameEventManager.h"
#include "GameEvent_Damage.h"
#include <fstream>
#include <iostream>
#include <string>
#include <map>
#include "string_functions.h"

class QuestLoader{
private:
	const std::string questLocation = "assets/quests/quests.gdef";
	map<int, Quest*> mapQuests;
	int currentlyShownIndex = -1;
public:
	QuestLoader(){}
	~QuestLoader(){
		for (map<int, Quest*>::iterator it = mapQuests.begin(); it != mapQuests.end(); ++it){
			SAFE_DELETE(it->second);
		}
		mapQuests.clear();
	}
	void loadAllQuests(GameEventManager* gem, PersonLoader* personLoader, Graphics* g,float uiX,float uiY);
	map<int, Quest*>* getMapQuests() {
		return &mapQuests;
	}
	Quest* getQuest(int id)
	{
		return mapQuests[id];
	}
	int getCurrentlyShownIndex(){ return currentlyShownIndex; }
	void setCurrentlyShownIndex(int i){ currentlyShownIndex = i; }
};
#endif