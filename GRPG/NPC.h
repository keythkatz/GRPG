#ifndef _NPC_H                 // Prevent multiple definitions if this 
#define _NPC_H				// file is included in more than one place

#include "constants.h"
#include "Person.h"
#include "graphics.h"
#include "entity.h"
#include <string>

class PersonLoader;
class DrawManager;

class NPC : public Person
{
private:
	string name;
	string description;
	int maxHealth;

	bool isEnemy;

public:

	NPC() : Person() {}
	NPC(string i, float mov, float atk, float h, float w, int cols, int colHeight, int colWidth, string nama,string desc,int maxhp, bool enemy)
		: Person(i, mov, atk, h, w, cols, colHeight, colWidth)
	{
		name = nama;
		description = desc;
		maxHealth = maxhp;
		isEnemy = enemy;
	}

	static Entity* spawn(Game* gamePtr, int npcId, VECTOR2 coords, Entity* victim = nullptr);

	string getname() { return name; }
	string getdescription() { return description; }
	int getmaxhealth() { return maxHealth; }

	bool getIsEnemy() { return isEnemy; }
};

#endif