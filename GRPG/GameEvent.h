// Module: Games Programming
// Assignment 2: GRPG
//  Student Name:       Matthew Lee
//  Student Number:     s10128677

#ifndef _GAMEEVENT_H                 // Prevent multiple definitions if this 
#define _GAMEEVENT_H                 // file is included in more than one place

#include "constants.h"
#include "Entity.h"
#include <string>
#include "QuestData.h"

class GameEvent
{
protected:
	string beforeCompleteText;
	string afterCompleteText;
	//Represents information for quest data update. If empty string, do nothing.
	//Otherwise, change the relevant information
	string numberToChange;
	int newNumber;
public:
	GameEvent(string before, string after){
		beforeCompleteText = before;
		afterCompleteText = after;
		numberToChange = "";
		newNumber = 0;
	}
	virtual ~GameEvent(){ 
		//should be deleted elsewhere
	}

	virtual void addChangeRequired(string n, int newN)
	{
		numberToChange = n;
		newNumber = newN;
	}

	virtual void performChange(QuestData* qd)
	{
		if (numberToChange != "")
		{
			qd->setValue(numberToChange, newNumber);
		}
	}

	virtual bool is(GameEvent* ge) = 0;
	virtual string getType(){ return "GAMEEVENT"; }

	virtual string getBeforeText() { return beforeCompleteText; }
	virtual string getAfterText() { return afterCompleteText; }
};

#endif